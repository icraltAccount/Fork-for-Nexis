// Copyright (c) 2026 icarotelesdasilva colauzz-coder saintsHr
// Licensed under the MIT License

#pragma once

#include <stdint.h>

typedef uint16_t io_port_t;
typedef uint8_t io_value_t;

void io_outb(io_port_t port, io_value_t val);
io_value_t io_inb(io_port_t port);
void io_wait(void);
