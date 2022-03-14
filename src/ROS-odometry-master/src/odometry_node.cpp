#include "ros/ros.h"
#include "robotics_project/floatStamped.h"
#include "robotics_project/customOdom.h"
#include <message_filters/subscriber.h>
#include <message_filters/time_synchronizer.h>
#include <message_filters/sync_policies/approximate_time.h>
#include <geometry_msgs/Quaternion.h>
#include <nav_msgs/Odometry.h>
#include <tf/transform_broadcaster.h>
#include <dynamic_reconfigure/server.h>
#include <robotics_project/ParametersConfig.h>
#include <string.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Int32.h>
#include <sys/time.h>
#include <ctime>

using namespace std;

const double WHEEL_BASELINE=0.25;
const double REAR_FRONT_DISTANCE=0.27;
const double STEERING_FACTOR=1.0;
const double PI=3.14159265;

double x=0.0;
double y=0.0;
double theta=0.0;

double lastStamp=0.0;

double Vr, Vl, steer;

std::string odom_type="ackerman";

ros::Publisher odom_pub;
ros::Publisher odomTest;

struct timeval time_now{};

void speed_L_Callback(const std_msgs::Float64& Vlx)
{
  Vl = Vlx.data;
}

void speed_R_Callback(const std_msgs::Float64& Vrx)
{
  Vr = Vrx.data;
}

void ackermanDriveCalculus(const std_msgs::Int32& steer1){//callback function. ConstPtr is a pointer to the data structure we receive

    steer = steer1.data;  

    steer = (steer-1455) / 16.12;
    double rearVelocity = (Vl+Vr)/2.0;;
    double angularVelocity;
    double Vx;
    double Vy; 

    //computing velocity
    if(odom_type=="ackerman"){
      double normalizedSteeringAngle=steer/STEERING_FACTOR;   
      angularVelocity=rearVelocity*(tan(normalizedSteeringAngle*PI/180));
      angularVelocity=angularVelocity/REAR_FRONT_DISTANCE;
      Vx=rearVelocity;
      Vy=0.0;
    } else if(odom_type=="differential")
    {
      angularVelocity = (Vr - Vl)/WHEEL_BASELINE;
      Vx=rearVelocity*cos(theta);
      Vy=rearVelocity*sin(theta);
    }
    

    

    ROS_INFO("V: [%f], w: [%f]", rearVelocity,angularVelocity);

    gettimeofday(&time_now, nullptr);
    time_t msecs_time = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);
    double secs_time = (double(msecs_time)/1000);

    //computing dt
    double timeSpan;

    timeSpan = secs_time - lastStamp;

    lastStamp = secs_time;

    //runge-kutta integration
    x+=rearVelocity*timeSpan*cos(theta+(angularVelocity*timeSpan)/2);
    y+=rearVelocity*timeSpan*sin(theta+(angularVelocity*timeSpan)/2);
    theta+=angularVelocity*timeSpan;

    geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(theta);

    geometry_msgs::TransformStamped odom_trans;
    odom_trans.header.stamp = ros::Time::now();
    odom_trans.header.frame_id="odom";
    odom_trans.child_frame_id="base_footprint";
    odom_trans.transform.translation.x=x;
    odom_trans.transform.translation.y=y;
    odom_trans.transform.translation.z=0.0;
    odom_trans.transform.rotation=odom_quat;

    //prepare odom message
    nav_msgs::Odometry odom;
    odom.header.stamp=ros::Time::now();
    odom.header.frame_id="odom";

    odom.pose.pose.position.x=x;
    odom.pose.pose.position.y=y;
    odom.pose.pose.position.z=0.0;
    odom.pose.pose.orientation=odom_quat;

    odom.child_frame_id="base_footprint";
    odom.twist.twist.linear.x=Vx;
    odom.twist.twist.linear.y=Vy;
    odom.twist.twist.linear.z=0.0;

    odom.twist.twist.angular.x=0.0;
    odom.twist.twist.angular.y=0.0;
    odom.twist.twist.angular.z=angularVelocity;

    //publish custom odom
    robotics_project::customOdom custom_odom;
    custom_odom.odometry=odom;
    custom_odom.odometry_type=odom_type;
    odomTest.publish(odom);
    odom_pub.publish(custom_odom);

    static tf::TransformBroadcaster br;
    tf::Transform transform;//ros structure for tf
    transform.setOrigin( tf::Vector3(x, y, 0) );//set the origin in a 3d space (Vector3). As the turtle works in a 2d field, the 3rd value is set to 0
    tf::Quaternion q;
    q.setRPY(0, 0, theta);//2d spaces => 1 value of the quaternion
    transform.setRotation(q);
    br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "odom", "base_footprint"));//boradcast the transformation //car-> base_footprint

}


void dynamicRecCallback(robotics_project::ParametersConfig &config, uint32_t level) {
    if(config.mode==0){
      odom_type="ackerman";
      ROS_INFO("Changed mode to: Ackerman ");
    }
    else {
      odom_type="differential";
      ROS_INFO("Changed mode to: Differential ");
    }
    x=config.x;
    y=config.y;
    ROS_INFO("Setting (x,y) to: (%f,%f)",x,y);
    

}


int main(int argc, char **argv){
  	
	ros::init(argc, argv, "odometry_node");

	ros::NodeHandle n;
    odom_pub=n.advertise<robotics_project::customOdom>("custom_odom",60);
    odomTest=n.advertise<nav_msgs::Odometry>("odom",60);
    ROS_INFO("I'm alive");

    ros::Subscriber sub1 = n.subscribe("speed_L", 100, speed_L_Callback);
    ros::Subscriber sub2 = n.subscribe("speed_R", 100, speed_R_Callback);
    ros::Subscriber sub3 = n.subscribe("steer", 100, ackermanDriveCalculus);
  
    dynamic_reconfigure::Server<robotics_project::ParametersConfig> server;
	  dynamic_reconfigure::Server<robotics_project::ParametersConfig>::CallbackType f;
	  f = boost::bind(&dynamicRecCallback, _1,_2);
	  server.setCallback(f);

  	ros::spin();


    return 0;
}
