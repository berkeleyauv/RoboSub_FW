# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# initalize pico_sdk from installed location
# (note this can come from environment, CMake cache etc)
# set(PICO_SDK_PATH "/home/mathew/src/pico/pico-sdk")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(water_sensor C CXX ASM)

set(PICO_CXX_ENABLE_EXCEPTIONS 1)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(water_sensor water_sensor.c )

pico_set_program_name(water_sensor "water_sensor")
pico_set_program_version(water_sensor "0.1")

pico_enable_stdio_uart(water_sensor 1)
pico_enable_stdio_usb(water_sensor 0)

# Add the standard library to the build
target_link_libraries(water_sensor pico_stdlib)

# Add any user requested libraries
target_link_libraries(water_sensor
        hardware_clocks
        )

pico_add_extra_outputs(water_sensor)

