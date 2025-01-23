/*
    Copyright(C) 2025 NullPotOS Project. All Rights Reserved.

    Module name:
        Gdt.cpp

    Description:
        This file is the Gdt module of the NullPotOS kernel.

    Author:
        LuoYuDian
        MaxSinoh

    Date:
        2025.1.22
 */

#include <Types.hpp>
#include <Core/Kernel/Asm/Gdt/Gdt.hpp>
#include <Core/Drivers/View/Gop/Gop.hpp>
#include <Core/Kernel/Debug/Print/Print.hpp>

#define GdtLength 5
#define KernelDataSelector 0x10

GdtEntryT GdtEntries[GdtLength];
GdtPtrT GdtPtr;

static void GdtInstall(INT64 Num, UINT64 Base, UINT64 Limit, UINT8 Access, UINT8 Granularity)
{
    GdtEntries[Num].BaseLow		= (Base & 0xFFFF);
	GdtEntries[Num].BaseMiddle	= (Base >> 16) & 0xFF;
	GdtEntries[Num].BaseHigh		= (Base >> 24) & 0xFF;

	GdtEntries[Num].LimitLow		= (Limit & 0xFFFF);
	GdtEntries[Num].Granularity	= (Limit >> 16) & 0x0F;

	GdtEntries[Num].Granularity	|= Granularity & 0xF0;
	GdtEntries[Num].Access			= Access;
}
void _InitGdt(void)
{

	GdtPtr.Limit 	= sizeof(GdtEntryT) * GdtLength - 1;
	GdtPtr.Base		= (UINT64)&GdtEntries;

	GdtInstall(0, 0, 0, 0, 0);
	GdtInstall(1, 0, 0xFFFFFFFF, 0x9B, 0xA0);
	GdtInstall(2, 0, 0xFFFFFFFF, 0x93, 0xA0);
	GdtInstall(3, 0, 0xFFFFFFFF, 0xFB, 0xA0);
	GdtInstall(4, 0, 0xFFFFFFFF, 0xF3, 0xA0);

	asm volatile 
	(
		"lgdt [GdtPtr]\n"
		:
		: [GdtPtr] "*p" (&GdtPtr)
	);
	asm volatile
	(
		"mov %[Dsel], %%ds\n"
		"mov %[Dsel], %%fs\n"
		"mov %[Dsel], %%gs\n"
		"mov %[Dsel], %%es\n"
		"mov %[Dsel], %%ss\n"
		:
		: [Dsel] "rm" (KernelDataSelector)
	);  
}