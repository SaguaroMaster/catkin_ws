#include <ros.h>
#include <std_msgs/Int32.h>

int str_req;

ros::NodeHandle nh;
ros::Subscriber<std_msgs::Int32> sub_steer("sub_steer", &messageCb_steer);

void setup(){
    nh.initNode();
}
void loop(){
    nh.SpinOnce;
}

void messageCb_steer(const std_msgs::Int32 &str_msg){
    str_req = str_msg.data;
}