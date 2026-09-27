// Copyright (c) 2026 icarotelesdasilva colauzz-coder saintsHr
// Licensed under the MIT License

#include "interrupts/idt.h"
#include "interrupts/isr.h"
#include "interrupts/irq.h"

__attribute__((aligned(0x10)))
static idt_entry_t idt[256];
static idt_register_t idtr;

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags) {
    ptr_t addr = (ptr_t)isr;

    idt[vector].offset_low  = addr & 0xFFFF;
    idt[vector].selector    = 0x08;
    idt[vector].zero        = 0;
    idt[vector].flags       = flags;
    idt[vector].offset_high = (addr >> 16) & 0xFFFF;
}

void idt_init(void) {
    idtr.base  = (ptr_t)&idt[0];
    idtr.limit = sizeof(idt_entry_t) * 256 - 1;

    for (ptr_t i = 0; i < 256; i++) {
        idt[i].offset_low  = 0;
        idt[i].selector    = 0;
        idt[i].zero        = 0;
        idt[i].flags       = 0;
        idt[i].offset_high = 0;
    }

    isr_install();
    irq_install();

    __asm__ volatile ("lidt %0" : : "m"(idtr));
}
