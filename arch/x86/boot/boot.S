// 创建于2024.12.8
// NullPotOS x86 boot
#define __ASM__ 1
#include <arch/x86/boot/multiboot.h>

#define MB_FLAGS    MULTIBOOT_MEMORY_INFO | MULTIBOOT_PAGE_ALIGN
#define KPG_SIZE    24*1024
.code32

.section .header
    .align 8
    .long MULTIBOOT_MAGIC
    .long MB_FLAGS
    .long CHECKSUM(MB_FLAGS)

.section .bss
    .global multiboot_info
    .align 16
    multiboot_info:
        .skip 4096
    stack_bottom:
        .skip 16318, 0
    stack_top:

.section .kpg
    .global _k_ptd
    _k_ptd:
        .skip KPG_SIZE, 0

.section .hhkinit
    .global start_
    .type start_, @function
    start_:
        movl $stack_bottom, %esp

        subl $16, %esp

        movl $multiboot_info, 4(%esp)
        movl %ebx, (%esp)
        call _save_multiboot_info

        movl $(KPG_SIZE), 4(%esp)
        movl $(_k_ptd - 0xC0000000), (%esp)    /* PTD物理地址 */
        call _hhkinit

        movl (%esp), %eax
        andl $0xfffff000, %eax
        movl %eax, %cr3

        movl %cr0, %eax
        orl $0x80000000, %eax
        movl %eax, %cr0

        addl $16, %esp

        pushl $_hhkmain
        ret