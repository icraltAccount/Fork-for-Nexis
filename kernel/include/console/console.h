// Copyright (c) 2026 icarotelesdasilva colauzz-coder saintsHr
// Licensed under the MIT License

#pragma once

#include "vga/vga.h"

typedef uint32_t console_str_len_t;

void console_move(vga_coord_t x, vga_coord_t y);
void console_set_color(vga_color_t fg, vga_color_t bg);

void console_clear(void);
void console_write_char(vga_char_t c);
void console_write_string(const vga_char_t* c);
