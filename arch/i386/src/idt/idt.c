#include <stdint.h>
#include "../../include/idt/idt.h"

extern void* isr_stub_table[];
static idt_reg_t idtr;
__attribute__((aligned(0x10))) idt_t idt[256];

__attribute__((noreturn))
void exception_handler(void) {
    __asm__ __volatile__("cli");
    while (1) __asm__ __volatile__("hlt");
}

void idt_set_descriptor(uint8_t vector, void *isr, uint8_t flags) {
    idt[vector].isr_low = (uint32_t)isr & 0xFFFF;
    idt[vector].selector = 0x08;
    idt[vector].flags = flags;
    idt[vector].isr_high = (uint32_t)isr << 16;
    idt[vector].extra = 0;
}

void idt_init(void) {
    idtr.base = (uint32_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(idt_t) * 256 - 1;

    for(uint32_t i = 0; i < 32; i++) {
        idt_set_descriptor(i, isr_stub_table[i], 0x8E);
    }

    __asm__ __volatile__ ("lidt %0" : : "m"(idtr));
    __asm__ __volatile__ ("sti");
}
