#ifndef TLB_H
#define TLB_H


#include <stdint.h>


void tlb_flush_single(uintptr_t virtual_address);
void tlb_flush_all(void);

#endif
