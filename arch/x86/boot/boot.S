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

        pushl %esp

        call _hhkmain

        cli

        jmp .loop

    .loop:
        hlt
        jmp .loop