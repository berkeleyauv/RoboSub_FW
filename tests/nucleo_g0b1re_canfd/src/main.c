#include <zephyr.h>
#include <drivers/gpio.h>

const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);

int main() {
	gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE);

	printk("Hello world!\r\n");

	while (1) {
		gpio_pin_toggle_dt(&led);
		k_msleep(1000);
	}
}
