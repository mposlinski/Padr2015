'''
Created on Oct 30, 2015

@author: mpolisk
'''

import sys
import os
import subprocess


import Image, ImageDraw
import time
import serial
# from EpsImagePlugin import split
# import serial.tools.list_ports as tls

#import psutil
# from Canvas import Line

PORT_5 = 4

# print tls.main()
ser = serial.Serial(PORT_5)  # open first serial port
print ser

ser.setTimeout(2)
print ser.getTimeout()



timeout = time.time() + 10

ser.setTimeout(2)
ser.flushInput()
im = Image.open("Untitled.bmp")
print im.format, im.size, im.mode
# im.show()
draw = ImageDraw.Draw(im)
for x in range(10, 630):
    for y in range(10, 470):
        draw.point((x,y), 0xFFFFFF)
    
im.save('Untitled.bmp', "bmp")


i = 0
while True:
    if time.time() > timeout:
        break
    receivedLine = ser.readline().split(' ')  # wait for start transmision
    if receivedLine[0] == "X":
        print "X = " + receivedLine[2] + "    Y = " + receivedLine[7]
        x_point = receivedLine[2]
        y_point = receivedLine[7]
        x_point = x_point.strip().split('\x00')[0]
        x_ = int(x_point)
        y_point = y_point.strip().split('\x00')[0]
        y_ = int(y_point)
        y_ = 480 - y_
        draw.point((x_,y_), 0xFF)
        im.save('Untitled.bmp', "bmp")
del draw
ser.close() # close port
print "closed"
