// 创建于2024.12.13
// NullPotOS x86 idt
// 在中国，这一天是南京大屠杀死难者国家公祭日
// 为死者默哀!!!

#include <arch/x86/asm/idt/idt.h>
#include <arch/x86/asm/idt/types.h>
#include <arch/x86/asm/interrupts/interrupts.h>
#include <stdint.h>

#define IDT_ENTRY 32

uint64_t _idt[IDT_ENTRY];
uint16_t _idt_limit = sizeof(_idt) - 1;

void _set_idt_entry(uint32_t vector, uint16_t seg_selector, void (*isr)(), uint8_t dpl) {
    uintptr_t offset = (uintptr_t)isr;
    _idt[vector] = (offset & 0xffff0000) | IDT_ATTR(dpl);
    _idt[vector] <<= 32;
    _idt[vector] |= (seg_selector << 16) | (offset & 0x0000ffff);
}


void _initidt() {
    _set_idt_entry(FAULT_DIVISION_ERROR, 0x08, _asm_isr0, 0);
}