cmake_minimum_required(VERSION 3.10.2)

project(pet_mcu_ir_remote_module)

add_library(ir_remote_module INTERFACE)
add_library(pet::ir_remote_module ALIAS ir_remote_module)
target_sources(ir_remote_module
  INTERFACE
    $<INSTALL_INTERFACE:share/pet_mcu_common/src/ir_remote_module.cpp>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/ir_remote_module.cpp>
)
target_include_directories(ir_remote_module
  INTERFACE
    $<INSTALL_INTERFACE:include/pet_mcu_common>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_link_libraries(ir_remote_module
  INTERFACE
    pet::mcu_core
    pet::ros_lib
)

set(ARDUINO_LIBRARIES_PATH $ENV{HOME}/Arduino/libraries)

# IRremote Arduino library
set(IRREMOTE_LIB_PATH ${ARDUINO_LIBRARIES_PATH}/IRremote/src)

add_library(irremote INTERFACE)
target_include_directories(irremote
  INTERFACE
    ${IRREMOTE_LIB_PATH}
)
target_sources(irremote
  INTERFACE
    ${IRREMOTE_LIB_PATH}/IRremote.cpp
    ${IRREMOTE_LIB_PATH}/irPronto.cpp
    ${IRREMOTE_LIB_PATH}/irReceive.cpp
    ${IRREMOTE_LIB_PATH}/irSend.cpp
    ${IRREMOTE_LIB_PATH}/ir_BoseWave.cpp
    ${IRREMOTE_LIB_PATH}/ir_Denon.cpp
    ${IRREMOTE_LIB_PATH}/ir_Dish.cpp
    ${IRREMOTE_LIB_PATH}/ir_JVC.cpp
    ${IRREMOTE_LIB_PATH}/ir_LG.cpp
    ${IRREMOTE_LIB_PATH}/ir_Lego_PF.cpp
    ${IRREMOTE_LIB_PATH}/ir_MagiQuest.cpp
    ${IRREMOTE_LIB_PATH}/ir_NEC.cpp
    ${IRREMOTE_LIB_PATH}/ir_Panasonic.cpp
    ${IRREMOTE_LIB_PATH}/ir_RC5_RC6.cpp
    ${IRREMOTE_LIB_PATH}/ir_Samsung.cpp
    ${IRREMOTE_LIB_PATH}/ir_Sanyo.cpp
    ${IRREMOTE_LIB_PATH}/ir_Sharp.cpp
    ${IRREMOTE_LIB_PATH}/ir_Sharp_alt.cpp
    ${IRREMOTE_LIB_PATH}/ir_Sony.cpp
    ${IRREMOTE_LIB_PATH}/ir_Template.cpp
    ${IRREMOTE_LIB_PATH}/ir_Whynter.cpp
    ${IRREMOTE_LIB_PATH}/esp32.cpp
    ${IRREMOTE_LIB_PATH}/sam.cpp
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/
  DESTINATION share/pet_mcu_common/src
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
  DESTINATION include/pet_mcu_common
)

install(TARGETS ir_remote_module irremote
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
