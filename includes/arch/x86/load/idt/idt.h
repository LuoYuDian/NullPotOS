// 创建于2024.12.13
// NullPotOS x86 idt头文件
// 在中国，这一天是南京大屠杀死难者国家公祭日
// 为死者默哀!!!

#define IDT_ATTR(dpl)                   ((0x70 << 5) | (dpl & 3) << 13 | 1 << 15)

void _initidt();
