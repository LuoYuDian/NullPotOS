/*
    Copyright(C) 2025 NullPotOS Project. All Rights Reserved.

    Module name:
        Math.hpp

    Description:
        This file is the math function of the NullPotOS kernel.

    Author:
        LuoYuDian
        MaxSinoh

    Date:
        2025.1.21
 */

#include <Core/Libs/Math/Math.hpp>

double Sin(double X)
{
	asm volatile
    (
        "fldl %0 \n"
        "fsin \n"
        "fstpl %0\n"
        : "+m"(X)
	);
	return X;
}

double Cos(double X)
{
	asm volatile
    (
        "fldl %0 \n"
        "fcos \n"
        "fstpl %0\n"
        : "+m"(X)
	);
	return X;
}

double Tan(double X)
{
	asm volatile
    (
        "fldl %0 \n"
        "fptan \n"
        "fstpl %0\n"
        : "+m"(X)
	);
	return X;
}

double Sqrt(double X)
{
	asm volatile
    (
        "fldl %0 \n"
        "fsqrt \n"
        "fstpl %0\n"
        : "+m"(X)
	);
	return X;
}

double Log2(double X)
{
	asm volatile
    (
        "fld1 \n"
        "fldl %0 \n"
        "fyl2x \n"
        "fwait \n"
        "fstpl %0\n"
        : "+m"(X)
	);
	return X;
}