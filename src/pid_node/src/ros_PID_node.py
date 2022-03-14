#!/usr/bin/env python

#from termios import VREPRINT
import rospy
from std_msgs.msg import Int32
from std_msgs.msg import Float64
#from std_msgs.msg import Float64MultiArray
from simple_pid import PID

Kp = 100
Ki = 80
Kd = 0.0

pid = PID(Kp, Ki, Kd)
pid.sample_time = 0.05
target_speed = 0
throttle_target = 1455


rospy.init_node('pid_node')

def sender(throttle_value):
    pub2 = rospy.Publisher('sub_throttle', Int32, queue_size=10)
    rate = rospy.Rate(30) # hz
    pub2.publish(throttle_value)
    rate.sleep()

def callback4(data):
    global target_speed
    target_speed = data.data

def callback_vr(data):
    global Vr
    Vr = data.data

def callback_vl(data):
    Vl = data.data
    speed = (Vl+Vr)/2

    pid.setpoint = target_speed

    if (target_speed != 0):
        Kf = 300
        if (pid.auto_mode != True):
            pid.auto_mode = True
        pid_output = pid(speed) + target_speed * Kf
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
rospy.Subscriber("speed_R", Float64, callback_vr)
rospy.Subscriber("speed_L", Float64, callback_vl)

rospy.spin()