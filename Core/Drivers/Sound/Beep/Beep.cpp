/*
    Copyright(C) 2025 NullPotOS Project. All Rights Reserved.

    Module name:
        Beep.cpp

    Description:
        This file is the beep driver of the NullPotOS kernel.

    Author:
        LuoYuDian
        MaxSinoh

    Date:
        2025.1.23
 */

#include <Core/Drivers/Sound/Beep/Beep.hpp>
#include <Core/Hal/Io/Io.hpp>

void EnableBeep()
{
	SystemBeep(1);
}

void DisableBeep()
{
	SystemBeep(0);
}

void SystemBeep(int Hert)
{
	int i;
	if (Hert == 0) 
	{
		i = Inb(0x61);
		Outb(0x61, i & 0x0d);
	} 

	else
	{
		i = Hert;
		Outb(0x43, 0xb6);
		Outb(0x42, i & 0xff);
		Outb(0x42, i >> 8);
		i = Inb(0x61);
		Outb(0x61, (i | 0x03) & 0x0f);
	}
}
