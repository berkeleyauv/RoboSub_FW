/**
 * Underwater Robotics @ Berkeley
 * 
  Raspberry Pi Pico SDK PWM Example

  Credits: https://wokwi.com/projects/326847710095213139

  Generates two 250khZ PWM signal (1 MHz clock, 4 cycle period) on pins 0, 1

  Use the logic analyzer to view the signals: https://docs.wokwi.com/guides/logic-analyzer
*/

#include "pico/stdlib.h"
#include "hardware/pwm.h"

int main() {
  // Tell GPIO 0 and 1 they are allocated to the PWM
  gpio_set_function(0, GPIO_FUNC_PWM);
  gpio_set_function(1, GPIO_FUNC_PWM);

  // Find out which PWM slice is connected to GPIO 0 (it's slice 0)
  uint slice_num = pwm_gpio_to_slice_num(0);

  pwm_set_clkdiv(slice_num, 125); // pwm clock should now be running at 1MHz

  // Set period of 4 cycles (0 to 3 inclusive)
  pwm_set_wrap(slice_num, 3);
  // Set channel A output high for one cycle before dropping
  pwm_set_chan_level(slice_num, PWM_CHAN_A, 1);
  // Set initial B output high for three cycles before dropping
  pwm_set_chan_level(slice_num, PWM_CHAN_B, 3);
  // Set the PWM running
  pwm_set_enabled(slice_num, true);

  // Note we could also use pwm_set_gpio_level(gpio, x) which looks up the
  // correct slice and channel for a given GPIO.
  while (1) {
    sleep_ms(250);
  }
}
