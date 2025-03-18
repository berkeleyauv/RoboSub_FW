
Separate Firmware Builds.
These files support Wokwi simulation. 
Run the simulation by clicking on the `diagram.json` files and run the green "Play" Button. 

For each individual firmware, `cd [<name>]/build` then run `cmake ..` and `make` to generate the program binary. 
Then use `picotool -x [binary_name.elf or .uf2]` or other uploading tools to the target device. 
Ensure that the target device is in bootloader mode by checking `ls /media/[username]` and that the target shows up as a file.  

To add an individual firmware, copy a folder and then change the name to the component you want to write firmware for. 
You need to change the `CMakeLists.txt` file,  wokwi's `wokwi.toml` file and the individual `.c` file respectively. 


