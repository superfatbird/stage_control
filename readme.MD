### Overview
This repository hosts a project of wheelencoder based stage controller. <br />
The encoder and its PCB are from adafruit, the product id is 5001 and 5221. 
The controller mcu could be Feather BLE 32u4 or arduino (with Arduino IDE and .ino scripts). 
Another controller could be a Feather M0 (with circuitpython implementation). 
The computer end software to simulate stage behavior is python.

### Code description
"realsimulator_2ndTry.py" is the python script to animate the stage motion. Four points will be plot in a box. By rotating the encoder, one of them will move accordingly. Four buttons at the outside of the encoder (left, up, right, down) can enable axis for x, y, z and rotation, switching between different axis. The button in the center could be used to switch the fine/coarse movements of the points.

"serialresponse.py" is the python script to test if serial message from the MCU could be used and responded.

### Ref links:
- 1. [encoder datasheet](https://cdn-learn.adafruit.com/assets/assets/000/104/942/original/tsw.pdf?1633105183)
### Photo of the controller
<img src="IMG_2930.JPG" height="300"/></a>
<img src="IMG_2931.JPG" height="300"/></a>

### Notes: 
1. The recommended editor to work with circuitpython is Mu. Unforturnately, it is currently (checked May 4, 2022) does not install properly on Ubuntu 22.04. I think the main convinient-wise feature of Mu is the built-in serial console. So I am just using the default editor of ubuntu and write a very simple python script to listen to what the microcontroller is talking over the serial. The script is "serialread.py", it can be invoked in a terminal with "python3 serialread.py". All it is doing is to print anything it reads from the designated serial port/line.
