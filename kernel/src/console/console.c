#include "console/console.h"
#include "vga/vga.h"

static vga_coord_t console_x = 0;
static vga_coord_t console_y = 0;

static vga_color_t console_fg = VGA_COLOR_LIGHT_GREY;
static vga_color_t console_bg = VGA_COLOR_BLACK;

void console_move(vga_coord_t x, vga_coord_t y) {
    console_x = x;
    console_y = y;

    vga_move_cursor(vga_get_index(x, y));
}

void console_set_color(vga_color_t fg, vga_color_t bg) {
    console_fg = fg;
    console_bg = bg;
}

void console_write_char(vga_char_t c) {
    vga_set_cell(
        vga_make_cell(c, vga_make_attr(console_fg, console_bg)),
        vga_get_index(console_x, console_y)
    );

    if (console_x >= VGA_WIDTH) {
        console_x = 0;
        console_y++;
    } else {
        console_x++;
    }

    console_move(console_x, console_y);
}


void console_clear(void) {
    for (vga_coord_t y = 0; y < VGA_HEIGHT; y++) {
        for (vga_coord_t x = 0; x < VGA_WIDTH; x++) {
            vga_set_cell(
                vga_make_cell(' ', vga_make_attr(console_fg, console_bg)),
                vga_get_index(x, y)
            );
        }
    }
}
