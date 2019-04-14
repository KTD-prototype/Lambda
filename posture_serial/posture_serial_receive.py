#!/usr/bin/env python
# -*- coding: utf-8 -*-
#code for python2
import rospy
import serial, time, signal, sys

ser = serial.Serial('/dev/Lambda', 230400)
time.sleep(0.1)
send_command = []
send_command += [chr(1)]

while True:
    # ser.reset_input_buffer()
    ser.write(send_command)
    while ser.inWaiting() < 28:
        # print("loop")
        # print("")
        pass

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

    passed_time = ser.readline()
    passed_time = passed_time.replace('\r\n', '')
    passed_time = float(passed_time)

    print("roll angle : " + str(roll))
    print("pitch angle : " + str(pitch))
    print("heading : " + str(heading))
    print("gyroX : " + str(gyroX))
    print("gyroY : " + str(gyroY))
    print("gyroZ : " + str(gyroZ))
    print("time : " + str(passed_time))
    print("")
