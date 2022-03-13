#!/usr/bin/env python

import rospy
from std_msgs.msg import Int32
from std_msgs.msg import Float64
from std_msgs.msg import Float64MultiArray
from simple_pid import PID

from time import sleep

Kp = 80
Ki = 60
Kd = 0.0

pid = PID(Kp, Ki, Kd)
pid.sample_time = 0.05
target_speed = 0
throttle_target = 1455
rpm_array1 = [0, 0, 0, 0]


rospy.init_node('pid_node')

def sender(throttle_value):
    pub2 = rospy.Publisher('sub_throttle', Int32, queue_size=10)
    rate = rospy.Rate(30) # hz
    pub2.publish(throttle_value)
    rate.sleep()


def callback4(data):
    global target_speed
    target_speed = data.data

    
def callback1(data):
    global rpm_array1
    rpm_array1 = data.data

    avg_rpm_rear = (rpm_array1[2]+rpm_array1[3])/2
    speed = (avg_rpm_rear/60)*0.355; 

    pid.setpoint = target_speed

    if (target_speed != 0):
        Kf = 250
        if (pid.auto_mode != True):
            pid.auto_mode = True
        pid_output = pid(speed) + (target_speed * abs(Kf))
        throttle_target = pid_output+1455
    else: 
        Kf = 0
        pid.auto_mode = False
        throttle_target = 1455

    if throttle_target >= 2000 :
        throttle_target = 2000
    elif throttle_target <= 1000 :
        throttle_target = 1000

    sender(throttle_target)



rospy.Subscriber("target_speed", Float64, callback4)
rospy.Subscriber("rpm", Float64MultiArray, callback1)


rospy.spin()