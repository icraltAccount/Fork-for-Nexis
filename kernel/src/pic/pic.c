#include "../../lib/include/io/io.h"
#include "../../include/pic/pic.h"


#include <stdint.h>

/*
 *
 *  NOTE: were created based on osdev, as per the source: (https://wiki.osdev.org/8259_PIC)
 *
 */

/*
 * ORIGINAL FUNCION:
 *          int pic_init(int offset1, int offset2){ return int_value };
 */

void pic_init(int offset1, int offset2) {


    io_outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);  // starts the initialization sequence (in cascade mode)
    //io_wait();
    io_outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    //io_wait();
    io_outb(PIC1_DATA, offset1);                 // ICW2: Master PIC vector offset
    //io_wait();
    io_outb(PIC2_DATA, offset2);                 // ICW2: Slave PIC vector offset
    //io_wait();
    io_outb(PIC1_DATA, 1 << CASCADE_IRQ);        // ICW3: tell Master PIC that there is a slave PIC at IRQ2
    //io_wait();
    io_outb(PIC2_DATA, CASCADE_IRQ);             // ICW3: tell Slave PIC its cascade identity
    //io_wait();

    io_outb(PIC1_DATA, ICW4_8086);               // ICW4: have the PICs use 8086 mode (and not 8080 mode)
    //io_wait();
    io_outb(PIC2_DATA, ICW4_8086);
    //io_wait();

    // Unmask both PICs.
    io_outb(PIC1_DATA, 0);
    io_outb(PIC2_DATA, 0);

}

void PIC_disable(void) {
    io_outb(PIC1_DATA, 0xff);
    io_outb(PIC2_DATA, 0xff);
}

void IRQ_set_mask(uint8_t IRQline) {
    uint16_t port;
    uint8_t value;

    if(IRQline < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        IRQline -= 8;
    }
    value = io_inb(port) | (1 << IRQline);
    io_outb(port, value);

}
void IRQ_clear_mask(uint8_t IRQline) {
    uint16_t port;
    uint8_t value;

    if(IRQline < 8) {
        port = PIC1_DATA;
    } else {
        port = PIC2_DATA;
        IRQline -= 8;
    }
    value = io_inb(port) & ~(1 << IRQline);
    io_outb(port, value);
}
