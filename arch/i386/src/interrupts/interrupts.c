// Copyright (c) 2026 icarotelesdasilva colauzz-coder saintsHr
// Licensed under the MIT License

#include "interrupts/interrupts.h"

void interrupts_enable(void) {
    __asm__ __volatile__("sti");
}

void interrupts_disable(void) {
    __asm__ __volatile__("cli");
}
