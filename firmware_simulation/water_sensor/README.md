# Pico SDK - Wokwi 

Underwater Robotics @ Berkeley Firmware using Pico SDK along with Wokwi configuration

Additional Libraries Needed:
- https://github.com/adamboardman/pico-onewire
- https://github.com/bonnyr/wokwi-ds1820-custom-chip
- 

## Building

```
mkdir -p build
cd build
cmake ..
make -j4
```

## Simulation

To simulate this project, install [Wokwi for VS Code](https://marketplace.visualstudio.com/items?itemName=wokwi.wokwi-vscode). Open the project directory in Visual Studio Code, press **F1** and select "Wokwi: Start Simulator".

## Automated Testing

This project includes a Wokwi Automation Scenario in [blink.test.yaml](blink.test.yaml). The scenario runs the simulation for 1 second, and verifies that the LED is blinking. The scenario is run automatically on every commit, using [wokwi-ci-action](https://github.com/wokwi/wokwi-ci-action). You can also run the scenario locally, using the [wokwi-cli](https://github.com/wokwi/wokwi-cli) tool:

```
wokwi-cli . --scenario blink.test.yaml --timeout 1000
```
