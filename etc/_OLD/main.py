import sys
import cv2
import rospy
from std_msgs. msg import Int32

thr_out=1450
str_out=1460
i = 0

camera = cv2.VideoCapture("nvarguscamerasrc ! video/x-raw(memory:NVMM), width=(int)3264, height=(int)2464,format=(string)NV12, framerate=(fraction)21/1 ! nvvidconv ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink")
camera.set(3, 640)
camera.set(4, 480)


def sender(steer_value, throttle_value):
    pub1 = rospy.Publisher('sub_steer', Int32, queue_size=10)
    pub2 = rospy.Publisher('sub_throttle', Int32, queue_size=10)
    rate = rospy.Rate(30) # hz
    while not rospy.is_shutdown():
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
    rospy.Subscriber("rpm", Int32MultiArray, callback1)
    rospy.Subscriber("steer", Int32, callback2)
    rospy.Subscriber("throttle", Int32, callback3)

while (camera.isOpened()):
    throttle_value = 1455
    steer_value = 1000
    wheel_diameter  = 0.355

    rospy.init_node('jetson', anonymous=True)

    sender(steer_value, throttle_value)
    listener()

    avg_rpm_rear = (rpm_array1[0]+rpm_array1[1])/2
    speed = (avg_rpm_rear/60)*1.5*wheel_diameter; 

    i = i+1
    rc_values = {speed, throttle1, steer1}
    thr_learn_raw = throttle1-1455

    if rc_values.mode == 0 :

        _, image = camera.read()    #  _ is a value for the succes/fail of retrieving the image
        image = cv2.flip(image, 0)
        cv2.imwrite("images/video_test_%04d_%04d.png" % (i, steer1), image)
        print("recording")

    if cv2.waitKey(1) & 0xFF == ord('q') :
        break

    #sys.stdout.write("Speed: %.2f m/s, Heading: %d \r" % (rc_values[0], str_learn) )
    #sys.stdout.flush()
