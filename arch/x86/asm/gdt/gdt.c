// 创建于2024.12.13
// NullPotOS x86 gdt
// 在中国，这一天是南京大屠杀死难者国家公祭日
// 为死者默哀!!!

#include <arch/x86/asm/gdt/gdt.h>
#include <stdint.h>

#define GDT_ENTRY 5

uint64_t _gdt[GDT_ENTRY];
uint16_t _gdt_limit = sizeof(_gdt);

void _setgdtentry(uint32_t index, uint32_t base, uint32_t limit, uint32_t flags) {
    _gdt[index] = SEG_BASE_H(base) | flags | SEG_LIM_H(limit) | SEG_BASE_M(base);
    _gdt[index] <<= 32;
    _gdt[index] |= SEG_BASE_L(base) | SEG_LIM_L(limit);
}

void _initgdt() {
    _setgdtentry(0, 0, 0, 0);
    _setgdtentry(1, 0, 0xfffff, SEG_R0_CODE);
    _setgdtentry(2, 0, 0xfffff, SEG_R0_DATA);
    _setgdtentry(3, 0, 0xfffff, SEG_R3_CODE);
    _setgdtentry(4, 0, 0xfffff, SEG_R3_DATA);
}