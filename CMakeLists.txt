cmake_minimum_required(VERSION 3.10.2)

project(pet_mcu_base)

find_package(catkin REQUIRED COMPONENTS
  rosserial_arduino
  rosserial_client
  pet_mk_iv_msgs
)

catkin_package()

rosserial_generate_ros_lib(
  PACKAGE rosserial_arduino
  SCRIPT make_libraries.py
)

add_library(pet_ros_lib INTERFACE)
add_library(pet::ros_lib ALIAS pet_ros_lib)
target_include_directories(pet_ros_lib
  INTERFACE
    ${${PROJECT_NAME}_ROS_LIB_DIR}
)
