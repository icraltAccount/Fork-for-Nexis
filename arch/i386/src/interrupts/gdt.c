// Copyright (c) 2026 icarotelesdasilva colauzz-coder saintsHr
// Licensed under the MIT License

#include "interrupts/gdt.h"
#include "memory/memory.h"

extern void gdt_flush(ptr_t);

static gdt_entry_t gdt_e[GDT_ENTRY_COUNT];
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
    gdt_p.limit = (sizeof(gdt_entry_t) * GDT_ENTRY_COUNT) - 1;
    gdt_p.base  = (ptr_t)&gdt_e;

    // Null Descriptor
    gdt_set_gate(
        0,
        0,
        0,
        0,
        0
    );

    // Kernel Code Segment
    gdt_set_gate(
        1,
        0,
        0xFFFFFFFF,
        GDT_KERNEL_CODE_FLAGS,
        GDT_DEFAULT_GRANULARITY
    );

    // Kernel Data Segment
    gdt_set_gate(
        2,
        0,
        0xFFFFFFFF,
        GDT_KERNEL_DATA_FLAGS,
        GDT_DEFAULT_GRANULARITY
    );

    // User Code Segment
    gdt_set_gate(
        3,
        0,
        0xFFFFFFFF,
        GDT_USER_CODE_FLAGS,
        GDT_DEFAULT_GRANULARITY
    );

    // User Data Segment
    gdt_set_gate(
        4,
        0,
        0xFFFFFFFF,
        GDT_USER_DATA_FLAGS,
        GDT_DEFAULT_GRANULARITY
    );

    gdt_flush((ptr_t)&gdt_p);
}
