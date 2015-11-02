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

timeout = time.time() + 30

ser.setTimeout(2)
ser.flushInput()
im = Image.open("Untitled.bmp")
print im.format, im.size, im.mode
# im.show()
draw = ImageDraw.Draw(im)

for x in range(0, 640):
    for y in range(0, 480):
        draw.point((x,y), 0xFFFFFF)

for x in range(0, 5):
    for y in range(0, 480):
        draw.point((x,y), 0x0)
        
for x in range(635, 640):
    for y in range(0, 480):
        draw.point((x,y), 0x0)
        
for x in range(0, 640):
    for y in range(0, 5):
        draw.point((x,y), 0x0)

for x in range(0, 640):
    for y in range(475, 480):
        draw.point((x,y), 0x0)
    
im.save('Untitled.bmp', "bmp")

while True:
    if time.time() > timeout:
        break   
    line = ser.readline() # wait for start transmision, read line, remove all spaces
    receivedLine = line.split('= ')
    if receivedLine[0] == "X ":
        x_point = receivedLine[1].strip().split('\x00')[0]
        y_point = receivedLine[2].strip().split('\x00')[0]

        x_ = int(x_point)
        y_ = int(y_point)
        print "X = " + str(x_) + "    Y = " + str(y_)
        y_ = 480 - y_
        draw.point((x_,y_), 0xFF)
        im.save('Untitled.bmp', "bmp")
        
del draw
ser.close() # close port
print "closed"
