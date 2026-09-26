// Copyright (c) 2026 icarotelesdasilva colauzz-coder saintsHr
// Licensed under the MIT License

#include "../../drivers/include/vga/vga.h"
#include "../../arch/i386/include/idt/idt.h"
void kmain() {
    vga_set_cell(
        vga_make_cell(
            '#',
            vga_make_attr(VGA_COLOR_LIGHT_RED, VGA_COLOR_BLACK)
        ),
        vga_get_index(39, 12)
    );
    idt_init();
    while(1);
}
