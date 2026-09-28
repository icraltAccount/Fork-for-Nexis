/*
 * WRITTEN BY: icarotelesdasilva
 */

#include "memory/MMU/tlb.h"
#include <stdint.h>
/*
* All files were sourced specifically from osdev.org, from the learning resource at  (https://wiki.osdev.org/Memory_Management_Unit#Translation)
*/

void tlb_flush_single(uint32_t virtual_address) {
    __asm__ __volatile__("invlpg (%0)" :: "r" (virtual_address) : "memory");
}



/*

* A processor architecture would normally, then provide an instruction to invalidate TLB entries, either en masse, or one by one, or however the CPU designers decided. Let's try to model a TLB flush

*  An OS would invoke this on our model architecture by doing something like this:

* asm volatile ("TLBFLSH   %0\n\t"::"r" (virtual_address));

*/
