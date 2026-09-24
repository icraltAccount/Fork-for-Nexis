; Copyright (c) 2026 icarotelesdasilva
; Licensed under the MIT License

; NOTE:
;   The code was tested and evaluated on actual hardware.
;   All information was taken from (wiki.osdev.org).

bits 16
org 0x10000

dw 0x4349

stage2:
    cli

    lgdt [dword gdt_descriptor]

    mov eax, cr0
    or eax, 1
    mov cr0, eax

    jmp dword 0x08:start_protected_mode

    bits 32

    start_protected_mode:

    mov ax, 0x10

    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    mov esp, 0x90000

    mov esi, 0x10200
    mov edi, 0x100000
    mov ecx, 0x4000
    cld
    rep movsd
    jmp 0x100000

hang:
    cli

    .loop:
        hlt
        jmp .loop

gdt_start:
    dd 0, 0

    dw 0xFFFF, 0x0000
    db 0x00, 10011010b, 11001111b, 0x00

    dw 0xFFFF, 0x0000
    db 0x00, 10010010b, 11001111b, 0x00
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

times 512 - ($ - $$) db 0
