// Copyright (c) 2026 icarotelesdasilva colauzz-coder saintsHr
// Licensed under the MIT License

#pragma once

#include <stdint.h>

typedef struct {
    uint32_t ds;
    uint32_t edi, esi, ebp, esp_dummy, ebx, edx, ecx, eax;
    uint32_t vector;
    uint32_t error_code;
    uint32_t eip, cs, eflags;
} __attribute__((packed)) isr_frame_t;

void isr_install(void);
void isr_handler(isr_frame_t* frame);
