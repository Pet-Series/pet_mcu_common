cmake_minimum_required(VERSION 3.10.2)

project(pet_mcu_core)

add_library(mcu_core INTERFACE)
add_library(pet::mcu_core ALIAS mcu_core)
target_sources(mcu_core
  INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/rosserial_node.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/timer.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/arduino_module.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/prgmem_string.cpp
)
target_include_directories(mcu_core
  INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(mcu_core
  INTERFACE
    pet::ros_lib
)
