#include "../../include/pmm/pmm.h"
#include <stdint.h>
#include "console/console.h"
uint32_t memory_size = 0; //the amount of RAM memory that exists
uint32_t used_memory = 0; //the amount of used and not avaible memory
uint32_t max_frames = 0; //the amount of frames that exist
uint32_t* bitmap = 0; //we still don't know the size of the memory so we can't separate it into Bits as an array, so it's a null pointer
extern uint32_t _kernel_end; //created by the linker
void pmm_init(info_struct* mbd){
    if(!(mbd->flags & (1 << 6))){ //checks if grub could read the memory map
        console_write_string("[ error ] grub couldn't read the memory map, kernel can not continue without knowing where theres RAM");
        return;
    }else{
        console_write_string("[ success ] grub read the memory map");
    }

    memory_map_struct* map_start = (memory_map_struct*)mbd->map_address; //points to the start of the memory map

    uint32_t map_end = mbd->map_address + mbd->map_length; //start + size = last element of the map

    while((uint32_t)map_start < map_end){
        if(map_start->type == 1){ //1 means usable RAM
            uint32_t last_byte = map_start->address + map_start->length; //returns the address of the last byte of that region in RAM
            if(last_byte > memory_size){
                memory_size = last_byte;
            }
        }
        map_start = (memory_map_struct*)((uint32_t)map_start + map_start->size + sizeof(uint32_t)); //the jump can't count the first piece, so we can't use (uint32_t)map_start + map_start->size
    }

    max_frames = memory_size / PAGE_MAX; //gets the amount of frames after getting the definitive amount of memory
    uint32_t bitmap_size = max_frames / 8;
    bitmap = (uint32_t*)&_kernel_end;

    for(uint32_t i = 0; i < bitmap_size / 4; i++){
        bitmap[i] = 0xFFFFFFFF; //makes all the bits turn to 0, makes everything become occupied
    }

    used_memory = memory_size; //RAM is 100% occupied
    map_start = (memory_map_struct*)mbd->map_address;
    while((uint32_t)map_start < map_end){
        if(map_start->type == 1){
            uint32_t start_frame = map_start->address / PAGE_MAX;
            uint32_t total_frames = map_start->length / PAGE_MAX;
            for(uint32_t i = 0; i < total_frames; i++){
                BITMAP_CLEAR(start_frame + i);
                if(used_memory >= PAGE_MAX){
                    used_memory-= PAGE_MAX;
                }
            }
        }
        map_start = (memory_map_struct*)((uint32_t)map_start + map_start->size + sizeof(uint32_t));
    }

    uint32_t kernel_start_frame = 0x100000 / PAGE_MAX;
    uint32_t kernel_end_frame = (uint32_t)&_kernel_end / PAGE_MAX;
    for(uint32_t i = 0; i < kernel_end_frame; i++){
        BITMAP_SET(i);
        used_memory += PAGE_MAX;
    }
    uint32_t bitmap_start_frame = (uint32_t)bitmap / PAGE_MAX;
    uint32_t bitmap_end_frame = ((uint32_t)bitmap + bitmap_size) / PAGE_MAX;

    for (uint32_t i = bitmap_start_frame; i <= bitmap_end_frame; i++) {
        BITMAP_SET(i);
        used_memory += PAGE_MAX;
    }
}

void* alloc(){
    if(used_memory >= memory_size){
        console_write_string("[ error ] tried to allocate memory that is not avaible");
        return 0;
    }
    uint32_t total = max_frames / 32;
    for(uint32_t i = 0; i < total; i++){
        if(bitmap[i] != 0xFFFFFFFF){
            for(uint32_t bit = 0; bit < 32; bit++){
                if(!(bitmap[i] & (1 << bit))){
                    uint32_t frame = (i * 32) + bit;
                    BITMAP_SET(frame);
                    used_memory += PAGE_MAX;
                    return (void*)(frame * PAGE_MAX);
                }
            }
        }
    }
    return 0;
}

void free(void* address){
    uint32_t frame = (uint32_t)address / PAGE_MAX;
    if (frame >= max_frames) {
        return;
    }

    BITMAP_CLEAR(frame);

    if (used_memory >= PAGE_MAX) {
        used_memory -= PAGE_MAX;
    }
}
