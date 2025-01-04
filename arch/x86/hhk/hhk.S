// 创建于2024.12.15
// NullPotOS hhk入口

.section .text
    .global _hhkmain
    _hhkmain:

        subl $16, %esp
        
        call _initgdt
        movl $_gdt, 2(%esp)
        movw _gdt_limit, %ax
        movw %ax, (%esp)
        lgdt (%esp)

        movw $0x10, %cx
        movw %cx, %es
        movw %cx, %ds
        movw %cx, %fs
        movw %cx, %gs
        movw %cx, %ss

        pushw $0x08
        pushl $_afterload
        retf

    _afterload:

        movl $multiboot_info, (%esp)
        call _kernelinit

        mov $0xffbffff0, %esp

        call _kernel_post_init

        subl $6, %esp

        movl $_idt, 2(%esp)
        movw _idt_limit, %ax
        movw %ax, (%esp)
        lidt (%esp)

        addl $6, %esp
 
        call _kernelmain

        cli
    
    .loop:
        hlt
        jmp .loop