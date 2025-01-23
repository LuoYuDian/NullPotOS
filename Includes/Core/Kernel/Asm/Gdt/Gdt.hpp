/*
    Copyright(C) 2025 NullPotOS Project. All Rights Reserved.

    Module name:
        Gdt.hpp

    Description:
        This header file is the Gdt module of the NullPotOS kernel.

    Author:
        LuoYuDian
        MaxSinoh

    Date:
        2025.1.22
 */

#ifndef GDT_HPP
#define GDT_HPP 

#include <Types.hpp>
#include <Core/Kernel/Asm/Gdt/Gdt.hpp>

typedef struct GdtEntryT 
{
	UINT16 LimitLow;
	UINT16 BaseLow;
	UINT8 BaseMiddle;
	UINT8 Access;
	UINT8 Granularity;
	UINT8 BaseHigh;
} __attribute__((packed)) GdtEntryT;

typedef struct GdtPtrT
{
	UINT16 Limit;
	UINT64 Base;
} __attribute__((packed)) GdtPtrT;

static void GdtInstall(INT64 Num, UINT64 Base, UINT64 Limit, UINT8 Access, UINT8 gran);
void _InitGdt(void);
#endif