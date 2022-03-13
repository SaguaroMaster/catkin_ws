#!/usr/bin/env python

import rospy
from std_msgs. msg import Int32

def sender():
    pub = rospy.Publisher('sub_steer', Int32, queue_size=10)
    rospy.init_node('jetson', anonymous=True)
    rate = rospy.Rate(10) # 10hz
    while not rospy.is_shutdown():
        data = 2000
        rospy.loginfo(data)
        pub.publish(data)
        rate.sleep()

if __name__ == '__main__':
    try:
        sender()
    except rospy.ROSInterruptException:
        pass