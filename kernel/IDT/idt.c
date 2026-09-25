#include "../library/types.h"

extern void* ISR_Stub_Table[];
typedef struct{
    uint16_t ISRLow; 
    uint16_t Selector;
    uint8_t Extra; 
    uint8_t Flags; 
    uint16_t ISRHigh; 
} __attribute__((packed)) InterruptDescriptorTable_Struct;

__attribute__((aligned(0x10))) 

InterruptDescriptorTable_Struct IDT[256];

typedef struct{
    uint16_t Limit; 
    uint32_t Base; 
} __attribute__((packed)) InterruptDescriptorTableRegister_Struct;

static InterruptDescriptorTableRegister_Struct IDTR;

__attribute__((noreturn))


void ExceptionHandler(void){
    __asm__ __volatile__("cli; hlt"); 
}

void SetIDTDescriptor(uint8_t Vector, void* ISR, uint8_t Flags){

    IDT[Vector].ISRLow = (uint32_t)ISR & 0xFFFF;
    IDT[Vector].Selector = 0x08;
    IDT[Vector].Flags = Flags;
    IDT[Vector].ISRHigh = (uint32_t)ISR << 16;
    IDT[Vector].Extra = 0;
}

void InitIDT(void){

    IDTR.Base = (uint32_t)&IDT[0]; 
    IDTR.Limit = (uint16_t)sizeof(InterruptDescriptorTable_Struct) * 256 - 1; 

    for(uint32_t i = 0; i < 32; i++){ 
        SetIDTDescriptor(i, ISR_Stub_Table[i], 0x8E);
    }

   __asm__ __volatile__ ("lidt %0" : : "m"(IDTR)); 
    __asm__ __volatile__ ("sti"); 
}
