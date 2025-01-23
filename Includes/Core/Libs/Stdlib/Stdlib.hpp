/*
    Copyright(C) 2025 NullPotOS Project. All Rights Reserved.

    Module name:
        Stdlib.hpp

    Description:
        This header file is the standard library of the NullPotOS kernel.

    Author:
        LuoYuDian
        MaxSinoh

    Date:
        2025.1.21
 */

#ifndef STDLIB_HPP
#define STDLIB_HPP

#include <Types.hpp>

#define MAX_PRECISION (10)

static const double Rounders[MAX_PRECISION + 1] = 
{
	0.5,
	0.05,
	0.005,
	0.0005,
	0.00005,
	0.000005,
	0.0000005,
	0.00000005,
	0.000000005,
	0.0000000005,
	0.00000000005
};

void Delay(UINT32 Count);

void Hang(void);

bool IsDigit(int C);

int Atoi(char* Pstr);

char *GetFilename(char *path);

char *Ftoa(double f,char *buf,int precision);

#endif // STDLIB_HPP