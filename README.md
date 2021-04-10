<h1 align="center">Welcome to the Pet MCU Base repository</h1> 

# Repository Content

Source code to our Pet-series micro robots (target platforms).
 Target platform | Short description 
 -----|------ 
[Pet-Mk-IV](https://github.com/kullken/Pet-Mk-IV) | https://github.com/kullken/Pet-Mk-IV
Pet-Mk-V                                          | (does not yet have its own repository)
  
The main objective/scope for this repository is to control the firmware on our MCU's. 
- Simplification: As MCU we mainly using Arduino compatible hardware, like Arduino UNO and Arduino NANO. 
- Standardisation: As system integration tool (Middle ware) we use ROS. Each MCU act as an ROS-serial device. 
- Modularisation: We have tried to make the code as generic/common as possible. 

 Path | Short description 
 -----|------ 
 [pet_mcu_base/core/src/](https://github.com/kullken/pet_mcu_base/tree/main/core/src) | Basic functionality for interacting with ROS-serial
 [pet_mcu_base/modules/](https://github.com/kullken/pet_mcu_base/tree/main/modules) | Function specific modules. Controlling input(Sensors)/Output(Actuators) 

As "top node" we use ROS on Raspian/Ubuntu - Running Raspberry Pi hardware.

# Developing Environment

Library / Tool | Source
---------------|---------
Arduino IDE | https://www.arduino.cc/en/Main/Software
ROS serial Library for Arduino | https://www.arduinolibraries.info/libraries/rosserial-arduino-library
Ultrasonic sensor Library for Arduino| https://bitbucket.org/teckel12/arduino-new-ping/wiki/
Servo Library for Arduino | https://github.com/arduino-libraries/Servo
IR-remote Library for Arduino | https://github.com/Arduino-IRremote/Arduino-IRremote
