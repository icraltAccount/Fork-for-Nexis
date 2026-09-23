ENTRY(_start)

SECTIONS {
    . = 0x100000;

    .text : ALIGN(4) {
        *(.text)
        *(.text.*)
        *(.rodata)
        *(.rodata.*)
    }

    .data : ALIGN(4) {
        *(.data)
        *(.data.*)
    }

    .bss : ALIGN(4) {
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
