// 创建于2024.12.22
// NullPotOS 计算机串口驱动头文件
 
#include <types.hpp>

#define SERIAL_PORT 0x3f8

int init_serial(void);

int serial_received(void);

char read_serial(void);

int is_transmit_empty(void);

void write_serial(char a);