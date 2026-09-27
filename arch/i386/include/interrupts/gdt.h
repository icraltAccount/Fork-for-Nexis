// Copyright (c) 2026 icarotelesdasilva colauzz-coder saintsHr
// Licensed under the MIT License

#pragma once

#include <stdint.h>
#include "memory/memory.h"

#define GDT_PRESENT        0x80
#define GDT_NOT_PRESENT    0x00

#define GDT_RING0          0x00
#define GDT_RING1          0x20
#define GDT_RING2          0x40
#define GDT_RING3          0x60

#define GDT_SYSTEM         0x00
#define GDT_CODE_DATA      0x10

#define GDT_CODE           0x08
#define GDT_CODE_READ      0x02
#define GDT_CODE_CONF      0x04
#define GDT_CODE_ACCESSED  0x01

#define GDT_DATA           0x00
#define GDT_DATA_WRITE     0x02
#define GDT_DATA_EXPAND    0x04
#define GDT_DATA_ACCESSED  0x01

#define GDT_GRAN_4K        0x80
#define GDT_SIZE_32        0x40
#define GDT_LONG_MODE      0x20

#define GDT_KERNEL_CODE_FLAGS \
    (GDT_PRESENT | GDT_RING0 | GDT_CODE_DATA | GDT_CODE | GDT_CODE_READ)
#define GDT_KERNEL_DATA_FLAGS \
    (GDT_PRESENT | GDT_RING0 | GDT_CODE_DATA | GDT_DATA | GDT_DATA_WRITE)

#define GDT_USER_CODE_FLAGS \
    (GDT_PRESENT | GDT_RING3 | GDT_CODE_DATA | GDT_CODE | GDT_CODE_READ)
#define GDT_USER_DATA_FLAGS \
    (GDT_PRESENT | GDT_RING3 | GDT_CODE_DATA | GDT_DATA | GDT_DATA_WRITE)

#define GDT_DEFAULT_GRANULARITY \
    (GDT_GRAN_4K | GDT_SIZE_32)

#define GDT_ENTRY_COUNT 5

typedef struct {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t  base_middle;
    uint8_t  access;
    uint8_t  granularity;
    uint8_t  base_high;
} __attribute__((packed)) gdt_entry_t;

typedef struct {
    uint16_t limit;
    ptr_t base;
} __attribute__((packed)) gdt_ptr_t;

void gdt_init(void);
