/**
 * Underwater Robotics @ Berkeley
/**
 * Raspberry Pi Pico Slide Switch
 * 
 * Reads the state of a slide switch connected to a GPIO pin
 * and prints its state 0 or 1
*/

 #include <stdio.h>
 #include "pico/stdlib.h"
 #include "hardware/gpio.h"
 
 #define SWITCH_PIN 28
 
 int main() {
   stdio_init_all();
 
   sleep_ms(2000);
   
   printf("Slide Switch Reader\n");
   printf("------------------\n");
 
   gpio_init(SWITCH_PIN);
   gpio_set_dir(SWITCH_PIN, GPIO_IN);
   gpio_pull_down(SWITCH_PIN);
     
 
   while (true) {
     // switch state (will be 0 or 1)
     int switch_state = gpio_get(SWITCH_PIN);
     
     // Print the state
     printf("Switch state: %d\n", switch_state);
     
     // Add a delay to avoid flooding the console
     sleep_ms(500);
   }
 }