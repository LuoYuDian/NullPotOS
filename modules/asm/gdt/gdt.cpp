// 创建于2024.12.24
// NullPotOS 设置全局描述符程序

#include <modules/asm/gdt/gdt.hpp>
#include <libs/printf.hpp>

#define GDT_LENGTH 5
#define kernel_data_selector 0x10

gdt_entry_t gdt_entries[GDT_LENGTH];

gdt_ptr_t gdt_ptr;

static void gdt_set_gate(int64_t num,uint64_t base,uint64_t limit,uint8_t access,uint8_t gran);

extern "C" uint64_t stack;

void _initgdt(void)
{
	print_busy("Init GDT...\r");

	gdt_ptr.limit	= sizeof(gdt_entry_t) * GDT_LENGTH - 1;
	gdt_ptr.base	= (uint64_t)&gdt_entries;

	gdt_set_gate(0, 0, 0, 0, 0);
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9B, 0xA0);
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x93, 0xA0);
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFB, 0xA0);
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF3, 0xA0);

	asm volatile 
	(
		"lgdt [gdt_ptr]\n"
		:
		: [gdt_ptr] "*p" (&gdt_ptr)
	);
	asm volatile 
	(
		"mov %[dsel], %%ds\n"
		"mov %[dsel], %%fs\n"
		"mov %[dsel], %%gs\n"
		"mov %[dsel], %%es\n"
		"mov %[dsel], %%ss\n"
		:
		: [dsel] "rm" (kernel_data_selector)
	);
	print_succ("GDT Init.\n"); // 提示用户gdt初始化完成
}

static void gdt_set_gate(int64_t num,uint64_t base,uint64_t limit,uint8_t access,uint8_t gran)
{
	gdt_entries[num].base_low		= (base & 0xFFFF);
	gdt_entries[num].base_middle	= (base >> 16) & 0xFF;
	gdt_entries[num].base_high		= (base >> 24) & 0xFF;

	gdt_entries[num].limit_low		= (limit & 0xFFFF);
	gdt_entries[num].granularity	= (limit >> 16) & 0x0F;

	gdt_entries[num].granularity	|= gran & 0xF0;
	gdt_entries[num].access			= access;
}
