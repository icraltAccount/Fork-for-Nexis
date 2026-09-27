#include "memory/memory.h"

void *memset(void *dst, byte_t value, usize_t n) {
    byte_t *ptr = (byte_t *)dst;

    while (n--) *ptr++ = value;

    return dst;
}

void *memcpy(void *dst, const void *src, usize_t n){
    byte_t *d = (byte_t *)dst;
    const byte_t *s = (const byte_t *)src;

    while (n--) *d++ = *s++;

    return dst;
}

isize_t memcmp(const void *a, const void *b, usize_t n) {
    const byte_t *a_byte = (const byte_t *)a;
    const byte_t *b_byte = (const byte_t *)b;

    while (n--) {
        if (*a_byte != *b_byte) return (isize_t)*a_byte - (isize_t)*b_byte;

        a_byte++;
        b_byte++;
    }

    return 0;
}
