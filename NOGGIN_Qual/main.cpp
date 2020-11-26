#include "BufferedSerial.h"
#include "CAN.h"
#include "DigitalIn.h"
#include "DigitalOut.h"
#include "EventQueue.h"
#include "PinNamesTypes.h"
#include "SerialBase.h"
#include "ThisThread.h"
#include "cmsis_os2.h"
#include "mbed.h"

/*
 * NOTE: Made for STM32F091CB
 * FIX: Disable HSE for buttons to work
 * FIX: Remove CAN lock when reading for RX IRQ to work
 * FIX: Enable PA_2 and PA_3 ADC map for current sense to work
 * FIX: Define TARGET_STM32F091RC for USART5 to work
 */

#include "F091_override.h"

// Debug
DigitalOut rgb[3] = {
    DigitalOut(PC_13, 1), 
    DigitalOut(PC_14, 1), 
    DigitalOut(PC_15, 1)
};

// disable HSE in mbed_app.json for these to work
DigitalIn sw1(PF_1, PullUp);
DigitalIn sw2(PF_0, PullUp);

BufferedSerial pc(PA_9, PA_10, 115200);

FileHandle *mbed::mbed_override_console(int fd) {
    return &pc;
}

// Peripherals
IRQ_CAN can(PA_11, PA_12, 1000000); // workaround for RX Irq to work

I2C i2c(PB_7, PB_6);

BufferedSerial uart(PB_3, PB_4, 115200);

PwmOut pwm(PA_4); // also DAC, ADC

AnalogOut dac(PA_5); // also ADC (PWM not available bc Timer 2)

PwmOut mot_in1(PA_6);
PwmOut mot_in2(PA_7);

AnalogIn v_sens_12v(PA_0);
AnalogIn v_sens_5v(PA_1);

// include F091_override.h for these to work
AnalogIn i_sens_12v(PA_2);
AnalogIn i_sens_5v(PA_3);

// CAN RX Irq stuff, needs F091_override.h
Thread eventThread(osPriorityNormal, 1024);
EventQueue queue;

void rxCAN(CANMessage msg) {
    // low speed CAN code here
    printf("rcvd msg! id: %d len: %d rtr: %d ide: %d data: ", msg.id, msg.len, msg.type, msg.format);
    for (int i = 0; i < msg.len; i++) {
        printf("%c", msg.data[i]);
    }
    printf("\n");
}

void rxIrq() {
    CANMessage msg;
    can.read(msg);
    queue.call(&rxCAN, msg);
    // high speed CAN code here
    rgb[0] = !rgb[0];
}

