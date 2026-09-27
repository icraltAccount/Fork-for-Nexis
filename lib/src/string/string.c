#include "string/string.h"
#include "memory/memory.h"

usize_t strlen(const char *s) {
    usize_t len = 0;

    while (s[len] != '\0') {
        len++;
    }

    return len;
}

isize_t strcmp(const char *s1, const char *s2) {
    while (*s1 != '\0' && *s1 == *s2) {
        s1++;
        s2++;
    }

    return (byte_t)*s1 - (byte_t)*s2;
}

char *strcpy(char *dest, const char *src) {
    char *ret = dest;

    while ((*dest++ = *src++) != '\0');

    return ret;
}

char *strcat(char *dest, const char *src) {
    char *ret = dest;

    while (*dest != '\0') {
        dest++;
    }

    while ((*dest++ = *src++) != '\0');

    return ret;
}
