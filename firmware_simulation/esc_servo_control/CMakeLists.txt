# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# initalize pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(esc_control C CXX ASM)

set(PICO_CXX_ENABLE_EXCEPTIONS 1)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(esc_control esc_control.c )

pico_set_program_name(esc_control "esc_control")
pico_set_program_version(esc_control "0.1")

pico_enable_stdio_uart(esc_control 1)
pico_enable_stdio_usb(esc_control 0)

# Add the standard library to the build
target_link_libraries(esc_control pico_stdlib)

# Add any user requested libraries
target_link_libraries(esc_control
        hardware_clocks
        hardware_adc
        )

pico_add_extra_outputs(esc_control)

