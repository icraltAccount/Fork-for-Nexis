#include "../library/types.h"
extern void* ISR_Stub_Table[];
typedef struct{
    uint16_t ISRLow; //ISR Address
    uint16_t Selector; //Code Segment(CS), 0x08
    uint8_t Extra; //Ignore/0
    uint8_t Flags; //Attributes/Flags
    uint16_t ISRHigh; //ISR Address
} __attribute__((packed)) InterruptDescriptorTable_Struct;
__attribute__((aligned(0x10))) //0x10 -> 16 In Hex
InterruptDescriptorTable_Struct IDT[256];

typedef struct{
    uint16_t Limit; //Size Of The IDT
    uint32_t Base; //The Address That The IDT Starts
} __attribute__((packed)) InterruptDescriptorTableRegister_Struct;
static InterruptDescriptorTableRegister_Struct IDTR;

__attribute__((noreturn))
void ExceptionHandler(void){
    __asm__ __volatile__("cli; hlt"); //Disables All The Interruptions And Stops The Computer(Halt)
}

void SetIDTDescriptor(uint8_t Vector, void* ISR, uint8_t Flags){
    IDT[Vector].ISRLow = (uint32_t)ISR & 0xFFFF;
    IDT[Vector].Selector = 0x08;
    IDT[Vector].Flags = Flags;
    IDT[Vector].ISRHigh = (uint32_t)ISR << 16;
    IDT[Vector].Extra = 0;
}

void InitIDT(void){
    IDTR.Base = (uint32_t*)&IDT[0]; //First Address Of The IDT Is The Base Of The IDT
    IDTR.Limit = (uint16_t)sizeof(InterruptDescriptorTable_Struct) * 256 - 1; //Maximum Size Of The IDT
    for(uint32_t i = 0; i < 32; i++){ //Sets All The 32 First Entries Of The IDT(Exceptions)
        SetIDTDescriptor(i, ISR_Stub_Table[i], 0x8E);
    }
    __asm__ __volatile__ ("lidt %0" : : "m"(&IDTR));
    __asm__ __volatile__ ("sti"); //Gets The Interruptions Back
}
