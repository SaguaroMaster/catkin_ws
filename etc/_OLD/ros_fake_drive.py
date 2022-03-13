#!/usr/bin/env python

import rospy
import random
from std_msgs.msg import Float64

steer = speed_L = speed_R = 0
x = 0

def sender(steer, speed_L, speed_R):
    pub1 = rospy.Publisher('speed_L', Float64, queue_size=10)
    pub2 = rospy.Publisher('speed_R', Float64, queue_size=10)
    pub3 = rospy.Publisher('steer', Float64, queue_size=10)
    rate = rospy.Rate(30) # hz
    pub1.publish(speed_L)
    pub2.publish(speed_R)
    pub3.publish(steer)
    rate.sleep()

while True:
    try:
        rospy.init_node('jetson', anonymous=True)

        steer_rand = random.randint(1,2)
        speed_rand = random.randint(1,2)


        if (steer_rand == 1 and steer <=12):
            steer = steer + 0.4
        elif (steer_rand == 2 and steer >=-12):
            steer = steer - 0.4

        if (speed_rand == 1 and speed_L <= 1.2):
            speed_L = speed_L + 0.1
        elif (speed_rand == 2 and speed_L >= 0.1):
            speed_L = speed_L - 0.1

        if (steer > 0):
            speed_R = speed_L - steer*0.01
        elif (steer < 0):
            speed_R = speed_L + abs(steer)*0.01
        elif(steer == 0):
            speed_R = speed_L


        print ("Steer: %.2f deg | speed_L: %.2f m/s | speed_R: %.2f m/s" % (steer, speed_L, speed_R))
        sender(steer, speed_R, speed_L)

    except rospy.ROSInterruptException:
        pass