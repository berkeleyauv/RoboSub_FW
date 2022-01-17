cmake_minimum_required(VERSION 3.20.0)

set(DTC_OVERLAY_FILE nucleo_g0b1re_canfd.overlay)
set(BOARD nucleo_g0b1re)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(nucleo_g0b1re_canfd)

target_sources(app PRIVATE src/main.c)