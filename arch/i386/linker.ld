/* Copyright (c) 2026 icarotelesdasilva colauzz-coder saintsHr */
/* Licensed under the MIT License */

ENTRY(_start)

SECTIONS {
    . = 1M;

    .multiboot : ALIGN(4K) {
        *(.multiboot)
        *(.multiboot.*)
    }

    .text : ALIGN(4K) {
        *(.text)
        *(.text.*)
    }

    .rodata : ALIGN(4K) {
        *(.rodata)
        *(.rodata.*)
    }

    .data : ALIGN(4K) {
        *(.data)
        *(.data.*)
    }

    .bss : ALIGN(4K) {
        *(.bss)
        *(.bss.*)
        *(COMMON)
    }

    /DISCARD/ : {
        *(.comment)
        *(.note*)
        *(.eh_frame*)
    }
}
