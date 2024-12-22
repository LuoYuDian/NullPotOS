// 创建于2024.12.22
// NullPotOS gdt头文件

#include <types.hpp>

/* 全局描述符类型 */
typedef struct gdt_entry_t 
{
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t  base_middle;
	uint8_t  access;
	uint8_t  granularity;
	uint8_t  base_high;
} __attribute__((packed)) gdt_entry_t;

typedef struct gdt_ptr_t 
{
	uint16_t limit;
	uint64_t base;
} __attribute__((packed)) gdt_ptr_t;

void _initgdt(void);