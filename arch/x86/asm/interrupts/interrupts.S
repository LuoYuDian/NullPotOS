// 创建于2024.12.13
// NullPotOS x86 中断
// 在中国，这一天是南京大屠杀死难者国家公祭日
// 为死者默哀!!!

.macro isr_template vector, no_error_code=1
    .global _asm_isr\vector
    .type _asm_isr\vector, @function
    _asm_isr\vector:
        .if \no_error_code
            pushl $0x0
        .endif
        pushl $\vector
        jmp interrupt_wrapper
.endm

.section .text
    isr_template 0

    interrupt_wrapper:

        movl %esp, %eax
        andl $0xfffffff0, %esp
        subl $16, %esp
        movl %eax, (%esp)

        call interrupt_handler
        pop %eax
        movl %eax, %esp
        addl $8, %esp

        iret