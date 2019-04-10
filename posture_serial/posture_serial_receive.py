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
        if ser.inWaiting() > 23:
            break

    roll = ser.readline()
    roll = roll.replace('\r\n', '')
    roll = float(roll)

    pitch = ser.readline()
    pitch = pitch.replace('\r\n', '')
    pitch = float(pitch)

    heading = ser.readline()
    heading = heading.replace('\r\n', '')
    heading = float(heading)

    gyroX = ser.readline()
    gyroX = gyroX.replace('\r\n', '')
    gyroX = float(gyroX)

    gyroY = ser.readline()
    gyroY = gyroY.replace('\r\n', '')
    gyroY = float(gyroY)

    gyroZ = ser.readline()
    gyroZ = gyroZ.replace('\r\n', '')
    gyroZ = float(gyroZ)

    print("roll angle : " + str(roll))
    print("pitch angle : " + str(pitch))
    print("heading : " + str(heading))
    print("gyroX : " + str(gyroX))
    print("gyroY : " + str(gyroY))
    print("gyroZ : " + str(gyroZ))
    print()
