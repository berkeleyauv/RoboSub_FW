/**
 * Underwater Robotics @ Berkeley
 * 
*/
#include <stdio.h>
#include "pico/stdlib.h"

const uint LED_PIN = 2;

/**
 * \brief Main fucntion
 *
 */
int main() 
{
    stdio_init_all();
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);
    while (true) {
        gpio_put(LED_PIN, 1);
        printf("LED on\n");
        sleep_ms(250);
        gpio_put(LED_PIN, 0);
        printf("LED off\n");
        sleep_ms(250);
    }
    return 0;
}
