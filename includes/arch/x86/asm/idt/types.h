// 创建于2024.12.13
// NullPotOS x86 idt向量表头文件
// 在中国，这一天是南京大屠杀死难者国家公祭日
// 为死者默哀!!!

#define FAULT_DIVISION_ERROR            0x0
#define FAULT_TRAP_DEBUG_EXCEPTION      0x1
#define INT_NMI                         0x2
#define TRAP_BREAKPOINT                 0x3
#define TRAP_OVERFLOW                   0x4
#define FAULT_BOUND_EXCEED              0x5
#define FAULT_INVALID_OPCODE            0x6
#define FAULT_NO_MATH_PROCESSOR         0x7
#define ABORT_DOUBLE_FAULT              0x8
#define FAULT_RESERVED_0                0x9
#define FAULT_INVALID_TSS               0xa
#define FAULT_SEG_NOT_PRESENT           0xb
#define FAULT_STACK_SEG_FAULT           0xc
#define FAULT_GENERAL_PROTECTION        0xd
#define FAULT_PAGE_FAULT                0xe
#define FAULT_RESERVED_1                0xf
#define FAULT_X87_FAULT                 0x10
#define FAULT_ALIGNMENT_CHECK           0x11
#define ABORT_MACHINE_CHECK             0x12
#define FAULT_SIMD_FP_EXCEPTION         0x13
#define FAULT_VIRTUALIZATION_EXCEPTION  0x14
#define FAULT_CONTROL_PROTECTION        0x15