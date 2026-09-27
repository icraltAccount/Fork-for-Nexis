#pragma once

#include <stdint.h>
#include <stdbool.h>

typedef uint32_t ptr_t;
typedef int32_t isize_t;
typedef uint32_t usize_t;
typedef uint8_t byte_t;

void *memset(void *dst, byte_t value, usize_t n);
void *memcpy(void *dst, const void *src, usize_t n);
isize_t memcmp(const void *a, const void *b, usize_t n);
