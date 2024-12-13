// 创建于2024.12.13
// NullPotOS x86 idt头文件
// 在中国，这一天是南京大屠杀死难者国家公祭日
// 为死者默哀!!!

typedef struct {
    unsigned int vector;
    unsigned int err_code;
    unsigned int eip;
    unsigned int cs;
    unsigned int eflags;
} __attribute__((packed)) isr_param;

void _asm_isr0();

void interrupt_handler(isr_param* param);
