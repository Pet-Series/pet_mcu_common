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

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/setup_ros_lib.cmake)


add_subdirectory(core)

add_subdirectory(modules/ultrasound_module)
add_subdirectory(modules/engine_module)
add_subdirectory(modules/ir_remote_module)
add_subdirectory(modules/line_sensor_module)

add_subdirectory(pet_mk_iv_uno)

install(TARGETS mcu_core pet_ros_lib engine_module ir_remote_module irremote line_sensor_module ultrasound_module new_ping
  EXPORT ${PROJECT_NAME}-export
  ARCHIVE DESTINATION lib/${PROJECT_NAME}
  LIBRARY DESTINATION lib/${PROJECT_NAME}
  RUNTIME DESTINATION bin
)

install(EXPORT ${PROJECT_NAME}-export
  FILE ${PROJECT_NAME}Targets.cmake
  NAMESPACE pet::
  DESTINATION share/${PROJECT_NAME}/cmake
)

install(FILES "cmake/pet_mcu_baseConfig.cmake"
  DESTINATION share/${PROJECT_NAME}/cmake
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
