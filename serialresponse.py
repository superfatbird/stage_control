# import necessary packages
import time
import serial

# get the serial object
ser = serial.Serial('/dev/ttyACM1')
time.sleep(1)

# initial data x, y, z, add theta initial position later
Px = [0, 0, 0]
flag = 0
# prepare the animation function
while flag != 3:
    b = ser.readline()  # read a line from serial, it will be in bytes
    string_n = b.decode() # convert to string
    string = string_n.rstrip() # remove space and \r\n stuff
    print(string)
    if string == 'x':
        flag = 0
    elif string == 'y':
        flag = 1
    elif string == 'z':
        flag = 2
    elif string == 'r':
        flag = 3
    elif string.isdigit():
        if flag == 0:
            Px[-3] += int(string)
        if flag == 1:
            Px[-2] += int(string)
        if flag == 2:
            Px[-1] += int(string)
ser.close()
print("Serial line closed")