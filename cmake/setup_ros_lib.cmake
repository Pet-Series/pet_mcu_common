add_custom_command(
  OUTPUT ${PROJECT_BINARY_DIR}/ros_lib
  COMMAND ${CATKIN_ENV} rosrun rosserial_arduino make_libraries.py ${PROJECT_BINARY_DIR}
)
add_custom_target(${PROJECT_NAME}_ros_lib ALL
  DEPENDS ${PROJECT_BINARY_DIR}/ros_lib
)

find_package(rosserial_msgs)
find_package(std_msgs)
add_dependencies(${PROJECT_NAME}_ros_lib
  rosserial_msgs_generate_messages_py
  std_msgs_generate_messages_py
)

add_library(ros_lib INTERFACE)
add_library(pet::ros_lib ALIAS ros_lib)
target_include_directories(ros_lib
  INTERFACE
    $<INSTALL_INTERFACE:include/pet_mcu_common/ros_lib>
    $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/ros_lib>
)
add_dependencies(ros_lib
  ${PROJECT_NAME}_ros_lib
)

install(DIRECTORY ${PROJECT_BINARY_DIR}/ros_lib/
  DESTINATION include/pet_mcu_common/ros_lib
)
