#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Aug 17 15:17:27 2022

@author: dapeng
"""

# import necessary packages
import time
import serial
import math

import matplotlib.pyplot as plt
import matplotlib.animation as animation
# initial data x, y, z, theta and flag for axis, the Px[4] is the flag

Px = [30, 40, 60, 30, 0]
#flag = [0]
# get the serial object
ser = serial.Serial('/dev/ttyACM0')
time.sleep(1)

# create figure and axes objects
fig, ax = plt.subplots()

# animation function
def animate(i, Px, ser):
    b = ser.readline()  # read a line from serial, it will be in bytes
    string_n = b.decode() # convert to string
    string = string_n.rstrip() # remove space and \r\n stuff
    print(string)
    if string == 'x':
        Px[4] = 0
    if string == 'y':
        Px[4] = 1
    if string == 'z':
        Px[4] = 2
        print(Px[3])
    if string == 'r':
        Px[4] = 3
    if string.lstrip("-").isdigit():
        print("flag= ", end="")
        print(Px[4])
        if Px[4] == 0:
            Px[0] += int(string)
            print(Px[0])
        if Px[4] == 1:
            Px[1] += int(string)
            print(Px[1])
        if Px[4] == 2:
            Px[2] += int(string)
            print(Px[2])
        if Px[4] == 3:
            Px[3] += int(string)
    ax.clear()
    realx = Px[0:3]
    realy = [50,70,90, 20 + 20*math.sin(-Px[3]/20)]
    realx.append(20 + 20*math.cos(-Px[3]/20))
    ax.scatter(realx,realy) # plot 4 data points
    ax.set_xlim(0, 100)
    ax.set_ylim(0,100)
    plt.gca().set_aspect('equal', adjustable='box')

# run the animation and show the figure
ani = animation.FuncAnimation(
    fig, animate, fargs=(Px, ser), interval=30
)
plt.show()

ser.close()
print("Serial line closed")