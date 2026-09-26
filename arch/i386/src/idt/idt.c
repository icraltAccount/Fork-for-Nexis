#include <stdint.h>
#include "../../include/idt/idt.h"
#include "console/console.h"
/*

    NOTE: THIS SOURCE CODE WAS BASED ON OSDEV.WIKI, LINKS THAT WERE USED: ( https://wiki.osdev.org/Interrupt_Descriptor_Table ) ( https://wiki.osdev.org/Interrupts_Tutorial )

 */

extern void* isr_stub_table[];

typedef struct {
    uint16_t isr_low;
    uint16_t selector;
    uint8_t extra;
    uint8_t flags;
    uint16_t isr_high;
} __attribute__((packed)) idt_struct;
__attribute__((aligned(0x10)))
idt_struct idt[256];

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idtr_struct;
static idtr_struct idtr;

void exception_handler(void) {
    console_write_string("CPU Got Inside An Exception");
    __asm__ __volatile__("cli");
    __asm__ __volatile__("hlt");
}

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags) {
    idt[vector].isr_low = (uint32_t)isr & 0xFFFF;
    idt[vector].selector = 0x08;
    idt[vector].flags = flags;
    idt[vector].isr_high = (uint32_t)isr >> 16;
    idt[vector].extra = 0;
}

void idt_init(void) {
    idtr.base = (uint32_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(idt_struct) * 256 - 1;

    for(uint32_t i = 0; i < 32; i++) {
        idt_set_descriptor(i, isr_stub_table[i], 0x8E);
    }

    __asm__ __volatile__ ("lidt %0" : : "m"(idtr));
    //Add Only When PIC Exists: __asm__ __volatile__ ("sti");
}
