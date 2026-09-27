// Copyright (c) 2026 icarotelesdasilva colauzz-coder saintsHr
// Licensed under the MIT License

#include "interrupts/gdt.h"
#include "types/types.h"

extern void gdt_flush(ptr_t);

static gdt_entry_t gdt_e[5];
static gdt_ptr_t gdt_p;

static void gdt_set_gate(
    int num, ptr_t base, ptr_t limit,
    uint8_t access, uint8_t gran
) {
    gdt_e[num].base_low    = base & 0xFFFF;
    gdt_e[num].base_middle = (base >> 16) & 0xFF;
    gdt_e[num].base_high   = (base >> 24) & 0xFF;

    gdt_e[num].limit_low   = limit & 0xFFFF;
    gdt_e[num].granularity = (limit >> 16) & 0x0F;

    gdt_e[num].granularity |= gran & 0xF0;
    gdt_e[num].access = access;
}

void gdt_init(void) {
    gdt_p.limit = (sizeof(gdt_entry_t) * 5) - 1;
    gdt_p.base  = (ptr_t)&gdt_e;

    gdt_set_gate(0, 0, 0, 0, 0);
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    gdt_flush((ptr_t)&gdt_p);
}
