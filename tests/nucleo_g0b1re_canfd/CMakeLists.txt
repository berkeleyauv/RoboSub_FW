cmake_minimum_required(VERSION 3.13.1)

set(DTC_OVERLAY_FILE nucleo_g0b1re_canfd.overlay)
set(BOARD nucleo_g0b1re)

find_package(Zephyr)
project(nucleo_g0b1re_canfd)

target_sources(app PRIVATE src/main.c)