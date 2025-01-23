/*
    Copyright(C) 2025 NullPotOS Project. All Rights Reserved.

    Module name:
        String.hpp

    Description:
        This header file is the string library of the NullPotOS kernel.

    Author:
        LuoYuDian
        MaxSinoh

    Date:
        2025.1.20
 */

#ifndef STRING_HPP
#define STRING_HPP

#include <Types.hpp>

int Memcmp(const void* Buffer1,const void* Buffer2,SizeT Count);

void Memcpy(UINT8 *Dest,const UINT8 *Src,UINT32 Len);

void Memset(void *Dest,UINT8 Val,UINT32 Len);

void Bzero(void *Dest,UINT32 Len);

void Memclean(char *s,int len);

int Strcmp(const char *Str1,const char *Str2);

char *Strcpy(char *Dest,const char *Src);

char *Strncpy(char *Dest,const char *Src,UINT32 Len);

char *Strcat(char *Dest,const char *Src);

char *Strchr(char *Str,int C);

int Strlen(const char *Src);

void DeleteChar(char *Str,int Pos);

void InsertChar(char *Str,int Pos,char Ch);

void InsertStr(char *Str,char *InsertStr,int Pos);

char *Strupr(char *Src);

char *Strlwr(char *Src);

#endif // STRING_HPP