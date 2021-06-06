#include "mbed.h"

#include "F091_override.h"

// Debug
DigitalOut led(PC_13, 1);

// disable HSE in mbed_app.json for these to work
DigitalIn but(PF_1, PullUp);

BufferedSerial pc(PA_9, PA_10, 115200);

FileHandle *mbed::mbed_override_console(int fd) {
    return &pc;
}

// Peripherals
IRQ_CAN can(PA_11, PA_12, 1000000); // workaround for RX Irq to work

PwmOut esc(PB_4);

AnalogIn curr(PA_7);

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
}

int main() {
    esc.period_ms(50);
    esc.pulsewidth_us(1500);

    eventThread.start(callback(&queue, &EventQueue::dispatch_forever));
    can.attach(rxIrq);

    while (true) {
        led = !led;
        float i = (curr.read() - 0.5) * 75;
        printf("Current: %.3f\n", i);
        ThisThread::sleep_for(500ms);
    }
}

