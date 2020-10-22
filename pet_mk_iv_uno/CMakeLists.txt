cmake_minimum_required(VERSION 3.10.2)

project(pet_mk_iv_uno)

# TODO: Include these two portably instead of using hardcoded path.
include($ENV{HOME}/ros_ws/src/rosserial/rosserial_arduino/arduino-cmake/cmake/ArduinoToolchain.cmake)
include($ENV{HOME}/ros_ws/src/rosserial/rosserial_arduino/arduino-cmake/cmake/Platform/Arduino.cmake)

register_hardware_platform(${ARDUINO_SDK_PATH}/hardware/arduino)

# Not nicest solution. Would like to only add the flags for code from pet_mk_iv_arduino.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Wextra -Wpedantic")

# Generate Arduino Uno firmware
generate_arduino_firmware(pet_mk_iv_uno
  SRCS src/modules.cpp
  LIBS pet::mcu_core pet::ultrasound_module pet::engine_module pet::line_sensor_module
  BOARD uno
  PORT /dev/ArduinoUno0
  NO_AUTOLIBS
)
