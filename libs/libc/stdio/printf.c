// 创建于2024.12.13
// NullPotOS 标准库

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