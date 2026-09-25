#pragma once

#include <stdint.h>

typedef uint16_t io_port_t;
typedef uint8_t io_value_t;

void io_outb(io_port_t port, io_value_t val);
uint8_t io_inb(io_port_t port);
