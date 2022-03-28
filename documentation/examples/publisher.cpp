#include <ros.h>
#include <std_msgs/Float64.h>

ros::NodeHandle nh;
std_msgs::Float64 Vr_msg;
ros::Publisher speed_R("speed_R", &Vr_msg);

float Vr_mps;

void setup(){
    nh.initNode();
    nh.advertise(speed_R);
}
void loop(){
    Vr_msg.data = Vr_mps;
    speed_R.publish(&Vr_msg);
    nh.SpinOnce;
}
