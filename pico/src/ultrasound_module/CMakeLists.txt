cmake_minimum_required(VERSION 3.10.2)

project(pet_pico_ultrasound_module)

add_library(pico_ultrasound_module INTERFACE)
add_library(pet::pico_ultrasound_module ALIAS pico_ultrasound_module)
target_sources(pico_ultrasound_module
  INTERFACE
    $<INSTALL_INTERFACE:share/pet_mcu_common/pico/src/ultrasound_module.cpp>
    $<INSTALL_INTERFACE:share/pet_mcu_common/pico/src/ultrasound.cpp>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/ultrasound_module.cpp>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/ultrasound.cpp>
)
target_include_directories(pico_ultrasound_module
  INTERFACE
    $<INSTALL_INTERFACE:include/pet_mcu_common>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_link_libraries(pico_ultrasound_module
  INTERFACE
    # pet::mcu_core
    # pet::ros_lib
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/
  DESTINATION share/pet_mcu_common/pico/src
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
  DESTINATION include/pet_mcu_common
)

install(TARGETS pico_ultrasound_module
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
