// 创建于2024.12.14
// NullPotOS 错误处理头文件

#include "stdint.h"
#include <libs/libc/stdio.h>
#include <drivers/view/vga/vga.h>

// 错误代码
#define ERROR_NULL_PTR          0x00 // 空指针错误
#define ERROR_DIVIDE_BY_ZERO    0x01 // 除零错误
#define ERROR_OVERFLOW          0x02 // 溢出错误
#define ERROR_UNDERFLOW         0x03 // 下溢错误
#define ERROR_OUT_OF_PMEMORY     0x04 // 内存不足错误(物理)
#define ERROR_OUT_OF_VMEMORY    0x05 // 内存不足错误(虚拟)

void put_error(int error_code);