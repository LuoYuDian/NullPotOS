// 创建于2024.12.8
// NullPotOS x86 hhk

#include <arch/x86/asm/gdt/gdt.h>
#include <arch/x86/asm/idt/idt.h>
#include <drivers/view/vga/vga.h>

extern void _kernelmain(); // 定义内核函数

void _hhkmain()
{
    // 初始化
    VGA_clear();
    VGA_set_theme(VGA_COLOR_CYAN,VGA_COLOR_BLACK);
    _initgdt();
    _initidt();
}