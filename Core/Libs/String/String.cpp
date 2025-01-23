/*
    Copyright(C) 2025 NullPotOS Project. All Rights Reserved.

    Module name:
        String.cpp

    Description:
        This file is the string library of the NullPotOS kernel.

    Author:
        LuoYuDian
        MaxSinoh

    Date:
        2025.1.21
 */

#include <Core/Libs/String/String.hpp>
#include <Types.hpp>

int Memcmp(const void* Buffer1,const void* Buffer2,UINT32 Count)
{
	if(!Count) 
	{
		return 0;
	}

	while(Count-- && *(char*)Buffer1 == *(char*)Buffer2) 
	{
		Buffer1 = (char*)Buffer1 + 1;
		Buffer2 = (char*)Buffer2 + 1;
	}

	return( *((UINT8 *)Buffer1) - *((UINT8 *)Buffer2) );    
}

void Memcpy(UINT8 *Dest,const UINT8 *Src,UINT32 Len)
{
	UINT8 *Sr = (UINT8 *)Src;
	UINT8 *Dst = Dest;

	while (Len != 0) 
	{
		*Dst++ = *Sr++;
		Len--;
	}
}

void Memset(void *Dest,UINT8 Val,UINT32 Len)
{
	for (UINT8 *Dst = (UINT8 *)Dest; Len != 0; Len--) 
	{
		*Dst++ = Val;
	}
}

void Bzero(void *Dest,UINT32 Len)
{
	Memset(Dest, 0, Len);
}

void Memclean(char *S,UINT32 Len)
{
	int I;
	for (I = 0; I != Len; I++) 
	{
		S[I] = 0;
	}
	return;
}

int Strcmp(const char *Dest,const char *Src)
{
	int Ret = 0 ;

	while(!(Ret = *(unsigned char *)Src - *(unsigned char *)Dest) && *Dest) 
	{
		++Src;
		++Dest;
	}
	if (Ret < 0) 
	{
		Ret = -1;
	}
	else if (Ret > 0) 
	{
		Ret = 1;
	}
	return Ret;
}

char *Strcpy(char *Dest,const char *Src)
{
	char *Tmp = Dest;

	while (*Src) 
	{
		*Dest++ = *Src++;
	}
	*Dest = '\0';	
	return Tmp;
}

char *Strncpy(char *Dest,const char *Src,UINT32 Len)
{
	char *Dst = Dest;

	while (Len > 0) 
	{
		while (*Src)
		{
			*Dst++ = *Src++;
		}
		Len--;
	}
	*Dst = '\0';
	return Dst;
}

char *Strcat(char *Dest,const char *Src)
{
	char *Cp = Dest;

	while (*Cp) 
	{
		Cp++;
	}
	while ((*Cp++ = *Src++))
	{

	}
	return Dest;
}

char *Strchr(char *Str,int C)
{
	for (; *Str != 0; ++Str) 
	{
		if (*Str == C) 
		{
			return Str;
		}
	}
	return 0;
}

int Strlen(const char *Src)
{
	const char *Eos = Src;

	while (*Eos++)
	{

	}
	return (Eos - Src - 1);
}

void DeleteChar(char *Str,int Pos)
{
	int I;
	for (I = Pos; I < Strlen(Str); I++) 
	{
		Str[I] = Str[I + 1];
	}
}

void InsertChar(char *Str,int Pos,char Ch)
{
	int I;
	for (I = Strlen(Str); I >= Pos; I--) 
	{
		Str[I + 1] = Str[I];
	}
	Str[Pos] = Ch;
}

void InsertStr(char *Str,char *InsertStr,int Pos)
{
	for (int I = 0; I < Strlen(InsertStr); I++) 
	{
		InsertChar(Str, Pos + I, InsertStr[I]);
	}
}

char *Strupr(char *Src)
{
	while (*Src != '\0')
	{
		if (*Src >= 'a' && *Src <= 'z')
		{
			*Src -= 32;
		}
		Src++;
	}
	return Src;
}

char *Strlwr(char *Src)
{
	while (*Src != '\0')
	{
		if (*Src > 'A' && *Src <= 'Z')
		{ 
			*Src += 32;
		}
		Src++;
	}
	return Src;
}