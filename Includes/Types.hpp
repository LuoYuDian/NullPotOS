/*
    Copyright(C) 2025 NullPotOS Project. All Rights Reserved.

    Module name:
        Types.hpp

    Description:
        This header file contains the definitions of the basic types used in the NullPotOS project.
    
    Author:
        LuoYuDian
        MaxSinoh

    Date:
        2025-01-20
*/

#ifndef TYPES_HPP
#define TYPES_HPP

#ifdef __cplusplus
    #define NULL 0
#else
    #define NULL ((void *)0)
#endif

#define true 1
#define false 0

typedef __INTPTR_TYPE__				IntptrT;
typedef __UINTPTR_TYPE__			UintptrT;
typedef __INTPTR_TYPE__				SsizeT;
typedef __UINTPTR_TYPE__			SizeT;

typedef unsigned char				UChar;
typedef unsigned short				UShort;
typedef unsigned int				UInt;
typedef unsigned long				ULong;

typedef __UINT8_TYPE__  UINT8;
typedef __UINT16_TYPE__ UINT16;
typedef __UINT32_TYPE__ UINT32;
typedef __UINT64_TYPE__ UINT64;
typedef __INT8_TYPE__  INT8;
typedef __INT16_TYPE__ INT16;
typedef __INT32_TYPE__ INT32;
typedef __INT64_TYPE__ INT64;
typedef char Boolean;

#endif // TYPES_HPP