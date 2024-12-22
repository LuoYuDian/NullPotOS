// 创建于2024.12.22
// NullPotOS 常见设备驱动头文件

#include <types.hpp>
#include <libs/string.hpp>

void outb(uint16_t port,uint8_t value);

void outw(uint16_t port,uint16_t value);

void outl(uint16_t port,uint32_t value);

uint8_t inb(uint16_t port);

uint16_t inw(uint16_t port);
uint32_t inl(uint16_t port);

void insw(uint16_t port,void *buf,unsigned long n);

void outsw(uint16_t port,const void *buf,unsigned long n);

void insl(uint32_t port,void *addr,int cnt);

void outsl(uint32_t port,const void *addr,int cnt);

uint32_t get_cr0(void);

void set_cr0(uint32_t cr0);

void enable_interrupts(void);
void disable_interrupts(void);
void kernel_halt(void);