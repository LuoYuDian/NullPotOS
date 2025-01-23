/*
    Copyright(C) 2025 NullPotOS Project. All Rights Reserved.

    Module name:
        Print.hpp

    Description:
        This header file is the print function of the NullPotOS kernel.

    Author:
        LuoYuDian
        MaxSinoh

    Date:
        2025.1.20
 */

#ifndef PRINT_HPP
#define PRINT_HPP

#include <Core/Libs/Args/Vargs.hpp>
#include <Core/Drivers/View/Gop/Gop.hpp>

void Print(const char *Format,...);

void PrintColor(int Fore,const char *Format,...);

void PrintBusy(const char *Str);

void PrintSucc(const char *Str);

void PrintWarn(const char *Str);

void PrintErro(const char *Str);

int VsPrint(char *Buff,const char *Format,VaList Args);

void SPrint(char *Str,const char *Fmt,...);

#endif // PRINT_HPP