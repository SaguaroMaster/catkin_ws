import cv2

def main():
    camera = cv2.VideoCapture("nvarguscamerasrc ! video/x-raw(memory:NVMM), width=(int)3264, height=(int)2464,format=(string)NV12, framerate=(fraction)21/1 ! nvvidconv ! video/x-raw, format=(string)BGRx ! videoconvert ! video/x-raw, format=(string)BGR ! appsink")
    camera.set(3, 640)
    camera.set(4, 480)

    while( camera.isOpened()):
        _, image = camera.read()    #  _ is a value for the succes/fail of retrieving the image
        image = cv2.flip(image, 0)
        cv2.imshow('Original', image)

        b_w_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
        cv2.imshow('B/W', b_w_image)

        if cv2.waitKey(1) & 0xFF == ord('q') :
            break

    cv2.destroyAllWindows()

if __name__ == '__main__':
    main()
