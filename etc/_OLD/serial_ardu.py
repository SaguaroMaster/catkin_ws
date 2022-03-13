import serial



ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)

spd_out=0
thr_out=1450
str_out=1460
mode=2

while True:

    val = "!{:04}{:04}{:04}".format(spd_out, thr_out, str_out)
    ser.write(bytes(val).encode("utf-8"))
    received=(ser.readline()).decode()         #!aaaaxxxxyyyyzzzz  a=spd in m/s x=thr_in y=str_in z=mode

    if received!="" :
        spd_mps=int(received[1:5])
        thr_in=int(received[5:9])
        str_in=int(received[9:13])
        mode=int(received[13:17])
        print("thr_in: {} us".format(thr_in))
        print("str_in: {} us".format(str_in))
        print("mode: {}".format(mode))
        print("raw in: {}, raw out: {}".format(received[:17], val))
