// Copyright (c) 2026 icarotelesdasilva colauzz-coder saintsHr
// Licensed under the MIT License

#include "interrupts/pic.h"
#include "io/io.h"
#include <stdint.h>

void pic_init(io_value_t offset_1, io_value_t offset_2) {
    io_outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    io_outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    io_wait();
    io_outb(PIC1_DATA, offset_1);
    io_wait();
    io_outb(PIC2_DATA, offset_2);
    io_wait();
    io_outb(PIC1_DATA, 1 << CASCADE_IRQ);
    io_wait();
    io_outb(PIC2_DATA, CASCADE_IRQ);
    io_wait();

    io_outb(PIC1_DATA, ICW4_8086);
    io_wait();
    io_outb(PIC2_DATA, ICW4_8086);
    io_wait();
}

void pic_enable(void) {
    io_outb(PIC1_DATA, 0x00);
    io_outb(PIC2_DATA, 0x00);
}

void pic_disable(void) {
    io_outb(PIC1_DATA, 0xFF);
    io_outb(PIC2_DATA, 0xFF);
}

void irq_set_mask(uint8_t irq_line) {
    io_port_t port;
    io_value_t value;

    if(irq_line < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        irq_line -= 8;
    }

    value = io_inb(port) | (1 << irq_line);
    io_outb(port, value);
}

void irq_clear_mask(uint8_t irq_line) {
    io_port_t port;
    io_value_t value;

    if(irq_line < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        irq_line -= 8;
    }

    value = io_inb(port) & ~(1 << irq_line);
    io_outb(port, value);
}
