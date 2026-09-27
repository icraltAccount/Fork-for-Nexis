// Copyright (c) 2026 icarotelesdasilva colauzz-coder saintsHr
// Licensed under the MIT License

#include "console/console.h"

#include "interrupts/idt.h"
#include "interrupts/gdt.h"
#include "interrupts/pic.h"
#include "interrupts/interrupts.h"

void kinit() {
    interrupts_disable();

    console_clear();
    gdt_init();
    idt_init();
    pic_enable(0x20, 0x28);

    interrupts_enable();
}

void kmain() {
    kinit();

    console_write_string("Hello Kernel!");

    while(1);
}
