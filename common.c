#include "common.h"

void putchar(char ch);

void printf(char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    for (int i = 0; fmt[i] != '\0'; i++) {
        if (fmt[i] == '%') {
            i++;

            switch (fmt[i]) {
                case '\0': {
                    putchar('%');
                    goto end;
                }
                case '%': {
                    putchar('%');
                    break;
                }
                case 's': {
                    char* str = va_arg(args, char*);
                    for (int j = 0; str[j] != '\0'; j++) {
                        putchar(str[j]);
                    }
                    break;
                }
                case 'd': {
                    int value = va_arg(args, int);
                    if (value < 0) {
                        putchar('-');
                        value = -value;
                    }

                    int divisor = 1;
                    while (value / divisor > 9) {
                        divisor *= 10;
                    }

                    while (divisor > 0) {
                        putchar('0' + value / divisor);
                        value %= divisor;
                        divisor /= 10;
                    }
                    break;
                }
                case 'x': {
                    printf("0x");
                    unsigned value = va_arg(args, unsigned);
                    for (int i = 7; i >= 0; i--) {
                        unsigned nibble = (value >> (i * 4)) & 15;
                        putchar("0123456789abcdef"[nibble]);
                    }
                }
            }
        } else {
            putchar(fmt[i]);
        }
    }
    goto end;

    end:
        va_end(args);
}

void *memset(void *buf, char c, size_t n) {
    for (size_t i = 0; i < n; i++) {
        ((char*)buf)[i] = c;
    }
    return buf;
}

void *memcpy(void *dst, void *src, size_t n) {
    for (size_t i = 0; i < n; i++) {
        ((char*)dst)[i] = ((char*)src)[i];
    }
    return dst;
}

int strlen(char *a) {
    int i = 0;
    while(*a != '\0') {
        i++;
        a++;
    }
    return i;
}

char *strcpy(char *dst, char *src) {
    int len = strlen(src);
    int i = 0;
    for (; i < len; i++) {
        dst[i] = src[i];
    }
    dst[i] = '\0';
    return dst;
}

int strcmp(char *a, char *b) {
    int len1 = strlen(a);
    int len2 = strlen(b);

    int i = 0;
    for (; i < len1 && i < len2; i++) {
        if (a[i] != b[i]) {
            break;
        }
    }

    return ((unsigned char*)a)[i] - ((unsigned char*)b)[i];
}
