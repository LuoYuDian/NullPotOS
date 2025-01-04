// 创建于2024.12.8
// NullPotOS string

#include <libs/libc/string.h>

size_t strlen(const char* str)
{
    size_t len = 0;
    while (str[len])
    {
        len++;
    }
    return len;
}