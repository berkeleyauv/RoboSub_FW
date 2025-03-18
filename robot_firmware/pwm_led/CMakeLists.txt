# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# initalize pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(pwm_led C CXX ASM)

set(PICO_CXX_ENABLE_EXCEPTIONS 1)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(pwm_led pwm_led.c )

pico_set_program_name(pwm_led "pwm_led")
pico_set_program_version(pwm_led "0.1")

pico_enable_stdio_uart(pwm_led 1)
pico_enable_stdio_usb(pwm_led 0)

# Add the standard library to the build
target_link_libraries(pwm_led pico_stdlib)

# Add any user requested libraries
target_link_libraries(pwm_led
                hardware_clocks
                hardware_pwm
        )

pico_add_extra_outputs(pwm_led)

