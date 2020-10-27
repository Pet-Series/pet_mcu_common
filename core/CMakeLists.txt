cmake_minimum_required(VERSION 3.10.2)

project(pet_mcu_core)

add_library(mcu_core INTERFACE)
add_library(pet::mcu_core ALIAS mcu_core)
target_sources(mcu_core
  INTERFACE
    $<INSTALL_INTERFACE:share/pet_mcu_base/src/main.cpp>
    $<INSTALL_INTERFACE:share/pet_mcu_base/src/rosserial_node.cpp>
    $<INSTALL_INTERFACE:share/pet_mcu_base/src/timer.cpp>
    $<INSTALL_INTERFACE:share/pet_mcu_base/src/arduino_module.cpp>
    $<INSTALL_INTERFACE:share/pet_mcu_base/src/prgmem_string.cpp>
)
target_include_directories(mcu_core
  INTERFACE
    $<INSTALL_INTERFACE:include/pet_mcu_base>
)
target_link_libraries(mcu_core
  INTERFACE
    pet::ros_lib
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/
  DESTINATION share/pet_mcu_base/src
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
  DESTINATION include/pet_mcu_base
)
