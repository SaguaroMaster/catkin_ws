import serial

def serial_comm(spd_out, thr_out, str_out):

    ser = serial.Serial()
    ser.baudrate = 115200
    ser.port = '/dev/ttyUSB0'
    ser.timeout = 1

    if ser.is_open == False:
        ser.open()

    spd_mps=0
    thr_in=0
    str_in=0
    mode=0

    val = "!{:04}{:04}{:04}".format(spd_out, thr_out, str_out)
    #ser.write(bytes(val).encode("utf-8"))
    ser.write(bytes(val, encoding="utf-8"))
    received=ser.readline()         #!aaaaxxxxyyyyzzzz  a=spd in m/s x=thr_in y=str_in z=mode
    received=received.decode()      #0123456789012
    i=0
    if received!="" :
        spd_mps=float(received[1:5])/100  #the value is multiplied by 100 on the arduino so that decimal point is not needed and now it has to be divided by 100
        thr_in=int(received[5:9])
        str_in=int(received[9:13])
        mode=int(received[13:17])


    serial_comm.spd_mps = spd_mps
    serial_comm.thr = thr_in
    serial_comm.str = str_in
    serial_comm.mode = mode
    return serial_comm
    #return [spd_mps, thr_in, str_in, mode]


def degree_to_us(degree):
    us = (degree - 90) * 16.12 + 1455
    return us

def us_to_degree(us):
    degree = (us - 1455) / 16.12 + 90
    return degree
