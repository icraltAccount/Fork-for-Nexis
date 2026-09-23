; Copyright (c) 2026 icarotelesdasilva
; Licensed under the MIT License

; NOTE:
;   The code was tested and evaluated on actual hardware.
;   All information was taken from (wiki.osdev.org).

bits 16
org 0x7c00

jmp start

%ifndef TOTAL_SECTORS
%define TOTAL_SECTORS 2
%endif

boot_drive db 0

start:
    cli

    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x9000

    mov [boot_drive], dl

    in al, 0x92
    or al, 2
    and al, 0xFE
    out 0x92, al

    mov ah, 0x41
    mov bx, 0x55AA
    mov dl, [boot_drive]

    int 0x13
    jc chs

    cmp bx, 0xAA55
    jne chs

    test cx, 0x0001
    jz chs

    jmp lba

chs:
    mov ax, 0x1000
    mov es, ax
    xor bx, bx

    mov ah, 0x02
    mov al, TOTAL_SECTORS

    mov ch, 0
    mov cl, 2
    mov dh, 0
    mov dl, [boot_drive]

    int 0x13
    jc disk_error

    jmp loaded

lba:
    mov ax, 0x1000
    mov es, ax
    xor bx, bx

    mov si, dap

    mov word [si + 0], 0x0010

    mov word [si + 2], TOTAL_SECTORS

    mov word [si + 4], 0x0000
    mov word [si + 6], 0x1000

    mov dword [si + 8], 0x00000001
    mov dword [si + 12], 0x00000000

    mov ah, 0x42
    mov dl, [boot_drive]

    int 0x13
    jc disk_error

    jmp loaded

loaded:
    mov ax, 0x1000
    mov es, ax

    cmp word [es:0x0000], 0x4349
    jne signature_error

    jmp 0x1000:0x0002

signature_error:
    mov ax, 0xB800
    mov ds, ax

    mov byte [0x00], 'S'
    mov byte [0x01], 0x0C

    jmp hang

disk_error:
    mov ax, 0xB800
    mov ds, ax

    mov byte [0x00], 'D'
    mov byte [0x01], 0x0C

    jmp hang

hang:
    cli
    .loop:
        hlt
        jmp .loop

dap:
    times 510 - ($ - $$) db 0
    dw 0xAA55
