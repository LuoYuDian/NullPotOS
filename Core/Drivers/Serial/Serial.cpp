/*
    Copyright(C) 2025 NullPotOS Project. All Rights Reserved.

    Module name:
        Serial.cpp

    Description:
        This file is the serial driver of the NullPotOS kernel.

    Author:
        LuoYuDian
        MaxSinoh

    Date:
        2025.1.20
 */

#include <Core/Drivers/Serial/Serial.hpp>
#include <Core/Hal/Io/Io.hpp>

int InitSerial(void)
{
	Outb(SERIAL_PORT + 1, 0x00);
	Outb(SERIAL_PORT + 3, 0x80);
	Outb(SERIAL_PORT + 0, 0x03);
	Outb(SERIAL_PORT + 1, 0x00);
	Outb(SERIAL_PORT + 3, 0x03);
	Outb(SERIAL_PORT + 2, 0xC7);
	Outb(SERIAL_PORT + 4, 0x0B);
	Outb(SERIAL_PORT + 4, 0x1E);
	Outb(SERIAL_PORT + 0, 0xAE);

	if (Inb(SERIAL_PORT + 0) != 0xAE) 
	{
		return 1;
	}

	Outb(SERIAL_PORT + 4, 0x0F);
	return 0;
}

int SerialReceived(void)
{
	return Inb(SERIAL_PORT + 5) & 1;
}

char ReadSerial(void)
{
	while (SerialReceived() == 0)
	{

	}
	return Inb(SERIAL_PORT);
}

int IsTransmitEmpty(void)
{
	return Inb(SERIAL_PORT + 5) & 0x20;
}

void WriteSerial(char A)
{
	while (IsTransmitEmpty() == 0)
	{

	}
	Outb(SERIAL_PORT, A);
}