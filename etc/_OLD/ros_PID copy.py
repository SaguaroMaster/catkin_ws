#!/usr/bin/env python

import sys
import rospy
from std_msgs.msg import Int32
from std_msgs.msg import Float32MultiArray
from std_msgs.msg import Float32

from simple_pid import PID

target_speed = float(sys.argv[1])   #terminal command: python ros_PID.py <Speed in m/s>

pid = PID(80, 60, 0.01)
pid.sample_time = 0.05
speed1 = 0
steer1 = 0
throttle1 = 0
rpm_array1 = [0, 0, 0, 0]

def sender(steer_value, throttle_value ,speed_mps_l, speed_mps_r):
    pub1 = rospy.Publisher('sub_steer', Int32, queue_size=10)
    pub2 = rospy.Publisher('sub_throttle', Int32, queue_size=10)
    pub3 = rospy.Publisher('speedL_stamped', Float32, queue_size=10)
    pub4 = rospy.Publisher('speedR_stamped', Float32, queue_size=10)
    rate = rospy.Rate(30) # hz
    pub1.publish(steer_value)
    pub2.publish(throttle_value)
    pub3.publish(speed_mps_l)
    pub4.publish(speed_mps_r)
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
        steer_value = 1455

        avg_rpm_rear = (rpm_array1[2]+rpm_array1[3])/2
        speed = (avg_rpm_rear/60)*0.355; 

        speed_mps_r = (((rpm_array1[1]+rpm_array1[3])/2)/60)*0.355
        speed_mps_l = (((rpm_array1[0]+rpm_array1[2])/2)/60)*0.355

        pid.setpoint = target_speed

        x = pid(speed)

        Kf = 180 / target_speed
        pid_output = x + (target_speed * Kf)
        if(pid_output>0):
            throttle_target = pid_output+1455
        
        if throttle_target >= 2500 :
            throttle_target = 2500
        elif throttle_target <= 1455 :
            throttle_target = 1455

        print ("Target: %.2f m/s | Current: %.2f m/s | PID: %.2f us | x: %d" % (target_speed, speed, throttle_target, x))
        sender(steer_value, throttle_target, speed_mps_l, speed_mps_r)

    except KeyboardInterrupt:
        break