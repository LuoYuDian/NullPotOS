// 创建于2024.12.22
// NullPotOS 可变参数头文件

typedef __builtin_va_list va_list;

#define va_start(ap, last)	(__builtin_va_start(ap, last))
#define va_arg(ap, type)	(__builtin_va_arg(ap, type))
#define va_end(ap)