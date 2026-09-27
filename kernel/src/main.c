// Copyright (c) 2026 icarotelesdasilva colauzz-coder saintsHr
// Licensed under the MIT License

#include "main.h"

#include "console/console.h"
#include "vga/vga.h"
#include "keyboard/keyboard.h"
#include "memory/pmm/pmm.h"

#include "interrupts/idt.h"
#include "interrupts/gdt.h"
#include "interrupts/pic.h"
#include "interrupts/irq.h"
#include "interrupts/interrupts.h"


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

bool kinit(magic_t magic, mbi_t *mbi) {
    interrupts_disable();

    if (magic != 0x2BADB002) kpanic("Invalid magic number.");

    console_clear();
    console_move(0, 0);

    gdt_init();
    idt_init();
    pic_init(0x20, 0x28);
    pmm_init(mbi);

    pic_enable();

    keyboard_init();
    irq_register(1, keyboard_handler);

    interrupts_enable();

    return true;
}

void kmain(magic_t magic, mbi_t *mbi) {
    if (!kinit(magic, mbi)) return;
    while(1) __asm__ __volatile__("hlt");
}
