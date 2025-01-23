/*
    Copyright(C) 2025 NullPotOS Project. All Rights Reserved.

    Module name:
        Beep.hpp

    Description:
        This header file is the beep driver of the NullPotOS kernel.

    Author:
        LuoYuDian
        MaxSinoh

    Date:
        2025.1.23
 */

#ifndef BEEP_HPP
#define BEEP_HPP

#include <Types.hpp>

void EnableBeep();
void DisableBeep();
void SystemBeep(int Hert);

#endif