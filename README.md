# RoboSub_FW

Firmware for Underwater Robotics at Berkeley (UR@B). Based on Zephyr RTOS.

## Setup

1. Follow the [Zephyr Getting Started Guide](https://docs.zephyrproject.org/latest/getting_started/index.html) to install Zephyr dependencies but don't make a workspace just yet.
2. Create a new workspace just for RoboSub_FW.
	```
	west init -m https://github.com/berkeleyauv/RoboSub_FW.git <workspace name>
	cd <workspace name>
	west update
	```
3. Try building and running a test project.
	```
	cd <workspace name>/RoboSub_FW/tests/nucleo_g0b1re_canfd
	west build
	west flash
	```

While we use `west` to manage dependencies, the main repo is still a normal git repo and can be developed as such. If `west.yml` changes, you may need to run `west update` again to update the dependencies.
