// Copyright (c) 2026 icarotelesdasilva colauzz-coder saintsHr
// Licensed under the MIT License

#include "main.h"

#include "console/console.h"

#include "interrupts/idt.h"
#include "interrupts/gdt.h"
#include "interrupts/pic.h"
#include "interrupts/interrupts.h"
#include "vga/vga.h"

void kpanic(const vga_char_t* message) {
    interrupts_disable();
    console_clear();

    console_set_color(VGA_COLOR_LIGHT_RED, VGA_COLOR_BLACK);
    console_move(2, 1);
    console_write_string("Kernel Panic!");

    console_set_color(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    console_move(3, 3);
    console_write_string("Message: ");

    console_set_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    console_write_string(message);

    while(1) __asm__ __volatile__("hlt");
}

void kinit() {
    interrupts_disable();

    console_clear();
    console_move(0, 0);

    gdt_init();
    idt_init();
    pic_enable(0x20, 0x28);

    interrupts_enable();
}

void kmain() {
    kinit();

console_write_string("Hello, Kernel");

    while(1) __asm__ __volatile__("hlt");
}
