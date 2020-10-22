cmake_minimum_required(VERSION 3.10.2)

project(pet_mcu_base)

find_package(catkin REQUIRED COMPONENTS
  rosserial_arduino
  rosserial_client
  pet_mk_iv_msgs
)

set(BUILD_SHARED_LIBS FALSE)
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")

set(EXECUTABLE_OUTPUT_PATH ${CATKIN_DEVEL_PREFIX}/${CATKIN_PACKAGE_LIB_DESTINATION}/${PROJECT_NAME})

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
add_dependencies(pet_ros_lib
  ${PROJECT_NAME}_ros_lib
)

add_subdirectory(core)

add_subdirectory(modules/ultrasound_module)
add_subdirectory(modules/engine_module)
add_subdirectory(modules/line_sensor_module)

add_subdirectory(pet_mk_iv_uno)

catkin_package(
  # LIBRARIES pet::mcu_core pet::ultrasound_module
)

# rosserial_configure_client(
#   DIRECTORY pet_mk_iv_uno
#   TOOLCHAIN_FILE ${ROSSERIAL_ARDUINO_TOOLCHAIN}
# )

# rosserial_add_client_target(pet_mk_iv_uno pet_mk_iv_uno ALL)

# rosserial_configure_client(
#   DIRECTORY firmware
#   TOOLCHAIN_FILE ${ROSSERIAL_ARDUINO_TOOLCHAIN}
# )

# rosserial_add_client_target(firmware arduino_uno ALL)
# rosserial_add_client_target(firmware arduino_uno-upload)

# rosserial_add_client_target(firmware arduino_nano ALL)
# rosserial_add_client_target(firmware arduino_nano-upload)
