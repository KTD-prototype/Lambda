#!/usr/bin/env python
# -*- coding: utf-8 -*-
#code for python2
import rospy
import serial, time, signal, sys

ser = serial.Serial('/dev/Lambda', 115200)
time.sleep(0.1)

while True:
    a = ser.readline()
    # a = a.decode('utf-8')
    # a = float(a)

    b = ser.readline()
    # b = b.decode('utf-8')
    # b = float(b)

    c = ser.readline()
    # c = c.decode('utf-8')
    # c = float(c)

    # a = a * 2

    print(a)
    print(b)
    print(c)
    print(type(a))
    # print(b)
    # print(c)
