cmake_minimum_required(VERSION 3.10.2)

project(pet_mcu_light_beacon_module)

add_library(light_beacon_module INTERFACE)
add_library(pet::light_beacon_module ALIAS light_beacon_module)
target_sources(light_beacon_module
  INTERFACE
    $<INSTALL_INTERFACE:share/pet_mcu_base/src/light_beacon_module.cpp>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/light_beacon_module.cpp>
)
target_include_directories(light_beacon_module
  INTERFACE
    $<INSTALL_INTERFACE:include/pet_mcu_base>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_link_libraries(light_beacon_module
  INTERFACE
    pet::mcu_core
    pet::ros_lib
)

set(ARDUINO_LIBRARIES_PATH $ENV{HOME}/Arduino/libraries)

# Servo Arduino library
set(SERVO_LIB_PATH ${ARDUINO_LIBRARIES_PATH}/Servo/src)

add_library(servo INTERFACE)
target_include_directories(servo
  INTERFACE
    ${SERVO_LIB_PATH}
    ${SERVO_LIB_PATH}/avr
)
target_sources(servo
  INTERFACE
    ${SERVO_LIB_PATH}/avr/Servo.cpp
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/
  DESTINATION share/pet_mcu_base/src
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
  DESTINATION include/pet_mcu_base
)

install(TARGETS light_beacon_module servo
  EXPORT ${PROJECT_NAME}-export
  ARCHIVE DESTINATION lib/${PROJECT_NAME}
  LIBRARY DESTINATION lib/${PROJECT_NAME}
  RUNTIME DESTINATION bin
)

install(EXPORT ${PROJECT_NAME}-export
  FILE ${PROJECT_NAME}Targets.cmake
  NAMESPACE pet::
  DESTINATION share/pet_mcu_base/cmake
)
