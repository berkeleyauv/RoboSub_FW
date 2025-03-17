# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# initalize pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
# set(PICO_SDK_PATH "/home/mathew/src/pico/pico-sdk")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(slide_sw C CXX ASM)

set(PICO_CXX_ENABLE_EXCEPTIONS 1)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(slide_sw slide_sw.c )

pico_set_program_name(slide_sw "slide_sw")
pico_set_program_version(slide_sw "0.1")

pico_enable_stdio_uart(slide_sw 1)
pico_enable_stdio_usb(slide_sw 0)

# Add the standard library to the build
target_link_libraries(slide_sw pico_stdlib)

# Add any user requested libraries
target_link_libraries(slide_sw
        hardware_clocks
        )

pico_add_extra_outputs(slide_sw)

