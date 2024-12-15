// 创建于2024.12.15
// NullPotOS 硬件抽象层 设备io

#include <stdint.h>
#include <hal/hal.h>

void io_port_wb(uint8_t port, uint8_t value) 
{
    asm volatile 
    (
        "movb %0, %%al\n"
        "movb %1, %%dx\n"
        "out %%al, %%dx\n"
        :: "r"(value) "r"(port)
    );
}

void io_port_wl(uint8_t port, uint32_t value) 
{
    asm volatile 
    (
        "movl %0, %%eax\n"
        "movb %1, %%dx\n"
        "out %%eax, %%dx\n"
        :: "r"(value) "r"(port)
    );
}

uint8_t io_port_rb(uint8_t port) 
{
    asm volatile 
    (
        "movb $0, %%eax\n"
        "movb %0, %%dx\n"
        "in %%dx, %%al\n"
        :: "r"(port)
    );
}

uint32_t io_port_rl(uint8_t port) 
{
    asm volatile 
    (
        "movb %0, %%dx\n"
        "in %%dx, %%eax\n"
        :: "r"(port)
    );
}
