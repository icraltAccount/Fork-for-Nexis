// Copyright (c) 2026 icarotelesdasilva colauzz-coder saintsHr
// Licensed under the MIT License

#pragma once

#include <stdint.h>
#include "types/types.h"

typedef void (*irq_handler_t)(void);
typedef uint8_t irq_num_t;

void irq_install(void);
void irq_handler(ptr_t irq);
void irq_register(irq_num_t irq, irq_handler_t handler);
