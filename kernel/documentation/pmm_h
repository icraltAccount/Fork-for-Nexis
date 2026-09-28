#ifndef PMM_H
#define PMM_H
#include <stdint.h>
#define BITMAP_SET(frame) ( bitmap[frame / 32] |= (1 << (frame % 32)) ) //turn a bit on
#define BITMAP_CLEAR(frame) ( bitmap[frame / 32] &= ~(1 << (frame % 32)) ) //turn a bit off
#define BITMAP_TEST(frame) ( bitmap[frame / 32] & (1 << (frame % 32)) ) //test if a bit is occupied or not
#define PAGE_MAX 4096
extern uint32_t memory_size;
extern uint32_t used_memory;
extern uint32_t max_frames;
extern uint32_t* bitmap;
typedef struct{ //describes the entries that grub puts in memory: the size of the first 4 bytes are the "uint32_t size", the next 8 bytes are the initial address "uint64_t address", the next 8 are the extension "uint64_t length", the last 4 are the type "uint32_t type"
    uint32_t size; //how many bytes are necessary to jump to the next piece of memory
    uint64_t address; //the first address that exists, if a piece of free RAM starts at the byte 1 MB of memory, the stored value will be 0x0000000000100000(1.048.576 in decimal)
    uint64_t length; //the size in bytes of each region of memory(each piece), if the size is 512 MB the value will be 536.870.912 bytes
    uint32_t type; //the type of memory, possible values: 1 -> not used RAM/can be used, 2 -> reserved for hardware/BIOS, 3 -> ACPI memory tables(BIOS uses it for energy control), 4 -> preserved memory when the computer is turned off
} __attribute__((packed)) memory_map_struct;

typedef struct{ //informations that grub gives to us about the system
    uint32_t flags; //has 32 bits of turned off and on bits for security, some systems may not be able to read the memory map from BIOS, before reading the map our kernel makes the bitwise test "flags & (1 << 6)", if the answer is different from 0 that means that the grub could read the memory map and the map_address and map_length have trustable data
    uint32_t memory_lower; //the amount of avaible RAM memory lower than 1 MB in kilobytes
    uint32_t memory_upper; //the amount of avaible RAM memory bigger than 1 MB in kilobytes
    uint32_t boot_device; //the device that grub used to load the kernel, it's important for the filesystem, first byte is: 0x00 -> drive number in BIOS, 0x80 -> first floppy disk, 0x81 -> HD/SSD, second byte is: number of primary partition(0, 1, 2 or 3), third byte is: number of sub-partition, fourth and last byte is: reserved
    uint32_t cmd_line; //it's a pointer to a string, that string contains the configuration parameters for the grub, it is basically the text that is written in the grub screen when it's time to activate the kernel, it has the configurations before the kernel starts
    uint32_t modules_count; //it's the amount of modules(extra files) that grub has loaded inside RAM with the kernel
    uint32_t modules_address; //it's a pointer that points to the RAM, it points to a table that lists where each one of the modules(files) were put inside the RAM, it's important if we want to load things for the kernel like drivers, disk images, screen fonts, configuration files and other things, we need that because it HAS to be loaded BEFORE the kernel
    uint32_t syms[4]; //it's a 16 bytes array that is reserved to pass the executable symbols table from our kernel, it exists because if our kernel gets a fatal error(panic) and crashes, its really helpful to print the name of the C function where the error happened, since the CPU only sees numbers in memory and not function names, this table of symbols gives to the kernel the address of the function that has the error
    uint32_t map_length; //the size of the table in bytes, since the computer can have 2, 15, more or less memory regions, we need to know the size of an entire block
    uint32_t map_address; //the memory address(pointer) of where grub wrote the first memory map, it is basically the start point of the PMM
} __attribute__((packed)) info_struct;

void pmm_init(info_struct* mbd); //mbd means multiboot descriptor/multiboot data
void* alloc();
void free(void* address);
#endif
