/*
    Copyright(C) 2025 NullPotOS Project. All Rights Reserved.

    Module name:
        Print.cpp

    Description:
        This file is the print library of the NullPotOS kernel.

    Author:
        LuoYuDian
        MaxSinoh

    Date:
        2025.1.21
 */

#include <Core/Drivers/View/Gop/Gop.hpp>
#include <Core/Libs/Args/Vargs.hpp>
#include <Core/Libs/Stdlib/Stdlib.hpp>
#include <Core/Libs/String/String.hpp>
#include <Core/Kernel/Debug/Print/Print.hpp>

#define IsDigit(c)	((c) >= '0' && (c) <= '9')
#define ZEROPAD		1
#define SIGN		2
#define PLUS    	4
#define SPACE		8
#define LEFT		16
#define SPECIAL		32
#define SMALL		64

#define DoDiv(n,base) ({														\
        int __res;																\
        __asm__("divl %4":"=a" (n),"=d" (__res):"0" (n),"1" (0),"r" (base));	\
        __res; })


void PrintBusy(const char *Str)
{
	Print("[");
	PrintColor(GOP_COLOR_RED, " ** ");
	Print("]");
	Print("%s", Str);
}

void PrintSucc(const char *Str)
{
	Print("[");
	PrintColor(GOP_COLOR_GREEN, "PASS");
	Print("]");
	Print("%s", Str);
}

void PrintWarn(const char *Str)
{
	Print("[");
	PrintColor(GOP_COLOR_ORANGE, "WARN");
	Print("]");
	Print("%s", Str);
}

void PrintErro(const char *Str)
{
	Print("[");
	PrintColor(GOP_COLOR_RED, "ERRO");
	Print("]");
	Print("%s", Str);
}

void Print(const char *Format,...)
{
	static char buff[1024];
	VaList Args;
	int I;

	VaStart(Args,Format);
	I = VsPrint(buff,Format,Args);
	VaEnd(Args);

	buff[I] = '\0';
	GopPutString(buff);
}

void PrintColor(int Fore,const char *Format,...)
{
	static char Buff[1024];
	VaList Args;
	int I;

	VaStart(Args,Format);
	I = VsPrint(Buff,Format,Args);
	VaEnd(Args);

	Buff[I] = '\0';
	GopPutStringColor(Buff,Fore);
}

static int SkipAtoi(const char **s)
{
	int I = 0;

	while (IsDigit(**s)) 
	{
		I = I * 10 + *((*s)++) - '0';
	}
	return I;
}

static char *Number(char *Str,int Num,int Base,int Size,int Precision,int Type)
{
	char C, Sign, Tmp[36];
	const char *Digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int I;

	if (Type & SMALL) 
	{
		Digits ="0123456789abcdefghijklmnopqrstuvwxyz";
	}
	if (Type & LEFT) 
	{
		Type &= ~ZEROPAD;
	}
	if (Base < 2 || Base > 36) 
	{
		return 0;
	}

	C = (Type & ZEROPAD) ? '0' : ' ' ;

	if (Type & SIGN && Num < 0) 
	{
		Sign = '-';
		Num = -Num;
	} 
	else 
	{
		Sign = (Type&PLUS) ? '+' : ((Type&SPACE) ? ' ' : 0);
	}
	
	if (Sign) 
	{
		Size--;
	}
	
	if (Type & SPECIAL) 
	{
		if (Base == 16) 
		{
			Size -= 2;
		} 
		else if (Base == 8) 
		{
			Size--;
		}
	}
	I = 0;
	if (Num == 0) 
	{
		Tmp[I++] = '0';
	} 
	else 
	{
		while (Num != 0) 
		{
			Tmp[I++] = Digits[DoDiv(Num,Base)];
		}
	}
	if (I > Precision) 
	{
		Precision = I;
	}
	Size -= Precision;

	if (!(Type&(ZEROPAD+LEFT))) 
	{
		while (Size-- > 0) 
		{
			*Str++ = ' ';
		}
	}
	if (Sign) 
	{
		*Str++ = Sign;
	}
	
	if (Type & SPECIAL) 
	{
		if (Base == 8) 
		{
			*Str++ = '0';
		} 
		else if (Base == 16) 
		{
			*Str++ = '0';
			*Str++ = Digits[33];
		}
	}
	if (!(Type&LEFT)) 
	{
		while (Size-- > 0) 
		{
			*Str++ = C;
		}
	}
	while (I < Precision--) 
	{
		*Str++ = '0';
	}
	while (I-- > 0) 
	{
		*Str++ = Tmp[I];
	}
	while (Size-- > 0) 
	{
		*Str++ = ' ';
	}
	return Str;
}

