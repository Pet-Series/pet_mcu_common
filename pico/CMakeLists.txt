cmake_minimum_required(VERSION 3.12)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(pico_micro_ros_poc C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_subdirectory(src/ultrasound_module)

# Linking against "our" version of libmicroros does not work, yet. In the meantime we link against a pre-built version.
set(libmicroros_directory ${CMAKE_CURRENT_SOURCE_DIR}/microros_static_library/libmicroros)
# set(libmicroros_directory ${CMAKE_CURRENT_SOURCE_DIR}/microros_static_library/firmware/build)

link_directories(${libmicroros_directory})

add_executable(pico_firmware
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/pico_transport.c
)

target_link_libraries(pico_firmware
    pico_stdlib
    microros
    pet::pico_ultrasound_module
)

target_include_directories(pico_firmware
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${libmicroros_directory}/include
)

# Workaround for https://github.com/micro-ROS/micro_ros_setup/issues/530
# file(GLOB_RECURSE extra_microros_include_directories LIST_DIRECTORIES true ${libmicroros_directory})
# target_include_directories(pico_firmware
#   PUBLIC
#     ${extra_microros_include_directories}
# )

SET(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -ffunction-sections -fdata-sections")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -ffunction-sections -fdata-sections")

# Configure Pico
pico_enable_stdio_usb(pico_firmware 1)
pico_enable_stdio_uart(pico_firmware 0)
add_compile_definitions(PICO_UART_ENABLE_CRLF_SUPPORT=0)
add_compile_definitions(PICO_STDIO_ENABLE_CRLF_SUPPORT=0)
add_compile_definitions(PICO_STDIO_DEFAULT_CRLF=0)

# Generate UF2
pico_add_extra_outputs(pico_firmware)