int main()
{
    printf("Starting Qual...\n");

    printf("Press SW1 to continue...\n");
    while (sw1);

    printf("Press SW2 to continue...\n");
    while (sw2);

    printf("Flashing red LED...\n");
    for (int i = 0; i < 8; i++) {
        rgb[0] = !rgb[0];
        ThisThread::sleep_for(25ms);
    }

    printf("Flashing green LED...\n");
    for (int i = 0; i < 8; i++) {
        rgb[1] = !rgb[1];
        ThisThread::sleep_for(25ms);
    }

    printf("Flashing blue LED...\n");
    for (int i = 0; i < 8; i++) {
        rgb[2] = !rgb[2];
        ThisThread::sleep_for(25ms);
    }

    printf("\nTesting I2C at 100kHz...\n");
    i2c.frequency(100000);
    bool found = false;
    for (uint8_t i = 0; i < 128; i++) {
        if (i2c.write(i << 1, NULL, 0) == 0) {
            found = true;
            printf("Found! 0x%X\n", i);
        }
    }
    if (!found) {
        printf("No I2C devices found!\n");
    }

    // bug in targets.json STM32F091xC defined, but not STM32F091RC, which also breaks UART5
    // TODO submit bug report for this
    printf("\nTesting UART (loopback)...\n");
    char str[] = "Hello!";
    printf("Press SW1 to send \"%s\" or press SW2 to skip...\n", str);
    while (sw1 && sw2);
    if (sw2) {
        uart.write(str, strlen(str));
        uart.read(str, strlen(str));
        printf("Received \"%s\"\n", str);
    }
    while (!sw1 || !sw2);
    ThisThread::sleep_for(50ms);

    printf("\nTesting DAC (0.69V)...\n");
    dac.write(0.69 / 3.3);

    printf("\nTesting PWM (Servo)...\n");
    printf("Press SW1 to start or press SW2 to skip...\n");
    pwm.period_ms(50);
    while (sw1 && sw2);
    if (sw2) {
        for (int i = 500; i <= 2500; i += 50) {
            pwm.pulsewidth_us(i);
            ThisThread::sleep_for(50ms);
        }
        for (int i = 2500; i >= 500; i -= 50) {
            pwm.pulsewidth_us(i);
            ThisThread::sleep_for(50ms);
        }
        pwm.pulsewidth_us(1500);
    }
    while (!sw1 || !sw2);
    ThisThread::sleep_for(50ms);

    printf("\nTesting motor at 1kHz PWM...\n");
    printf("Press SW1 to start or press SW2 to skip...\n");
    mot_in1.period_ms(1);
    mot_in2.period_ms(1);
    while (sw1 && sw2);
    if (sw2) {
        printf("Forward full speed!\n");
        mot_in1 = 0;
        mot_in2 = 1;
        ThisThread::sleep_for(500ms);
        printf("Brake!\n");
        mot_in1 = 1;
        mot_in2 = 1;
        ThisThread::sleep_for(250ms);
        printf("Backward full speed!\n");
        mot_in1 = 1;
        mot_in2 = 0;
        ThisThread::sleep_for(500ms);
        printf("Brake!\n");
        mot_in1 = 1;
        mot_in2 = 1;
        ThisThread::sleep_for(250ms);
        printf("Forward quarter speed!\n");
        mot_in1 = 0.75;
        mot_in2 = 1;
        ThisThread::sleep_for(500ms);
        printf("Coast!\n");
        mot_in1 = 0;
        mot_in2 = 0;
        ThisThread::sleep_for(250ms);
        printf("Backward quarter speed!\n");
        mot_in1 = 1;
        mot_in2 = 0.75;
        ThisThread::sleep_for(500ms);
        printf("Coast!\n");
        mot_in1 = 0;
        mot_in2 = 0;
        ThisThread::sleep_for(250ms);
    }
    while (!sw1 || !sw2);
    ThisThread::sleep_for(50ms);

    printf("\nMeasuring rail voltages...\n");
    v_sens_12v.set_reference_voltage(36300.0);
    v_sens_5v.set_reference_voltage(18810.0);
    printf("5v: %d mV\n", (int) v_sens_5v.read_voltage());
    printf("12v: %d mV\n", (int) v_sens_12v.read_voltage());

    printf("\nMeasuring currents...\n");
    printf("5v: %d mA\n", (int) ((3300.0 * i_sens_5v.read() - 1500.0) / 200.0 * 1000.0));
    printf("12v: %d mA\n", (int) ((3300.0 * i_sens_12v.read() - 1500.0) / 200.0 * 1000.0));

    printf("\nTesting CAN at 1Mbps...\n");
    printf("Press SW1 to send \"%s\" using ID 69 or press SW2 to skip...\n", str);
    while (sw1 && sw2);
    if (sw2) {
        can.write(CANMessage(69, str, strlen(str)));
    }
    while (!sw1 || !sw2);
    ThisThread::sleep_for(50ms);

    printf("Attaching IRQ listener to CAN...\n");
    eventThread.start(callback(&queue, &EventQueue::dispatch_forever));
    can.attach(rxIrq);

    printf("\nQual finished!\n\n");
    for (int i = 0; i < 8; i++) {
        rgb[0] = !rgb[0];
        rgb[1] = !rgb[1];
        rgb[2] = !rgb[2];
        ThisThread::sleep_for(50ms);
    }

    // eventThread.join();
    char c;
    while (true) {
        // rgb[2] = !rgb[2];
        c++;
        // can.write(CANMessage(69, (char*) &c, 8, CANData, CANExtended));
        ThisThread::sleep_for(250ms);
    }
}

