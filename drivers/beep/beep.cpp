// 创建于2024.12.22
// NullPotOS 板载蜂鸣器驱动

#include <drivers/beep/beep.hpp>
#include <drivers/common/common.hpp>

void system_beep(int hertz)
{
	int i;
	if (hertz == 0) 
	{
		
		i = inb(0x61);
		outb(0x61, i & 0x0d);
	} 
	else
	{
		i = hertz;
		outb(0x43, 0xb6);
		outb(0x42, i & 0xff);
		outb(0x42, i >> 8);
		i = inb(0x61);
		outb(0x61, (i | 0x03) & 0x0f);
	}
}
