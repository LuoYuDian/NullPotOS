// 创建于2024.12.13
// NullPotOS x86 中断
// 在中国，这一天是南京大屠杀死难者国家公祭日
// 为死者默哀!!!

#include <arch/x86/load/interrupts/interrupts.h>
#include <libs/libc/stdio.h>
#include <drivers/view/vga/vga.h>

void isr0 (isr_param* param) 
{
    printf("[PANIC] Exception (%d) CS=0x%X, EIP=0x%X", param->vector, param->cs, param->eip);
}

void interrupt_handler(isr_param* param) 
{
    switch (param->vector)
    {
        case 0:
            isr0(param);
            break;
    }
}