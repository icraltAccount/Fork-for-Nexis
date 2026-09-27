#include "memory/pmm/pmm.h"
#include "main.h"
#include <stdint.h>

usize_t pmm_total_memory = 0;
usize_t pmm_used_memory = 0;
usize_t pmm_max_frames = 0;

ptr_t *pmm_bitmap = 0;

extern ptr_t _kernel_start;
extern ptr_t _kernel_end;

void pmm_init(mbi_t *mbd){
    if(!(mbd->flags & (1 << 6))){
        kpanic("Invalid memory map.");
        return;
    };

    mmap_t *map_start = (mmap_t *)mbd->map_address;
    ptr_t map_end = mbd->map_address + mbd->map_length;

    while((ptr_t)map_start < map_end){
        if(map_start->type == 1){
            ptr_t last_byte = map_start->address + map_start->length;

            if(last_byte > pmm_total_memory){
                pmm_total_memory = last_byte;
            }
        }

        map_start = (mmap_t *)((ptr_t)map_start + map_start->size + sizeof(ptr_t));
    }

    pmm_max_frames = pmm_total_memory / PAGE_SIZE;
    usize_t bitmap_size = pmm_max_frames / 8;
    pmm_bitmap = (ptr_t *)&_kernel_end;

    for(usize_t i = 0; i < bitmap_size / 4; i++){
        pmm_bitmap[i] = 0xFFFFFFFF;
    }

    pmm_used_memory = pmm_total_memory;
    map_start = (mmap_t *)mbd->map_address;

    while((ptr_t)map_start < map_end){
        if(map_start->type == 1){
            ptr_t start_frame = map_start->address / PAGE_SIZE;
            usize_t total_frames = map_start->length / PAGE_SIZE;
            for(usize_t i = 0; i < total_frames; i++){
                PMM_BITMAP_CLEAR(start_frame + i);
                if(pmm_used_memory >= PAGE_SIZE){
                    pmm_used_memory-= PAGE_SIZE;
                }
            }
        }

        map_start = (mmap_t *)((ptr_t)map_start + map_start->size + sizeof(ptr_t));
    }

    ptr_t kernel_start_frame = _kernel_start / PAGE_SIZE;
    ptr_t kernel_end_frame = (ptr_t)&_kernel_end / PAGE_SIZE;

    for(usize_t i = 0; i < kernel_end_frame; i++){
        PMM_BITMAP_SET(i);
        pmm_used_memory += PAGE_SIZE;
    }

    ptr_t bitmap_start_frame = (ptr_t)pmm_bitmap / PAGE_SIZE;
    ptr_t bitmap_end_frame = ((ptr_t)pmm_bitmap + bitmap_size) / PAGE_SIZE;

    for (usize_t i = bitmap_start_frame; i <= bitmap_end_frame; i++) {
        PMM_BITMAP_SET(i);
        pmm_used_memory += PAGE_SIZE;
    }
}

void *pmm_alloc_page(){
    if(pmm_used_memory >= pmm_total_memory){
        kpanic("Tried to allocate memory that is not avaible.");
        return 0;
    }

    usize_t total = pmm_max_frames / 32;

    for(usize_t i = 0; i < total; i++){
        if(pmm_bitmap[i] != 0xFFFFFFFF){
            for(usize_t bit = 0; bit < 32; bit++){
                if(!(pmm_bitmap[i] & (1 << bit))){
                    usize_t frame = (i * 32) + bit;
                    PMM_BITMAP_SET(frame);
                    pmm_used_memory += PAGE_SIZE;
                    return (void *)(frame * PAGE_SIZE);
                }
            }
        }
    }

    return 0;
}

void pmm_free_page(void *address){
    usize_t frame = (ptr_t)address / PAGE_SIZE;

    if (frame >= pmm_max_frames) {
        return;
    }

    PMM_BITMAP_CLEAR(frame);

    if (pmm_used_memory >= PAGE_SIZE) {
        pmm_used_memory -= PAGE_SIZE;
    }
}
