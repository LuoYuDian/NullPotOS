// 创建于2024.12.13
// NullPotOS 标准库
// 在中国，这一天是南京大屠杀死难者国家公祭日
// 为死者默哀!!!

#include <stdarg.h>

#ifdef __LIBC
void __sprintf_internal(char* buffer, char* fmt, va_list args);
#endif

void sprintf(char* buffer, char* fmt, ...);
void printf(char* fmt, ...);