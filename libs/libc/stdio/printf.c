// 创建于2024.12.13
// NullPotOS 标准库
// 在中国，这一天是南京大屠杀死难者国家公祭日
// 为死者默哀!!!

#include <libs/libc/stdio.h>
#include <stdarg.h>

#include <drivers/view/vga/vga.h>

void printf(char* fmt, ...)
{
    char buffer[1024];
    va_list args;
    va_start(args, fmt);
    __sprintf_internal(buffer, fmt, args);
    va_end(args);

    VGA_put_str(buffer);
}