; Copyright (c) 2026 icarotelesdasilva colauzz-coder saintsHr
; Licensed under the MIT License

global irq_stub_table

extern irq_handler

section .data

irq_stub_table:
    dd irq_stub_0
    dd irq_stub_1
    dd irq_stub_2
    dd irq_stub_3
    dd irq_stub_4
    dd irq_stub_5
    dd irq_stub_6
    dd irq_stub_7
    dd irq_stub_8
    dd irq_stub_9
    dd irq_stub_10
    dd irq_stub_11
    dd irq_stub_12
    dd irq_stub_13
    dd irq_stub_14
    dd irq_stub_15

section .text

%macro IRQ 2
irq_stub_%1:
    pusha
    push %2
    call irq_handler
    add esp, 4
    popa
    iret
%endmacro

IRQ 0, 0
IRQ 1, 1
IRQ 2, 2
IRQ 3, 3
IRQ 4, 4
IRQ 5, 5
IRQ 6, 6
IRQ 7, 7
IRQ 8, 8
IRQ 9, 9
IRQ 10, 10
IRQ 11, 11
IRQ 12, 12
IRQ 13, 13
IRQ 14, 14
IRQ 15, 15
