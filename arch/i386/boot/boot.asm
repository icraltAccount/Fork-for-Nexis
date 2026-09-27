; Copyright (c) 2026 icarotelesdasilva colauzz-coder saintsHr
; Licensed under the MIT License

MBALIGN     equ 1<<0
MEMINFO     equ 1<<1
FLAGS       equ MBALIGN | MEMINFO
MAGIC       equ 0x1BADB002
CHECKSUM    equ -(MAGIC + FLAGS)

section .multiboot

align 4
    dd MAGIC
    dd FLAGS
    dd CHECKSUM

section .bss

align 16
stack_bottom:
    resb 16384 ; 16 KiB
stack_top:

section .text

global _start
extern kmain

_start:
    cli
    mov esp, stack_top

    push ebx
    push eax
    call kmain

    .hang:
        cli
        hlt
        jmp .hang