int VsPrint(char *Buff,const char *Format,VaList Args)
{
	int Len;
	int I;
	char *Str;
	char *S;
	int *Ip;

	int Flags;

	int FieldWidth;
	int Precision;

	for (Str = Buff ; *Format ; ++Format) 
	{
		if (*Format != '%') 
		{
			*Str++ = *Format;
			continue;
		}
		Flags = 0;
		repeat:
			++Format;
		switch (*Format) 
		{
				case '-': 
					Flags |= LEFT;
					goto repeat;
				case '+': 
					Flags |= PLUS;
					goto repeat;
				case ' ': 
					Flags |= SPACE;
					goto repeat;
				case '#': 
					Flags |= SPECIAL;
					goto repeat;
				case '0': 
					Flags |= ZEROPAD;
					goto repeat;
			}

		FieldWidth = -1;
		if (IsDigit(*Format))
		{
			FieldWidth = SkipAtoi(&Format);
		} 
		else if (*Format == '*') 
		{
			FieldWidth = VaArg(Args, int);
			if (FieldWidth < 0) 
			{
				FieldWidth = -FieldWidth;
				Flags |= LEFT;
			}
		}

		Precision = -1;
		if (*Format == '.') 
		{
			++Format;	
			if (IsDigit(*Format)) 
			{
				Precision = SkipAtoi(&Format);
			} 
			else if (*Format == '*') 
			{	
				Precision = VaArg(Args, int);
			}
			if (Precision < 0) 
			{
				Precision = 0;
			}
		}

		if (*Format == 'h' || *Format == 'l' || *Format == 'L') 
		{
			++Format;
		}
		switch (*Format) 
		{
			case 'c':
				if (!(Flags & LEFT)) 
				{
					while (--FieldWidth > 0) 
					{
						*Str++ = ' ';
					}
				}
				*Str++ = (unsigned char) VaArg(Args, int);
				while (--FieldWidth > 0) 
				{
					*Str++ = ' ';
				}
				break;
			case 's':
				S = VaArg(Args, char *);
				Len = Strlen(S);
				if (Precision < 0) 
				{
					Precision = Len;
				} 
				else if (Len > Precision) 
				{
					Len = Precision;
				}
				if (!(Flags & LEFT)) 
				{
					while (Len < FieldWidth--) 
					{
						*Str++ = ' ';
					}
				}
				for (I = 0; I < Len; ++I) 
				{
					*Str++ = *S++;
				}
				while (Len < FieldWidth--)
				{
					*Str++ = ' ';
				}
				break;
			case 'o':
				Str = Number(Str, VaArg(Args, unsigned long), 8, FieldWidth, Precision, Flags);
				break;
			case 'p':
				if (FieldWidth == -1) 
				{
					FieldWidth = 8;
					Flags |= ZEROPAD;
				}
				Str = Number(Str, (unsigned long) VaArg(Args, void *), 16, FieldWidth, Precision, Flags);
				break;
			case 'x':
				Flags |= SMALL;
			case 'X':
				Str = Number(Str, VaArg(Args, unsigned long), 16, FieldWidth, Precision, Flags);
				break;
			case 'd':
			case 'i':
				Flags |= SIGN;
			case 'u':
				Str = Number(Str, VaArg(Args, unsigned long), 10, FieldWidth, Precision, Flags);
				break;
			case 'f':
				Str = Ftoa(VaArg(Args, double), Str, Precision);
				break;
			case 'b':
				Str = Number(Str, VaArg(Args, unsigned long), 2, FieldWidth, Precision, Flags);
				break;
			case 'n':
				Ip = VaArg(Args, int *);
				*Ip = (Str - Buff);
				break;
			default:
				if (*Format != '%')
				{
					*Str++ = '%';
				}
				if (*Format)
				{
					*Str++ = *Format;
				} 
				else 
				{
					--Format;
				}
				break;
			}
		}
	*Str = '\0';
	return (Str - Buff);
}

void SPrint(char *Str,const char *Fmt,...)
{
	VaList Arg;
	VaStart(Arg,Fmt);
	VsPrint(Str,Fmt,Arg);
	VaEnd(Arg);
}