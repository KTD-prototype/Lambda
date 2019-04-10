#!/usr/bin/env python
# -*- coding: utf-8 -*-
#code for python2
import rospy
import serial, time, signal, sys

ser = serial.Serial('/dev/Lambda', 115200)
time.sleep(0.1)

while True:
    # ser.reset_input_buffer()

    ser.write(chr(1))
    while True:
        if ser.inWaiting() > 11:
            break

    a = ser.readline()
    a = a.replace('\r\n', '')
    a = float(a)

    b = ser.readline()
    b = b.replace('\r\n', '')
    b = float(b)

    c = ser.readline()
    c = c.replace('\r\n', '')
    c = float(c)



    print(a)
    print(b)
    print(c)
    print("")
    # print(b)
    # print(c)
