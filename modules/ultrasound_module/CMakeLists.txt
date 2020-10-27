cmake_minimum_required(VERSION 3.10.2)

project(pet_ultrasound_module)

add_library(ultrasound_module INTERFACE)
add_library(pet::ultrasound_module ALIAS ultrasound_module)
target_sources(ultrasound_module
  INTERFACE
    $<INSTALL_INTERFACE:share/pet_mcu_base/src/ultrasound_module.cpp>
    $<INSTALL_INTERFACE:share/pet_mcu_base/src/ultrasound.cpp>
)
target_include_directories(ultrasound_module
  INTERFACE
    $<INSTALL_INTERFACE:include/pet_mcu_base>
)
target_link_libraries(ultrasound_module
  INTERFACE
    pet::mcu_core
    pet::ros_lib
    new_ping
)

set(ARDUINO_LIBRARIES_PATH $ENV{HOME}/Arduino/libraries)

# NewPing Arduino library
set(NEW_PING_SOURCE_DIR ${ARDUINO_LIBRARIES_PATH}/NewPing/src)
set(NEW_PING_INCLUDE_DIRS ${NEW_PING_SOURCE_DIR})
set(NEW_PING_SOURCE_FILES
  ${NEW_PING_SOURCE_DIR}/NewPing.cpp
)

add_library(new_ping INTERFACE)
target_sources(new_ping
  INTERFACE
    ${NEW_PING_SOURCE_DIR}/NewPing.cpp
)
target_include_directories(new_ping
  INTERFACE
    ${NEW_PING_INCLUDE_DIRS}
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/
  DESTINATION share/pet_mcu_base/src
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
  DESTINATION include/pet_mcu_base
)
