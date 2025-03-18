/**
 * Underwater Robotics @ Berkeley
 * 
*/
/**
 * Temperature Sensor Reading for Raspberry Pi Pico in C
 * 
 * This program reads temperature from an NTC thermistor connected to ADC pin
 * and calculates the temperature in Celsius using the Steinhart-Hart equation.
 */

 #include "pico/stdlib.h"
 #include "hardware/adc.h"
 #include <stdio.h>
 #include <math.h>
 
 // Constants for temperature calculation
 #define BETA 3950
 #define R1 10000
 #define V_REF 3.3f
 #define ROOM_TEMP_K 298.15f  // 25°C in Kelvin
 
 // ADC configuration
 #define ADC_PIN 28
 #define ADC_CHANNEL 2       // ADC channel for GPIO 28 is 2
 
 int main() {
     // Initialize stdio for console output
     stdio_init_all();
     
     // Initialize ADC
     adc_init();
     adc_gpio_init(ADC_PIN);
     adc_select_input(ADC_CHANNEL);
     
     // Give time for serial to connect
     sleep_ms(2000);
     
     printf("NTC Thermistor Temperature Sensor\n");
     printf("--------------------------------\n");
     
     while (true) {
         // Read the ADC value
         uint16_t adc_raw = adc_read();
         
         // Convert ADC reading to voltage (12-bit ADC on Pico, range 0-4095)
         float voltage = (adc_raw / 4095.0f) * V_REF;
         
         // Calculate the resistance of the thermistor
         float resistance = R1 / ((V_REF / voltage) - 1.0f);
         
         // Calculate temperature using the beta parameter equation
         float kelvin = 1.0f / (1.0f / ROOM_TEMP_K + (1.0f / BETA) * logf(resistance / R1));
         float celsius = kelvin - 273.15f;
         
         // Print the temperature
         printf("Temperature: %.2f °C\n", celsius);
         
         // Wait before next reading
         sleep_ms(1000);
     }
     
     return 0;
 }