// 创建于2024.12.13
// NullPotOS 标准库
// 在中国，这一天是南京大屠杀死难者国家公祭日
// 为死者默哀!!!

#include <libs/libc/string.h>

char*
strcpy(char* dest, const char* src) {
    char c;
    unsigned int i = 0;
    while ((c = src[i]))
    {
        dest[i] = c;
        i++;
    }
    dest[i] = '\0';
    return dest;
}