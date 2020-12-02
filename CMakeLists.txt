cmake_minimum_required(VERSION 3.10.2)

project(pet_mcu_base)

find_package(catkin REQUIRED COMPONENTS
  rosserial_arduino
  rosserial_client
  pet_mk_iv_msgs
)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/setup_ros_lib.cmake)

add_subdirectory(core)

add_subdirectory(modules/engine_module)
add_subdirectory(modules/ir_remote_module)
add_subdirectory(modules/light_beacon_module)
add_subdirectory(modules/line_sensor_module)
add_subdirectory(modules/ultrasound_module)

install(TARGETS mcu_core ros_lib engine_module ir_remote_module irremote light_beacon_module servo line_sensor_module ultrasound_module new_ping
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
