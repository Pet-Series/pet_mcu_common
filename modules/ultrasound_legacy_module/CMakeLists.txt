cmake_minimum_required(VERSION 3.10.2)

project(pet_mcu_ultrasound_legacy_module)

add_library(ultrasound_legacy_module INTERFACE)
add_library(pet::ultrasound_legacy_module ALIAS ultrasound_legacy_module)
target_sources(ultrasound_legacy_module
  INTERFACE
    $<INSTALL_INTERFACE:share/pet_mcu_common/src/ultrasound_legacy_module.cpp>
    $<INSTALL_INTERFACE:share/pet_mcu_common/src/ultrasound_legacy.cpp>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/ultrasound_legacy_module.cpp>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/ultrasound_legacy.cpp>
)
target_include_directories(ultrasound_legacy_module
  INTERFACE
    $<INSTALL_INTERFACE:include/pet_mcu_common>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_link_libraries(ultrasound_legacy_module
  INTERFACE
    pet::mcu_core
    pet::ros_lib
    new_ping
)

set(ARDUINO_LIBRARIES_PATH $ENV{HOME}/Arduino/libraries)

# Assume target for NewPing library is already created by modules/ultrasound_module/CMakeLists.txt.
# # NewPing Arduino library
# set(NEW_PING_LIB_PATH ${ARDUINO_LIBRARIES_PATH}/NewPing/src)

# add_library(new_ping INTERFACE)
# target_include_directories(new_ping
#   INTERFACE
#     ${NEW_PING_LIB_PATH}
# )
# target_sources(new_ping
#   INTERFACE
#     ${NEW_PING_LIB_PATH}/NewPing.cpp
# )

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/
  DESTINATION share/pet_mcu_common/src
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
  DESTINATION include/pet_mcu_common
)

install(TARGETS ultrasound_legacy_module #new_ping
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
