// 创建于2024.12.22
// NullPotOS 内核调试和打印信息程序头文件

#include <libs/vargs.hpp>

void printf(const char *format,...);

void printf_color(int fore,const char *format,...);

void print_busy(const char *str);

void print_succ(const char *str);

void print_warn(const char *str);

void print_erro(const char *str);

int vsprintf(char *buff,const char *format,va_list args);

void sprintf(char *str,const char *fmt,...);