/*
    Copyright(C) 2025 NullPotOS Project. All Rights Reserved.

    Module name:
        A20.cpp

    Description:
        This file is the A20 module of the NullPotOS kernel.

    Author:
        LuoYuDian
        MaxSinoh

    Date:
        2025.1.20
 */

#include <Core/Kernel/Asm/A20/A20.hpp>
#include <Core/Hal/Io/Io.hpp>

void EnableA20()
{
    UINT8 Port = Inb(0x92);
    Outb(0x92, Port | 0x2);
}