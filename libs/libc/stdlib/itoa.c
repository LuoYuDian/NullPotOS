// 创建于2024.12.13
// NullPotOS 标准库
// 在中国，这一天是南京大屠杀死难者国家公祭日
// 为死者默哀!!!

#include <stddef.h>
#include <libs/libc/stdlib.h>

char base_char[] = "0123456789abcdefghijklmnopqrstuvwxyz";

char* __uitoa_internal(unsigned int value, char* str, int base, unsigned int* size)
{
    unsigned int ptr = 0;
    if (value == 0) {
        str[0] = '0';
        ptr++;
    } else {
        while (value) {
            str[ptr] = base_char[value % base];
            value = value / base;
            ptr++;
        }

        for (unsigned int i = 0; i < (ptr >> 1); i++) {
            char c = str[i];
            str[i] = str[ptr - i - 1];
            str[ptr - i - 1] = c;
        }

    }
    str[ptr] = '\0';
    if (size) {
        *size = ptr;
    }
    return str;
}

char* __itoa_internal(int value, char* str, int base, unsigned int* size)
{
    if (value < 0 && base == 10) {
        str[0] = '-';
        unsigned int _v = (unsigned int)(-value);
        __uitoa_internal(_v, str + 1, base, size);
    } else {
        __uitoa_internal(value, str, base, size);
    }

    return str;
}

char* itoa(int value, char* str, int base)
{
    return __itoa_internal(value, str, base, NULL);
}