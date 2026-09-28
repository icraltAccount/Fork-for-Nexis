#ifndef TLB_H
#define TLB_H

typedef uintptr_t vaddr_t ;  
typedef uintptr_t paddr_t ;  

struct tlb_cache_record_t 
{
   vaddr_t entry_virtual_address ; 
   paddr_t endereço_físico_relevante ; 
   permissões uint16_t ; 
   flags uint16_t ; 
};

struct tlb_cache_record_t hw_tlb [ CPU_MODEL_MAX_TLB_ENTRIES ];  

#endif
