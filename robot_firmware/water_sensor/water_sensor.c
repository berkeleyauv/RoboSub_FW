/**
 * Underwater Robotics @ Berkeley
 * 
*/
/**
 * Temperature sensor example using DS18B20 with Raspberry Pi Pico SDK
 */
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "pico/binary_info.h"
#include "libs/onewire/onewire.h"
#include "libs/ds18b20/ds18b20.h"

// DS18B20 sensor is connected to GPIO pin 4
#define DS_PIN 4
//TODO: Work in progress. Need to get the libraries
int main() {
    // Initialize standard library functions (including stdio)
    stdio_init_all();
    
    printf("DS18B20 Temperature Sensor Example\n");

    // Initialize the onewire bus
    onewire_t ow;
    onewire_init(&ow, DS_PIN);

    // Device address storage
    rom_address_t address;
    
    // Program main loop
    while (true) {
        // Reset the bus and check for device presence
        if (!onewire_reset(&ow)) {
            printf("No DS18B20 sensor detected!\n");
            sleep_ms(1000);
            continue;
        }
        
        // Scan for devices (assuming only one device on the bus)
        if (!onewire_rom_search(&ow, &address)) {
            onewire_reset_search(&ow);
            sleep_ms(1000);
            continue;
        }
        
        // Check if device found is a DS18B20 (family code 0x28)
        if (address.rom[0] != 0x28) {
            printf("Device is not a DS18B20 sensor!\n");
            sleep_ms(1000);
            continue;
        }
        
        // Start temperature conversion
        ds18b20_convert(&ow, &address);
        
        // Wait for conversion to complete (at least 750ms for full resolution)
        sleep_ms(750);
        
        // Read temperature
        float temperature = ds18b20_read_temp(&ow, &address);
        
        // Display temperature
        printf("Temperature: %.2f°C\n", temperature);
        
        // Wait before next reading
        sleep_ms(2000);
    }
    
    return 0;
}