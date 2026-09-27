// Copyright (c) 2026 icarotelesdasilva colauzz-coder saintsHr
// Licensed under the MIT License

#include "interrupts/irq.h"
#include "interrupts/idt.h"
#include "interrupts/pic.h"
#include "io/io.h"

extern ptr_t irq_stub_table[];

void irq_handler(ptr_t irq) {
    if (irq >= 8) {
        io_outb(PIC2_COMMAND, PIC_EOI);
    }

    io_outb(PIC1_COMMAND, PIC_EOI);
}

void irq_install(void) {
    for (ptr_t i = 0; i < 16; i++) {
        idt_set_descriptor(32 + i, (void*)irq_stub_table[i], 0x8E);
    }
}
