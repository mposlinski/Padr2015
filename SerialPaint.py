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
im = Image.open("Untitled.png")
print im.format, im.size, im.mode
# im.show()
draw = ImageDraw.Draw(im)
draw.point((0,0), 0xFF)

   # write to stdout
im.save('Untitled.png', "png")
draw.point((10,5), 0xFF)
im.save('Untitled.png', "png")
# im.show()
i = 0
while True:
    if time.time() > timeout:
        break
    i = i+1
    print ser.readline(),  # wait for start transmision
    draw.point((10,i), 0xFF)
    im.save('Untitled.png', "png")

del draw
ser.close() # close port
