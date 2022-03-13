#!/usr/bin/env python

import rospy
from std_msgs. msg import Float64

def sender():
    pub = rospy.Publisher('target_speed', Float64, queue_size=10)
    rospy.init_node('jetson', anonymous=True)
    rate = rospy.Rate(30) # 30hz
    while not rospy.is_shutdown():
        data = 0.5
        rospy.loginfo(data)
        pub.publish(data)
        rate.sleep()

if __name__ == '__main__':
    try:
        sender()
    except rospy.ROSInterruptException:
        pass