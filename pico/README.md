# RaspberryPi Pico + MicroROS

## Building the Firmware

The CMakeLists.txt in this folder defines a target "pico_firmware" with a corresponding uf2-file that can be flashed to the Pico. Configure and build as normal:

```bash
mkdir build
cd build
cmake ..
make
```

## Flashing the Firmware

To flash the Pico using picotool run:

```bash
picotool load pico_firmware.uf2 -f
```

(This assumes picotool is already installed. TODO: add instructions for picotool installation.)

## Running the MicroROS Agent

The MicroROS Agent is the link between the serial communication and the ROS2 topics. The MicroROS Agent needs to know which serial port it should use and what baudrate to communicate with:

```bash
ros2 run micro_ros_agent micro_ros_agent serial --dev /dev/ttyACM0 baudrate=115200
```
