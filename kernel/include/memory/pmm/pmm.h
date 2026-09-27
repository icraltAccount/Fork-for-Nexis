#pragma once

#include "memory/memory.h"
#include <stdint.h>

#define PMM_BITMAP_SET(frame)(pmm_bitmap[frame / 32] |= (1 << (frame % 32)))
#define PMM_BITMAP_CLEAR(frame)(pmm_bitmap[frame / 32] &= ~(1 << (frame % 32)))
#define PMM_BITMAP_TEST(frame)(pmm_bitmap[frame / 32] & (1 << (frame % 32)))

#define PAGE_SIZE 4096

extern usize_t pmm_total_memory;
extern usize_t pmm_used_memory;
extern usize_t pmm_max_frames;

extern ptr_t *pmm_bitmap;

typedef struct{
    uint32_t size;
    uint64_t address;
    uint64_t length;
    uint32_t type;
} __attribute__((packed)) mmap_t;

typedef struct{
    uint32_t flags;
    uint32_t memory_lower;
    uint32_t memory_upper;
    uint32_t boot_device;
    uint32_t cmd_line;
    uint32_t modules_count;
    uint32_t modules_address;
    uint32_t syms[4];
    uint32_t map_length;
    uint32_t map_address;
} __attribute__((packed)) mbi_t;

void pmm_init(mbi_t *mbd);
void *pmm_alloc_page();
void pmm_free_page(void *address);
