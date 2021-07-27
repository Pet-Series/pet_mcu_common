cmake_minimum_required(VERSION 3.10.2)

project(pet_mcu_engine_module)

add_library(engine_module INTERFACE)
add_library(pet::engine_module ALIAS engine_module)
target_sources(engine_module
  INTERFACE
    $<INSTALL_INTERFACE:share/pet_mcu_common/src/engine_module.cpp>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/engine_module.cpp>
)
target_include_directories(engine_module
  INTERFACE
    $<INSTALL_INTERFACE:include/pet_mcu_common>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_link_libraries(engine_module
  INTERFACE
    pet::mcu_core
    pet::ros_lib
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/src/
  DESTINATION share/pet_mcu_common/src
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
  DESTINATION include/pet_mcu_common
)

install(TARGETS engine_module
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
