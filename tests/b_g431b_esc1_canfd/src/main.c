#include <zephyr.h>
#include <drivers/gpio.h>
#include <drivers/can.h>

const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);

const struct device *can1 = DEVICE_DT_GET(DT_NODELABEL(can1));

const struct zcan_filter can_filter = {
	.id_type = CAN_STANDARD_IDENTIFIER,
	.rtr_mask = 0,
	.id_mask = 0
};

CAN_DEFINE_MSGQ(can_msgq, 16);

int main() {
	gpio_pin_configure_dt(&led, GPIO_OUTPUT_INACTIVE);

	can_set_mode(can1, CAN_LOOPBACK_MODE);
	can_set_bitrate(can1, 1000000, 8000000);
	can_attach_msgq(can1, &can_msgq, &can_filter);

	struct zcan_frame txmsg = {
		.id = 0x69,
		.id_type = CAN_STANDARD_IDENTIFIER,
		.rtr = CAN_DATAFRAME,
		.dlc = 1,
		.fd = true,
		.brs = true
	};

	printk("Hello world!\r\n");
	while (1) {
		printk("hi %d\r\n", txmsg.data[0]++);
		can_send(can1, &txmsg, K_FOREVER, NULL, NULL);

		struct zcan_frame rxmsg;
		k_msgq_get(&can_msgq, &rxmsg, K_FOREVER);
		printk("bye %d\r\n", rxmsg.data[0]);

		gpio_pin_toggle_dt(&led);
		k_msleep(1000);
	}
}
