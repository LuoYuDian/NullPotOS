/*
    Copyright(C) 2025 NullPotOS Project. All Rights Reserved.

    Module name:
        Io.hpp

    Description:
        This header file is the io function of the NullPotOS kernel.

    Author:
        LuoYuDian
        MaxSinoh

    Date:
        2025.1.21
 */

#ifndef IO_HPP
#define IO_HPP

#include <Types.hpp>
#include <Core/Libs/String/String.hpp>

void Outb(UINT16 Port,UINT8 Value);

void Outw(UINT16 Port,UINT16 Value);

void Outl(UINT16 Port,UINT32 Value);

UINT8 Inb(UINT16 Port);

UINT16 Inw(UINT16 Port);

UINT32 Inl(UINT16 Port);

void Insw(UINT16 Port,void *Buf,unsigned long N);

void Outsw(UINT16 Port,const void *Buf,unsigned long N);

void Insl(UINT32 Port,void *Addr,int Cnt);

void Outsl(UINT32 Port,const void *Addr,int Cnt);

UINT32 GetCr0(void);

void SetCr0(UINT32 Cr0);

void EnableInterrupts(void);
void DisableInterrupts(void);
void KernelHalt(void);

#endif // IO_HPP