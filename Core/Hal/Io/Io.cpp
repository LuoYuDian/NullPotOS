/*
    Copyright(C) 2025 NullPotOS Project. All Rights Reserved.

    Module name:
        Io.cpp

    Description:
        This module contains the implementation of the Io class.

    Author:
        LuoYuDian

    Date:
        2025-01-21
*/

#include <Core/Hal/io/Io.hpp>

void Outb(UINT16 Port,UINT8 Value)
{
	asm volatile("outb %1, %0" : : "dN" (Port), "a" (Value));
}

UINT8 Inb(UINT16 Port)
{
	UINT8 Ret;
	asm volatile("inb %1, %0" : "=a" (Ret) : "dN" (Port));
	return Ret;
}

void Outw(UINT16 Port,UINT16 Value)
{
	asm volatile("outw %1, %0" : : "dN" (Port), "a" (Value));
}


UINT16 Inw(UINT16 Port)
{
	UINT16 Ret;
	asm volatile("inw %1, %0" : "=a" (Ret) : "dN" (Port));
	return Ret;
}

void Outl(UINT16 Port,UINT32 Value)
{
	asm volatile("outl %1, %0" : : "dN"(Port), "a"(Value));
}

UINT32 Inl(UINT16 Port)
{
	UINT32 Ret;
	asm volatile("inl %1, %0" : "=a"(Ret) : "dN"(Port));
	return Ret;
}

void Insw(UINT16 Port,void *Buf,unsigned long N)
{
	asm volatile
    (
        "cld; rep; insw"
        : "+D"(Buf),
        "+c"(N)
        : "d"(Port));
}

void Outsw(UINT16 Port,const void *Buf,unsigned long N)
{
	asm volatile
    (
        "cld; rep; outsw"
        : "+S"(Buf),
        "+c"(N)
        : "d"(Port));
}

void Insl(UINT32 Port,void *Addr,int Cnt)
{
	asm volatile
    (
        "cld;"
        "repne; insl;"
        : "=D" (Addr), "=c" (Cnt)
        : "d" (Port), "0" (Addr), "1" (Cnt)
        : "memory", "cc");
}

void Outsl(UINT32 Port,const void *Addr,int Cnt)
{
	asm volatile
    (
        "cld;"
        "repne; outsl;"
        : "=S" (Addr), "=c" (Cnt)
        : "d" (Port), "0" (Addr), "1" (Cnt)
        : "memory", "cc"
    );
}


void EnableInterrupts(void)
{
	asm volatile("sti");
}

void DisableInterrupts(void)
{
	asm volatile("cli" ::: "memory");
}

void KernelHalt(void)
{
	DisableInterrupts();

	while(true) 
	{
		asm("hlt");
	}
}