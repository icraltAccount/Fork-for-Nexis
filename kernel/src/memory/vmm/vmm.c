/*
 * WRITTEN BY: nicooolo
 */


/* NOTES FOR icarotelesdasilva:
 *      adiciona o código com comentários lá no "documentation/vmm_c".
 *
 */


/*
 * REALLY IMPORTANT WARNING, PLEASE READ: WHEN PAGING IS DISABLED, WE WRITE THROUGH THE MEMORY DIRECTLY, BUT WHEN WE
 *                                        ACTIVATE PAGING, ALL THE C POINTERS ARE INTERPRETED BY THE CPU AS VIRTUAL
 *                                        ADDRESSES, THE OS WILL END UP IN A PAGE FAULT IN CASE PAGING IS ACTIVATED
 *                                        BEFORE MAPPING THE VMM: WHEN THE CPU TRIES TO READ THE VARIABLE page_table_entry
 *                                        THE CPU WILL END UP THROWING A PAGE FAULT AND BLOCK THE KERNEL FROM CONTINUING
 */


#include "memory/vmm/vmm.h"
#include "memory/pmm/pmm.h"
#include "memory/MMU/tlb.h"

void vmm_map(page_directory_struct* page_directory, uint32_t virtual_address, uint32_t physical_address, uint32_t flags){
    uint32_t page_directory_index = virtual_address >> 22;
    uint32_t page_table_index = (virtual_address >> 12) & 0x3FF;

    physical_address &= 0xFFFFF000;

    pde_t* page_directory_entry = &page_directory->entries[page_directory_index];
    page_table_struct* page_table_entry;

    if(!(*page_directory_entry & VMM_FLAG_PRESENT)){
        uint32_t new_table = (uint32_t)pmm_alloc_page();
        *page_directory_entry = new_table | VMM_FLAG_PRESENT | VMM_FLAG_WRITABLE | VMM_FLAG_USER;
        page_table_entry = (page_table_struct*)new_table;
        for(uint32_t i = 0; i < 1024; i++){
            page_table_entry->entries[i] = 0;
        }
    }else{
        page_table_entry = (page_table_struct*)(*page_directory_entry & 0xFFFFF000);
    }

    page_table_entry->entries[page_table_index] = physical_address | VMM_FLAG_PRESENT | flags;
    tlb_flush_single(virtual_address);
}

void vmm_load_cr3(page_directory_struct* page_directory){
    __asm__ __volatile__("mov %0, %%cr3" : : "r"(page_directory) : "memory");
}

void vmm_enable_paging(){
    /*
     * this part is for icarotelesdasilva
     * message for icarotelesdasilva:
     *      tu vai mudar o bit 31 do registrador cr0, acho que se tu usar o inline assembly tu consegue.
     *
     *      não faz a merda que eu fiz de esquecer de colocar "%%" para usar registradores especiais no inline asm.
     *
     *      cuidado pra não fazer bosta no registrador cr0 pois ele tem várias configurações importantissímas, não faz
     *      merda.
     *
     *      se você leu você é gay.
     */
}

void vmm_init(){
    /*
     * this part is for icarotelesdasilva
     * message for icarotelesdasilva:
     *      pelo amor de deus, lê o warning que deixei lá em cima e inicializa o paging e muda o cr3 no FINAL da função.
     *
     *      não tenho a miníma ideia de como fazer essa função aqui mas acho que tu chama as funções de cima ali e mais
     *      alguma coisa ai, bah notche, bah tardi, bah djiah.
     */
}
