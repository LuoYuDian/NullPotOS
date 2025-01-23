/*
    Copyright(C) 2025 NullPotOS Project. All Rights Reserved.

    Module name:
        Vargs.hpp

    Description:
        This header file is the standard library of the NullPotOS kernel.

    Author:
        LuoYuDian
        MaxSinoh

    Date:
        2025.1.20
 */

#ifndef VARGS_HPP
#define VARGS_HPP

typedef __builtin_va_list VaList;

#define VaStart(ap, last)	(__builtin_va_start(ap, last))
#define VaArg(ap, type)	(__builtin_va_arg(ap, type))
#define VaEnd(ap)

#endif // VARGS_HPP