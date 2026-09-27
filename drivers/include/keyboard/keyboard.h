// Copyright (c) 2026 icarotelesdasilva colauzz-coder saintsHr
// Licensed under the MIT License

#pragma once

#include <stdint.h>
#include <stdbool.h>

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64
#define KEYBOARD_BUFFER_SIZE 256

#define SC_LSHIFT 0x2A
#define SC_RSHIFT 0x36
#define SC_LSHIFT_REL 0xAA
#define SC_RSHIFT_REL 0xB6
#define SC_CTRL 0x1D
#define SC_CTRL_REL 0x9D
#define SC_ALT 0x38
#define SC_ALT_REL 0xB8
#define SC_CAPSLOCK 0x3A

typedef char keyboard_char_t;
typedef uint8_t keyboard_scancode_t;
typedef uint8_t keyboard_buffer_count_t;

void keyboard_init(void);
void keyboard_handler(void);
bool keyboard_get_char(keyboard_char_t *out);
