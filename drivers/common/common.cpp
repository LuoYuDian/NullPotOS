// 创建于2024.12.22
// NullPotOS 常见设备驱动

#include <drivers/common/common.hpp>

void outb(uint16_t port,uint8_t value)
{
	asm volatile("outb %1, %0" : : "dN" (port), "a" (value));
}

uint8_t inb(uint16_t port)
{
	uint8_t ret;
	asm volatile("inb %1, %0" : "=a" (ret) : "dN" (port));
	return ret;
}

void outw(uint16_t port,uint16_t value)
{
	asm volatile("outw %1, %0" : : "dN" (port), "a" (value));
}


uint16_t inw(uint16_t port)
{
	uint16_t ret;
	asm volatile("inw %1, %0" : "=a" (ret) : "dN" (port));
	return ret;
}

void outl(uint16_t port,uint32_t value)
{
	asm volatile("outl %1, %0" : : "dN"(port), "a"(value));
}

uint32_t inl(uint16_t port)
{
	uint32_t ret;
	asm volatile("inl %1, %0" : "=a"(ret) : "dN"(port));
	return ret;
}

void insw(uint16_t port,void *buf,unsigned long n)
{
	asm volatile("cld; rep; insw"
                 : "+D"(buf),
                 "+c"(n)
                 : "d"(port));
}

void outsw(uint16_t port,const void *buf,unsigned long n)
{
	asm volatile("cld; rep; outsw"
                 : "+S"(buf),
                 "+c"(n)
                 : "d"(port));
}

void insl(uint32_t port,void *addr,int cnt)
{
	asm volatile("cld;"
                 "repne; insl;"
                 : "=D" (addr), "=c" (cnt)
                 : "d" (port), "0" (addr), "1" (cnt)
                 : "memory", "cc");
}

void outsl(uint32_t port,const void *addr,int cnt)
{
	asm volatile("cld;"
                 "repne; outsl;"
                 : "=S" (addr), "=c" (cnt)
                 : "d" (port), "0" (addr), "1" (cnt)
                 : "memory", "cc");
}


void enable_interrupts(void)
{
	asm volatile("sti");
}

void disable_interrupts(void)
{
	asm volatile("cli" ::: "memory");
}

void kernel_halt(void)
{
	disable_interrupts();
	while(1) 
	{
		asm("hlt");
	}
}
