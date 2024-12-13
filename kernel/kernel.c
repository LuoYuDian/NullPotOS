// 创建于2024.12.8
// NullPotOS 内核

#include <drivers/view/vga/vga.h>
#include <libs/libc/stdio.h>

void _interrupts_kernel()
{
    __asm__("int $0");
}

void _kernelmain(void *info_table)
{
    (void *)info_table;
    printf("NullPotOS V0.04\n@Copyright LuoYuDian 2024\n");
    printf("You see source code at https://github/LuoYuDian/NUllPotOS!\n");
    printf("Welcome to use NullPotOS!\n");
    printf("\n");

    _interrupts_kernel();
}