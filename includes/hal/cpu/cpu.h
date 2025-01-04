// 创建于2024.12.15
// NullPotOS 硬件抽象层 cpu

#include <hal/hal.h>

typedef unsigned long reg32;
typedef unsigned short reg16;

typedef struct 
{
    reg32 edi;
    reg32 esi;
    reg32 ebp;
    reg32 esp;
    reg32 ebx;
    reg32 edx;
    reg32 ecx;
    reg32 eax;
} __attribute__((packed)) registers;

reg32 cpu_r_cr0();

reg32 cpu_r_cr2();

reg32 cpu_r_cr3();

void cpu_w_cr0(reg32 v);

void cpu_w_cr2(reg32 v);

void cpu_w_cr3(reg32 v);

void cpu_get_model(char* model_out);

int cpu_brand_string_supported();

void cpu_get_brand(char* brand_out);