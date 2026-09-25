; Copyright (c) 2026 icarotelesdasilva
; Licensed under the MIT License

bits 16
org 0x10000

dw 0x4349

MEM_MAP_COUNT equ 0x8000
MEM_MAP_DATA  equ 0x8004

stage2:
    xor ax, ax
    mov es, ax
    mov di, MEM_MAP_DATA
    xor ebp, ebp
    mov edx, 0x534D4150
    xor ebx, ebx

.e820_loop:
    mov eax, 0x0000E820
    mov ecx, 24
    int 0x15
    jc .e820_end

    cmp eax, 0x534D4150
    jne .e820_failed

    mov ecx, [es:di + 8]
    or ecx, [es:di + 12]
    jz .e820_jmp_entry

    inc ebp
    add di, 24

.e820_jmp_entry:
    test ebx, ebx
    jnz .e820_loop
    jmp .e820_failed

.e820_failed:
    xor ebp, ebp

.e820_end:
    mov [MEM_MAP_COUNT], bp

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

