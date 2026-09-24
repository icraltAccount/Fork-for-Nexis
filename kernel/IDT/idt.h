#ifndef IDT_H
#define IDT_H
void SetIDTDescriptor(uint8_t Vector, void* ISR, uint8_t Flags);
void ExceptionHandler(void);
void InitIDT(void);
#endif
