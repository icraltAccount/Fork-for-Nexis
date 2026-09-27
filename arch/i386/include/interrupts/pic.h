// Copyright (c) 2026 icarotelesdasilva colauzz-coder saintsHr
// Licensed under the MIT License

#pragma once

#include <stdint.h>
#include "io/io.h"

#define PIC1 0x20
#define PIC2 0xA0

#define PIC1_COMMAND PIC1
#define PIC1_DATA (PIC1+1)

#define PIC2_COMMAND PIC2
#define PIC2_DATA (PIC2+1)

#define PIC_EOI 0x20

#define ICW1_ICW4 0x01
#define ICW1_SINGLE 0x02
#define ICW1_INTERVAL4 0x04
#define ICW1_LEVEL 0x08
#define ICW1_INIT 0x10

#define ICW4_8086 0x01
#define ICW4_AUTO 0x02
#define ICW4_BUF_SLAVE 0x08
#define ICW4_BUF_MASTER 0x0C
#define ICW4_SFNM 0x10

#define CASCADE_IRQ 2

#define PIC_IRQ_TIMER (1 << 0)
#define PIC_IRQ_KEYBOARD (1 << 1)
#define PIC_IRQ_CASCADE (1 << 2)
#define PIC_IRQ_COM2 (1 << 3)
#define PIC_IRQ_COM1 (1 << 4)
#define PIC_IRQ_LPT2 (1 << 5)
#define PIC_IRQ_FLOPPY (1 << 6)
#define PIC_IRQ_LPT1 (1 << 7)

#define PIC_IRQ_RTC (1 << 8)
#define PIC_IRQ_ACPI (1 << 9)
#define PIC_IRQ_IRQ10 (1 << 10)
#define PIC_IRQ_IRQ11 (1 << 11)
#define PIC_IRQ_MOUSE (1 << 12)
#define PIC_IRQ_FPU (1 << 13)
#define PIC_IRQ_PRIMARY_ATA (1 << 14)
#define PIC_IRQ_SECONDARY_ATA (1 << 15)

void pic_init(io_value_t offset_1, io_value_t offset_2);

void pic_enable(void);
void pic_disable(void);

void irq_set_mask(uint8_t irq_line);
void irq_clear_mask(uint8_t irq_line);
