bits 32
global cpuid

section .text

extern apic_init
extern pic_init

cpuid:

mov eax, 1

cpuid

test edx, (1 << 9)

jz .pic

call apic_init

jmp .done



.pic:

call pic_init



.done:
	ret 




