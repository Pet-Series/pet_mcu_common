cmake_minimum_required(VERSION 3.10.2)

project(pet_line_sensor_module)

add_library(line_sensor_module INTERFACE)
add_library(pet::line_sensor_module ALIAS line_sensor_module)
target_sources(line_sensor_module
  INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/line_sensor_module.cpp
)
target_include_directories(line_sensor_module
  INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(line_sensor_module
  INTERFACE
    pet::mcu_core
    pet::ros_lib
)
