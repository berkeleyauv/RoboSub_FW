/**
 * Underwater Robotics @ Berkeley
 * 
*/
/**
 * Relay Toggle for an LED
 * 
 * Toggles a relay connected to LED on and off
 */

 #include "pico/stdlib.h"

 #define RELAY_PIN 28
 
 int main() {
     // Initialize standard library
     stdio_init_all();
     
     // Initialize the relay pin as an output
     gpio_init(RELAY_PIN);
     gpio_set_dir(RELAY_PIN, GPIO_OUT);
     
     // Main loop
     while (true) {
         // Delay for 1 second
         sleep_ms(1000);
 
         bool relay_pin_status = gpio_get(RELAY_PIN);
         printf("1)RELAY PIN Status: %d\n", relay_pin_status);
         
         // Turn the relay ON
         gpio_put(RELAY_PIN, 1);
         
         relay_pin_status = gpio_get(RELAY_PIN);
         printf("2)RELAY PIN Status: %d\n", relay_pin_status);
 
         // Delay for 1 second
         sleep_ms(1000);
         
         // Turn the relay OFF
         gpio_put(RELAY_PIN, 0);
 
     }
     
     return 0;
 }