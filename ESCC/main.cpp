#include "mbed.h"

#include "F091_override.h"

#define ID 69

// Debug
DigitalOut led(PC_13);

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
    if (msg.id == ID) {
        // TODO add command to reinit esc
        if (msg.len == 2) {
            uint16_t c = msg.data[1] << 8 | msg.data[0]; // little endian
            esc.pulsewidth_us(c);
        }
    }
}

void rxIrq() {
    CANMessage msg;
    can.read(msg);
    queue.call(&rxCAN, msg);
}

int main() {
    esc.period_ms(50);
    esc.pulsewidth_us(1500);

    // TODO init the esc

    eventThread.start(callback(&queue, &EventQueue::dispatch_forever));
    can.attach(rxIrq);

    while (true) {
        float i = (curr.read() - 0.5) * 75;
        printf("%.3f\n", i);
        ThisThread::sleep_for(50ms);
    }
}

