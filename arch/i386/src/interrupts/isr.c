// Copyright (c) 2026 icarotelesdasilva colauzz-coder saintsHr
// Licensed under the MIT License

#include "interrupts/isr.h"
#include "interrupts/idt.h"
#include "types/types.h"

extern ptr_t isr_stub_table[];

void isr_exception_handler(void) {
    __asm__ __volatile__("cli");
    __asm__ __volatile__("hlt");
}

void isr_install(void) {
    for (ptr_t i = 0; i < 32; i++) {
        idt_set_descriptor(i, (void*)isr_stub_table[i], 0x8E);
    }
}
