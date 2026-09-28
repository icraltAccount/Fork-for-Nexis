#define "tlb.h"


/*


*/


int tlb_lookup(vaddr_t v, paddr_t *p)
{
   for (int i=0; i<CPU_MODEL_MAX_TLB_ENTRIES; i++)
   {
      if (hw_tlb[i].flags & TLB_ENTRY_FLAGS_INUSE && hw_tlb[i].entry_virtual_address == v)
      {
         *p = hw_tlb[i].relevant_physical_address;
         return 1;
      };
   };
   return 0;
}




/*

* A processor architecture would normally, then provide an instruction to invalidate TLB entries, either en masse, or one by one, or however the CPU designers decided. Let's try to model a TLB flush

*  An OS would invoke this on our model architecture by doing something like this:

* asm volatile ("TLBFLSH   %0\n\t"::"r" (virtual_address));

*/
