// Copyright (c) 2026 icarotelesdasilva colauzz-coder saintsHr
// Licensed under the MIT License

#include "vga/vga.h"

void kmain() {
    vga_set_cell(
        vga_make_cell(
            'A',
            vga_make_attr(VGA_COLOR_WHITE, VGA_COLOR_BLACK)
        ),
        vga_get_index(0, 0)
    );

    while(1);
}
