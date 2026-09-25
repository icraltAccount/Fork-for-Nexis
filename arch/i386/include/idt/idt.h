#pragma once

#include <stdint.h>

typedef struct {
    uint16_t isr_low;
    uint16_t selector;
    uint8_t extra;
    uint8_t flags;
    uint16_t isr_high;
} __attribute__((packed))
idt_t;

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed))
idt_reg_t;

void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags);
void idt_exception_handler(void);
void idt_init(void);
