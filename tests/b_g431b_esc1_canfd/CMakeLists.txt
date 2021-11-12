cmake_minimum_required(VERSION 3.13.1)

set(DTC_OVERLAY_FILE b_g431b_esc1_canfd.overlay)
set(BOARD nucleo_g431rb)

find_package(Zephyr)
project(b_g431b_esc1_canfd)

target_sources(app PRIVATE src/main.c)