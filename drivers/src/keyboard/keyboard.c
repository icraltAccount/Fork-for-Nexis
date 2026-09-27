// Copyright (c) 2026 icarotelesdasilva colauzz-coder saintsHr
// Licensed under the MIT License

#include "keyboard/keyboard.h"
#include "io/io.h"

static const keyboard_char_t scancode_lower[128] = {
    0,  27, '1','2','3','4','5','6','7','8','9','0','-','=','\b',
    '\t','q','w','e','r','t','y','u','i','o','p','[',']','\n',
    0,
    'a','s','d','f','g','h','j','k','l',';','\'','`',
    0,
    '\\','z','x','c','v','b','n','m',',','.','/',
    0,
    '*',
    0,
    ' ',
    0,
};

static const keyboard_char_t scancode_upper[128] = {
    0,  27, '!','@','#','$','%','^','&','*','(',')','_','+','\b',
    '\t','Q','W','E','R','T','Y','U','I','O','P','{','}','\n',
    0,
    'A','S','D','F','G','H','J','K','L',':','"','~',
    0,
    '|','Z','X','C','V','B','N','M','<','>','?',
    0,
    '*',
    0,
    ' ',
    0,
};

static bool shift_pressed = false;
static bool ctrl_pressed = false;
static bool alt_pressed = false;
static bool caps_pressed = false;

static keyboard_char_t buffer[KEYBOARD_BUFFER_SIZE];
static keyboard_buffer_count_t buffer_head = 0;
static keyboard_buffer_count_t buffer_tail = 0;

static void buffer_push(keyboard_char_t c) {
    uint8_t next = (buffer_head + 1) % KEYBOARD_BUFFER_SIZE;

    if (next != buffer_tail) {
        buffer[buffer_head] = c;
        buffer_head = next;
    }
}

bool keyboard_get_char(keyboard_char_t *out) {
    if (buffer_tail == buffer_head) return false;
    *out = buffer[buffer_tail];
    buffer_tail = (buffer_tail + 1) % KEYBOARD_BUFFER_SIZE;
    return true;
}

void keyboard_init(void) {
    buffer_head = 0;
    buffer_tail = 0;

    shift_pressed = false;
    ctrl_pressed = false;
    alt_pressed = false;
    caps_pressed = false;
}

void keyboard_handler(void) {
    keyboard_scancode_t scancode = io_inb(KEYBOARD_DATA_PORT);

    switch (scancode) {
        case SC_LSHIFT:
        case SC_RSHIFT:
            shift_pressed = true;
            return;
        case SC_LSHIFT_REL:
        case SC_RSHIFT_REL:
            shift_pressed = false;
            return;
        case SC_CTRL:
            ctrl_pressed = true;
            return;
        case SC_CTRL_REL:
            ctrl_pressed = false;
            return;
        case SC_ALT:
            alt_pressed = true;
            return;
        case SC_ALT_REL:
            alt_pressed = false;
            return;
        case SC_CAPSLOCK:
            caps_pressed = !caps_pressed;
            return;
    }

    if (scancode & 0x80) return;
    if (scancode >= 128) return;

    keyboard_char_t c;
    bool use_shift = shift_pressed ^ caps_pressed;

    if (scancode_lower[scancode] >= 'a' && scancode_lower[scancode] <= 'z') {
        c = use_shift ? scancode_upper[scancode] : scancode_lower[scancode];
    } else {
        c = shift_pressed ? scancode_upper[scancode] : scancode_lower[scancode];
    }

    if (c != 0) {
        buffer_push(c);
    }
}
