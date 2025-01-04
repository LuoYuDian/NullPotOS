// 创建于2024.12.13
// NullPotOS 标准库

#include <stdarg.h>
#include <drivers/view/vga/vga.h>

#ifdef __LIBC
void __sprintf_internal(char* buffer, char* fmt, va_list args);
#endif

void sprintf(char* buffer, char* fmt, ...);
void printf(char* fmt, ...);