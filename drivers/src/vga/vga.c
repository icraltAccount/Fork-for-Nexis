#include "../../include/vga/vga.h"
#include "../../../lib/include/io/io.h"

static volatile vga_cell_t *const framebuffer = (volatile vga_cell_t *)VGA_MEMORY;

vga_attr_t vga_make_attr(vga_color_t fg, vga_color_t bg) {
    return (vga_attr_t)((fg & 0x0F) | ((bg & 0x0F) << 4));
}

vga_cell_t vga_make_cell(vga_char_t c, vga_attr_t attr) {
    return (vga_cell_t)(((vga_cell_t)attr << 8) | (vga_char_t)c);
}

vga_index_t vga_get_index(vga_coord_t x, vga_coord_t y) {
    if (x >= VGA_WIDTH) x = VGA_WIDTH - 1;
    if (y >= VGA_HEIGHT) y = VGA_HEIGHT - 1;
    return (vga_index_t)(y * VGA_WIDTH + x);
}

void vga_set_cell(vga_cell_t cell, vga_index_t index) {
    if (index >= VGA_WIDTH * VGA_HEIGHT) return;
    framebuffer[index] = cell;
}

vga_cell_t vga_get_cell(vga_index_t index) {
    if (index >= VGA_WIDTH * VGA_HEIGHT) return 0;
    return framebuffer[index];
}

void vga_move_cursor(vga_coord_t x, vga_coord_t y) {
    vga_index_t pos = vga_get_index(x, y);

    io_outb(0x3D4, 0x0E);
    io_outb(0x3D5, (pos >> 8) & 0xFF);
    io_outb(0x3D4, 0x0F);
    io_outb(0x3D5, pos & 0xFF);
}
