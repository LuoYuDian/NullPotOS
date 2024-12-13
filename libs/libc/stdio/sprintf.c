// 创建于2024.12.13
// NullPotOS 标准库
// 在中国，这一天是南京大屠杀死难者国家公祭日
// 为死者默哀!!!

#include <libs/libc/stdio.h>
#include <libs/libc/stdlib.h>
#include <libs/libc/string.h>
#include <stdint.h>

void __sprintf_internal(char* buffer, char* fmt, va_list args)
{
    char c;
    int num;
    unsigned int ptr = 0;
    unsigned int adv = 0;
    while ((c = *fmt)) {
        if (c != '%') {
            buffer[ptr] = c;
            adv = 1;
        } else {
            adv = 0;
            fmt++;
            switch (c = *fmt) {
                case 'c': 
                {
                    buffer[ptr] = (char)va_arg(args, int);
                    adv = 1;
                    break;
                }
                case 's': {
                    char* str = va_arg(args, char*);
                    strcpy(buffer + ptr, str);
                    adv = strlen(str);
                    break;
                }
                case 'i':
                case 'd': {
                    num = va_arg(args, int);
                    __itoa_internal(num, buffer + ptr, 10, &adv);
                    break;
                }
                case 'u': {
                    unsigned int unum = va_arg(args, unsigned int);
                    __uitoa_internal(unum, buffer + ptr, 10, &adv);
                    break;
                }
                case 'o': {
                    num = va_arg(args, int);
                    __itoa_internal(num, buffer + ptr, 8, &adv);
                    break;
                }
                case 'x':
                case 'X': 
                {
                    num = va_arg(args, int);
                    __itoa_internal(num, buffer + ptr, 16, &adv);
                    if (c == 'X') {
                        int p = ptr;
                        char c_;
                        while ((c_ = buffer[p])) {
                            buffer[p] = c_ & ~((c_ & 0x40) >> 1);
                            p++;
                        }
                    }
                    break;
                }
                case 'p': {
                    uintptr_t dptr = va_arg(args, uintptr_t);
                    buffer[ptr] = '0';
                    buffer[ptr+1] = 'x';
                    __itoa_internal((int)dptr, buffer + ptr + 2, 16, &adv);
                    adv+=2;
                    break;
                }
                case '%': {
                    buffer[ptr] = c;
                    adv = 1;
                    break;
                }
                default:
                    break;
            }
        }
        fmt++;
        ptr += adv;
    }
    buffer[ptr] = '\0';
}

void sprintf(char* buffer, char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    __sprintf_internal(buffer, fmt, args);
    va_end(args);
}