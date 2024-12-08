// 创建于2024.12.8
// NullPotOS 内核

#include <drivers/view/vga/vga.h>

void _kernelmain()
{
    VGA_put_str("NullPotOS V0.03\n@Copyright LuoYuDian 2024\n");
    VGA_put_str("You see source code at https://github/LuoYuDian/NUllPotOS !\n");
    VGA_put_str("Welcome to use NullPotOS!\n");
}