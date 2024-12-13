// 创建于2024.12.8
// NullPotOS x86 boot

#include <arch/x86/boot/multiboot.h>

.code32

.section .header
    .align 8
    .long MAGIC
    .long ALI
    .long CHECKSUM(ALI)
    
    .long WIDTH
    .long HEIGHT
    .long DEPTH

.section .bss
    .align 16
    stack_bottom:
        .skip 16318, 0
    stack_top:

.section .text
    .global start_

    start_:
        movl $stack_bottom, %esp

        call _hhkmain

        // 加载GDT
        subl $0x6, %esp
        movl $_gdt, 2(%esp)
        movw _gdt_limit, %ax
        movw %ax, (%esp)
        lgdt (%esp)
        addl $0x6, %esp

        // 加载IDT
        subl $0x6, %esp
        movl $_idt, 2(%esp)
        movw _idt_limit, %ax
        movw %ax, (%esp)
        lidt (%esp)
        addl $0x6, %esp


        // 设置段寄存器
        movw $0x10, %cx
        movw %cx, %es
        movw %cx, %ds
        movw %cx, %fs
        movw %cx, %gs
        movw %cx, %ss

        // 进入保护模式
        pushw $0x08
        pushl $_aftergdt
        retf

    _aftergdt:
        pushl %ebx
        
        // 进入内核
        call _kernelmain

        cli

    .loop:
        hlt
        jmp .loop