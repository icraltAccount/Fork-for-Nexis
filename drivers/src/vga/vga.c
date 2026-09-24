#include "vga/vga.h"

static volatile vga_cell_t *const framebuffer = (volatile vga_cell_t *)VGA_MEMORY;

vga_attr_t vga_make_attr(vga_color_t fg, vga_color_t bg) {
    return (vga_attr_t)(fg | (bg << 4));
}

vga_cell_t vga_make_cell(vga_char_t c, vga_attr_t attr) {
    return (vga_cell_t)((uint16_t)attr << 8 | (uint8_t)c);
}

vga_coord_t vga_get_index(vga_coord_t x, vga_coord_t y) {
    return (vga_coord_t)(y * VGA_WIDTH + x);
}

void vga_set_cell(vga_cell_t cell, vga_coord_t index) {
    framebuffer[index] = cell;
}

vga_cell_t vga_get_cell(vga_coord_t index) {
    return framebuffer[index];
}
