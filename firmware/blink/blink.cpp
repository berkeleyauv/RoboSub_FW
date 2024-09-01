/*
    Underwater Robotcs @ Berkeley. 
*/

#include "stdio.h"
#include "pico/stdlib.h"

#define GPIO_ON 1
#define GPIO_OFF 0

#define LED_PIN 22 //External GPIO Pin. Raspberry PI Pico Internal PIN is LED_PIN = 25 

/*********************************************************************
 * @fn      		  - main()
 *
 * @brief             -
 */
int main() {
    //Intiailize stdio
    stdio_init_all();

    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    while(true) {
        printf("Blinking On!\n");
        gpio_put(LED_PIN, GPIO_ON);
        sleep_ms(2000);
        printf("Blinking Off!\n");
        gpio_put(LED_PIN, GPIO_OFF);
        sleep_ms(2000);
    }

}