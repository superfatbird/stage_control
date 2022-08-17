#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Aug 16 16:14:19 2022

@author: dapeng
"""

import serial
ser = serial.Serial('/dev/ttyACM0')
print(ser.name)
while True:
    print(ser.readline())
ser.close()