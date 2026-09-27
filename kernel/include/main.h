#pragma once

#include "vga/vga.h"
#include <stdint.h>

typedef uint32_t magic_t;

void kpanic(const vga_char_t* message);
