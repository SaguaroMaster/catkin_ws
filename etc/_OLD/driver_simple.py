import cv2
import numpy as np
import logging
import math
from tensorflow.keras.models import load_model
import serial
import modules
import sys


def compute_steering_angle(model, frame):
    """ Find the steering angle directly based on video frame
        We assume that camera is calibrated to point to dead center
    """
    preprocessed = img_preprocess(frame)
    X = np.asarray([preprocessed])
    steering_angle = model.predict(X)[0]

    return int(steering_angle + 0.5) # round the nearest integer

def img_preprocess(image):
    height, _, _ = image.shape
    image = image[int(height/2):,:,:]  # remove top half of the image, as it is not relevant for lane following
    image = cv2.cvtColor(image, cv2.COLOR_BGR2YUV)  # Nvidia model said it is best to use YUV color space
    image = cv2.GaussianBlur(image, (3,3), 0)
    image = cv2.resize(image, (200,66)) # input image size (200,66) Nvidia model
    image = image / 255 # normalizing, the processed image becomes black for some reason.  do we need this?
    return image

ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=0.5)
#a
spd_out=0
thr_out=1450
str_out=1460

camera = cv2.VideoCapture("nvarguscamerasrc ! video/x-raw(memory:NVMM), width=(int)3264, height=(int)2464,format=(string)NV12, framerate=(fraction)21/1 ! nvvidconv ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink")
camera.set(3, 640)
camera.set(4, 480)

model_path='models/terminator_car_will_kill_you_be_careful.h5'

while (camera.isOpened()):

    model = load_model(model_path)

    rc_values = modules.serial_comm(spd_out, thr_out, str_out)
    thr_learn_raw = rc_values.thr-1455
    str_learn = modules.us_to_degree(rc_values.str)

    if rc_values.mode == 1 :

        _, image = camera.read()    #  _ is a value for the succes/fail of retrieving the image
        image = cv2.flip(image, 0)

        print(compute_steering_angle(model, image))

    if cv2.waitKey(1) & 0xFF == ord('q') :
        break
