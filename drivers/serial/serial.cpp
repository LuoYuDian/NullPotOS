// 创建于2024.12.22
// NullPotOS 计算机串口驱动

#include <drivers/serial/serial.hpp>
#include <drivers/common/common.hpp>

int init_serial(void)
{
	outb(SERIAL_PORT + 1, 0x00);
	outb(SERIAL_PORT + 3, 0x80);
	outb(SERIAL_PORT + 0, 0x03);
	outb(SERIAL_PORT + 1, 0x00);
	outb(SERIAL_PORT + 3, 0x03);
	outb(SERIAL_PORT + 2, 0xC7);
	outb(SERIAL_PORT + 4, 0x0B);
	outb(SERIAL_PORT + 4, 0x1E);
	outb(SERIAL_PORT + 0, 0xAE);

	if (inb(SERIAL_PORT + 0) != 0xAE) 
	{
		return 1;
	}

	outb(SERIAL_PORT + 4, 0x0F);
	return 0;
}

int serial_received(void)
{
	return inb(SERIAL_PORT + 5) & 1;
}

char read_serial(void)
{
	while (serial_received() == 0)
	{

	}
	return inb(SERIAL_PORT);
}

int is_transmit_empty(void)
{
	return inb(SERIAL_PORT + 5) & 0x20;
}

void write_serial(char a)
{
	while (is_transmit_empty() == 0)
	{

	}
	outb(SERIAL_PORT, a);
}
