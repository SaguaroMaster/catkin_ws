#!/usr/bin/env python

import rospy
from std_msgs.msg import Int32
from std_msgs.msg import Float32MultiArray

speed1 = 0
steer1 = 0
throttle1 = 0
rpm_array1 = [0, 0, 0, 0]


def sender(steer_value, throttle_value):
    pub1 = rospy.Publisher('sub_steer', Int32, queue_size=10)
    pub2 = rospy.Publisher('sub_throttle', Int32, queue_size=10)
    rate = rospy.Rate(30) # hz
    pub1.publish(steer_value)
    pub2.publish(throttle_value)
    rate.sleep()

def callback1(data):
    global rpm_array1
    rpm_array1 = data.data

def callback2(data):
    global steer1
    steer1 = data.data

def callback3(data):
    global throttle1
    throttle1 = data.data

def listener():
    rospy.Subscriber("rpm", Float32MultiArray, callback1)
    rospy.Subscriber("steer", Int32, callback2)
    rospy.Subscriber("throttle", Int32, callback3)

    #rospy.spin()

while True:
    try:
        rospy.init_node('jetson', anonymous=True)
        listener()


        throttle_value = 1455
        steer_value = 1000
        

        sender(steer_value, throttle_value)

    except KeyboardInterrupt:
        break
