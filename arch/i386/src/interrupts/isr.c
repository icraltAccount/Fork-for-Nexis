// Copyright (c) 2026 icarotelesdasilva colauzz-coder saintsHr
// Licensed under the MIT License

#include "interrupts/isr.h"
#include "interrupts/idt.h"
#include "interrupts/interrupts.h"
#include "types/types.h"
#include "main.h"

extern ptr_t isr_stub_table[];

static const char* exception_messages[32] = {
    "Division By Zero", "Debug", "Non Maskable Interrupt",
    "Breakpoint", "Into Detected Overflow", "Out of Bounds",
    "Invalid Opcode", "No Coprocessor", "Double Fault",
    "Coprocessor Segment Overrun", "Bad TSS", "Segment Not Present",
    "Stack Fault", "General Protection Fault", "Page Fault",
    "Unknown Interrupt", "Coprocessor Fault", "Alignment Check",
    "Machine Check", "Reserved", "Reserved", "Reserved", "Reserved",
    "Reserved", "Reserved", "Reserved", "Reserved", "Reserved",
    "Reserved", "Reserved", "Reserved", "Reserved"
};

void isr_handler(isr_frame_t* frame) {
    interrupts_disable();

    kpanic(exception_messages[frame->vector]);

    while(1) __asm__ __volatile__("hlt");
}

void isr_install(void) {
    for (ptr_t i = 0; i < 32; i++) {
        idt_set_descriptor(i, (void*)isr_stub_table[i], 0x8E);
    }
}
