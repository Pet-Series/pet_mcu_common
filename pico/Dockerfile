FROM osrf/ros:humble-desktop

SHELL ["/bin/bash", "-c"]

# pico SDK setup based on:
# https://robofoundry.medium.com/raspberry-pi-pico-ros2-via-micro-ros-actually-working-in-1-hr-9f7a3782d3e3
RUN apt-get update && sudo apt install -y build-essential cmake gcc-arm-none-eabi libnewlib-arm-none-eabi

RUN groupadd --system pi && useradd --create-home --shell /bin/bash --gid pi pi

USER pi

RUN mkdir --parents /home/pi/micro_ros_ws/src

WORKDIR /home/pi/micro_ros_ws/src

RUN git clone --recurse-submodules https://github.com/raspberrypi/pico-sdk.git
RUN git clone https://github.com/micro-ROS/micro_ros_raspberrypi_pico_sdk.git

ENV PICO_TOOLCHAIN_PATH=/usr/bin/arm-none-eabi-gcc
ENV PICO_SDK_PATH=/home/pi/micro_ros_ws/src/pico-sdk

WORKDIR /home/pi/micro_ros_ws/src/micro_ros_raspberrypi_pico_sdk

RUN mkdir build
RUN cd build && cmake ..
RUN cd build && make

# Build micro_ros_agent from source
WORKDIR /home/pi/micro_ros_ws/src

RUN git clone https://github.com/micro-ROS/micro-ROS-Agent.git
RUN git clone https://github.com/micro-ROS/micro_ros_msgs.git

WORKDIR /home/pi/micro_ros_ws

RUN source /opt/ros/humble/setup.bash && colcon build --packages-up-to micro_ros_agent

# Running micro_ros_agent requires sudo to get permission to access the usb device.
USER root

## Commands for running the example ##
# docker run -it --volume /media/vk:/media/pi --device=/dev/ttyACM0 pico_poc

# source install/setup.bash
# ros2 run micro_ros_agent micro_ros_agent serial --dev /dev/ttyACM0 baudrate=115200