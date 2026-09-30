;
; WRITTEN BY: nicooolo
;
BITS 32
global timer_handler
extern scheduler
timer_handler:
    pusha ;stores all the registers, including the eip, eflags and cs(code segment)
    push ds ;stores the data segment
    mov ax, 0x10 ;passes the value 0x10(16) to all the segments that exist for security
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    push esp ;saves the esp in the stack
    call scheduler ;calls the scheduler
    add esp, 4 ;clears the parameter that we pushed
    mov esp, eax

    mov al, 0x20
    out 0x20, al

    pop ds
    popa

    iret
