/*
    Copyright(C) 2025 NullPotOS Project. All Rights Reserved.

    Module name:
        Stdlib.hpp

    Description:
        This file is the stdlib function of the NullPotOS kernel.

    Author:
        LuoYuDian
        MaxSinoh

    Date:
        2025.1.21
 */

#include <Core/Libs/Stdlib/Stdlib.hpp>
#include <Core/Libs/String/String.hpp>

void Delay(UINT32 Count)
{
	while (Count--)
	{

	}
}

void Hang(void)
{
	while (true)
	{

	}
}

bool IsDigit(int C)
{
	return C >= '0' && C <= '9';
}

int Atoi(char* Pstr)
{
	int RetInteger = 0;
	int IntegerSign = 1;

	if (*Pstr == '-')
	{
		IntegerSign = -1;
	} 
	if (*Pstr == '-' || *Pstr == '+')
	{
		Pstr++;
	} 
	while (*Pstr >= '0' && *Pstr <= '9') 
	{
		RetInteger = RetInteger * 10 + *Pstr - '0';
		Pstr++;
	}
	RetInteger = IntegerSign * RetInteger;
	return RetInteger;
}

char *GetFileName(char *Path)
{
	char Ch = '/';
	char *FileName = Strchr(Path, Ch) + 1;
	return FileName;
}

char *Ftoa(double F,char *Buf,int Precision)
{
	char *Ptr = Buf;
	char *P = Ptr;
	char *P1;
	char C;
	long IntPart;

	if (Precision > MAX_PRECISION)
	{
		Precision = MAX_PRECISION;
	}

	if (F < 0)
	{
		F = -F;
		*Ptr++ = '-';
	}
	if (Precision < 0)
	{
		if (F < 1.0)
		{
			Precision = 6;
		}
		else if (F < 10.0)
		{
			Precision = 5;
		} 
		else if (F < 100.0)
		{
			Precision = 4;
		}
		else if (F < 1000.0)
		{
			Precision = 3;	
		} 
		else if (F < 10000.0)
		{
			Precision = 2;
		}		
		else if (F < 100000.0)
		{
			Precision = 1;
		}
		else
		{
			Precision = 0;
		} 
	}
	if (Precision)
	{
		F += Rounders[Precision];
	}
	IntPart = F;
	F -= IntPart;
	if (!IntPart)
	{
		*Ptr++ = '0';
	}
	else
	{
		P = Ptr;
		while (IntPart)
		{
			*P++ = '0' + IntPart % 10;
			IntPart /= 10;
		}
		P1 = P;
		while (P > Ptr)
		{
			C = *--P;
			*P = *Ptr;
			*Ptr++ = C;
		}
		Ptr = P1;
	}
	if (Precision)
	{
		*Ptr++ = '.';
		while (Precision--)
		{
			F *= 10.0;
			C = F;
			*Ptr++ = '0' + C;
			F -= C;
		}
	}
	*Ptr = 0;
	return Ptr;
}