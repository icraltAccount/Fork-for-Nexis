#include "../../include/io/io.h"

void io_outb(io_port_t port, io_value_t val) {
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

uint8_t io_inb(io_port_t port) {
    uint8_t value;

    asm volatile("inb %1, %0" : "=a"(value) : "Nd"(port));

    return value;
}
