/*
 * WARNING: types like pte_t and pde_t should NOT be removed, please don't remove them in the code
 * WRITTEN BY: nicooolo
 */
#ifndef VMM_H
#define VMM_H
#include <stdint.h>
#define VMM_FLAG_PRESENT 0x01 //if the real physical RAM exists/is present, it is represented by 0x01, 0000 0001 in binary, 1 = present, 0 = it's not present
#define VMM_FLAG_WRITABLE 0x02 //if you can write to that memory, it is represented my 0x02, 0000 0010 in binary, 1 = read/write, 0 = read only
#define VMM_FLAG_USER 0x04 //who can access that RAM, it is represented by 0x04, 0000 0100 in binary, 1 = user(ring 3), 0 = kernel(ring 0)
typedef uint32_t pte_t; //the page table entry
typedef uint32_t pde_t; //the page directory entry
typedef struct{ //the page table
    pte_t entries[1024]; //the page table 1024 entries
}__attribute__((aligned(4096))) page_table_struct; //says to gcc to make the structure start with a multiple of 4096, it is obbligatory since the last 12 bits of an address that is a multiple of 4096 are always zeroes, ex: 0x00100000, basically we need that to ignore those 12 zero bits to put the flags in it

typedef struct{ //the page directory
    pde_t entries[1024]; //the page directory 1024 entries
}__attribute__((aligned(4096))) page_directory_struct; //says to gcc to make the structure start with a multiple of 4096

void vmm_map(page_directory_struct* page_directory, uint32_t virtual_address, uint32_t physical_address, uint32_t flags);
void vmm_load_cr3(page_directory_struct* page_directory);

void vmm_init(void);
#endif
