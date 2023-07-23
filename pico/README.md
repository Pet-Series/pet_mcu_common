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

## Building MicroROS (WIP)

Commands that I do not want to forget that I had to run...

Setting up micro_ros workspace. Only required first time(?). Creates a new directory called `firmware` in the current directory.

```bash
$ cd ~/ws_ros2/src/pet_mcu_common/pico/microros_static_library
$ ros2 run micro_ros_setup create_firmware_ws.sh generate_lib
```

(The above command can complain about "vcs: command not found" and "rosdep: command not found", which are solved by installing "python3-vcstool" and "python3-rosdep", respectively, through apt. When installing rosdep it is also required to run "sudo rosdep init" followed by "rosdep update". Should not both of these be installed together with ROS?)

Building the static library:

```bash
$ cd ~/ws_ros2/src/pet_mcu_common/pico/microros_static_library
$ ros2 run micro_ros_setup build_firmware.sh ~/ws_ros2/src/pet_mcu_common/pico/microros_static_library/library_generation/toolchain.cmake ~/ws_ros2/src/pet_mcu_common/pico/microros_static_library/library_generation/colcon.meta
```

If successful, the above command will create the static library `libmicroros.a` and the `include` directory in the directory `pico/microros_static_library/firmware/build`.
