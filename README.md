# RoboSub_FW

Firmware for Underwater Robotics at Berkeley (UR@B). Based on Zephyr RTOS.

## Setup

1. Follow the [Zephyr Getting Started Guide](https://docs.zephyrproject.org/latest/getting_started/index.html) to install Zephyr dependencies and create a **west** workspace. The following commands will be run in the workspace folder.
2. Checkout the correct version of Zephyr and update the workspace.
	```
	git -C zephyr checkout zephyr-v2.7.0
	west update
	```
3. Clone this repo into the workspace.
	```
	git clone --recursive https://github.com/berkeleyauv/RoboSub_FW.git
	```
4. Try building and running a test project.
	```
	cd tests/nucleo_g0b1re_canfd
	west build
	west flash
	```

To pull new changes, run `git pull --recurse-submodules`.
