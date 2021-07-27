cmake_minimum_required(VERSION 3.10.2)

project(pet_mcu_core)

add_library(mcu_core INTERFACE)
add_library(pet::mcu_core ALIAS mcu_core)
target_sources(mcu_core
  INTERFACE
    $<INSTALL_INTERFACE:share/pet_mcu_common/src/main.cpp>
    $<INSTALL_INTERFACE:share/pet_mcu_common/src/rosserial_node.cpp>
    $<INSTALL_INTERFACE:share/pet_mcu_common/src/timer.cpp>
    $<INSTALL_INTERFACE:share/pet_mcu_common/src/arduino_module.cpp>
    $<INSTALL_INTERFACE:share/pet_mcu_common/src/prgmem_string.cpp>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/rosserial_node.cpp>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/timer.cpp>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/arduino_module.cpp>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/prgmem_string.cpp>
)
target_include_directories(mcu_core
  INTERFACE
    $<INSTALL_INTERFACE:include/pet_mcu_common>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_link_libraries(mcu_core
  INTERFACE
    pet::ros_lib
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/
  DESTINATION share/pet_mcu_common/src
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
  DESTINATION include/pet_mcu_common
)

install(TARGETS mcu_core ros_lib
  EXPORT ${PROJECT_NAME}-export
  ARCHIVE DESTINATION lib/${PROJECT_NAME}
  LIBRARY DESTINATION lib/${PROJECT_NAME}
  RUNTIME DESTINATION bin
)

install(EXPORT ${PROJECT_NAME}-export
  FILE ${PROJECT_NAME}Targets.cmake
  NAMESPACE pet::
  DESTINATION share/pet_mcu_common/cmake
)
