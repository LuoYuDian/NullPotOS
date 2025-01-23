/*
    Copyright(C) 2025 NullPotOS Project. All Rights Reserved.

    Module name:
        Gop.cpp

    Description:
        This file is the GOP driver of the NullPotOS kernel.

    Author:
        LuoYuDian
        MaxSinoh

    Date:
        2025.1.20
 */

#include <Types.hpp>
#include <Core/Drivers/Communicate/Serial/Serial.hpp>
#include <Firmware/Uefi/Uefi.hpp>
#include <Core/Libs/String/String.hpp>
#include <Core/Drivers/View/Gop/Gop.hpp>
#include <Core/Libs/Stdlib/Stdlib.hpp>

extern UINT8 AscFont[];

UINT32 *GopMem;
UINT32 Width, Height;
UINT32 ForeColor, BackColor;
INT32 X, Y;
INT32 Cx, Cy;
UINT32 CWidth, CHeight;

int GopSerial = 0;

void GetVInfo(FrameBufferConfig &Fbc)
{
	GopMem = (UINT32 *)Fbc.FrameBuffer;
	Width = Fbc.HorizontalResolution;
	Height = Fbc.VerticalResolution;

	GopSetForeColor(0xffffff);
	GopSetBackColor(0x000000);

	X = 2;
	Y = Cx = Cy = 0;

	CWidth = Width / 9;
	CHeight = Height / 16;
}

void GopClear(void)
{
	for (UINT32 i = 0; i < (Width * (Height)); i++) 
	{
		GopMem[i] = BackColor;
	}
	X = 2;
	Y = 0;
	Cx = Cy = 0;
}

void GopClearColor(int Color)
{
	GopSetBackColor(Color);
	for (UINT32 i = 0; i < (Width * (Height)); i++) 
	{
		GopMem[i] = Color;
	}
	X = 2;
	Y = 0;
	Cx = Cy = 0;
}

void GopWriteNewline(void)
{
	GopScroll();
	Cx = 0;
	Cy++;
}

void GopScroll(void)
{
	if ((UINT32)Cx > CWidth) 
	{
		Cx = 0;
		Cy++;
	} 
	else 
	{
		Cx++;
	}

	if ((UINT32)Cy >= CHeight) 
	{
		Cy = CHeight - 1;
		Memcpy(reinterpret_cast<UINT8 *>(GopMem), reinterpret_cast<UINT8 *>(GopMem + Width * 16 * sizeof(UINT8)), Width * (Height - 16) * sizeof(UINT32));
		for (UINT32 i = (Width * (Height - 16)); i != (Width * Height); i++) 
		{
			GopMem[i] = BackColor;
		}
	}
}

void GopDrawPixel(UINT32 X,UINT32 Y,UINT32 Color)
{
	if (X >= Width || Y >= Height) 
	{
		return;
	}
	Color = (Color & 0xff) | (Color & 0xff00) | (Color & 0xff0000);
	UINT32 *p = (UINT32 *)GopMem + Y * Width + X;
	*p = Color;
}

void GopDrawRect(int X0,int Y0,int X1,int Y1,int Color)
{
	int x, y;
	for (y = Y0; y <= Y1; y++) 
	{
		for (x = X0; x <= X1; x++) 
		{
			GopMem[y * Width + x] = Color;
		}
	}
}

void GopDrawChar(char C,INT32 X,INT32 Y,INT32 Color)
{
	UINT8 *Font = AscFont;
	Font += C * 16;

	for (int i = 0; i < 16; i++) 
	{
		for (int j = 0; j < 9; j++) 
		{
			if (Font[i] & (0x80 >> j)) 
			{
				GopMem[(Y + i) * Width + X + j] = Color;
			} 
			else
			{
				GopMem[(Y + i) * Width + X + j] = BackColor;
			}
		}
	}
}

void GopPutChar(char C,int Color)
{
	if (C == '\n') 
	{
		GopScroll();
		Cx = 0;
		Cy++;
		return;
	} 
	else if (C == '\r') 
	{
		Cx = 0;
		return;
	} 
	else if(C == '\t') 
	{
		for (int i = 0; i < 4; i++) GopPutChar(' ', Color);
		return;
	} 
	else if (C == '\b' && Cx > 0) 
	{
		Cx -= 1;
		if (Cx == 0) 
		{
			Cx = CWidth - 1;
			if (Cy != 0) Cy -= 1;
			if (Cy == 0) Cx = 0, Cy = 0;
		}
		int x = (Cx+1) * 9 - 7;
		int y = Cy * 16;
		GopDrawRect(x, y, x + 9, y + 16, BackColor);
		return;
	}
	GopScroll();
	GopDrawChar(C, Cx * 9 - 7, Cy * 16, Color);
}

void GopPutString(const char *Str)
{
	for (;*Str; ++Str) 
	{
		char C = *Str;
		GopPutChar(C, ForeColor);
	}
}

void GopPutStringColor(const char *Str,int Color)
{
	for (;*Str; ++Str) 
	{
		char C = *Str;
		GopPutChar(C, Color);
	}
}

void ToSerial(int Op)
{
	if (Op == 1)
	{
		GopSerial = 1;
	}
	else
	{
		GopSerial = 0;
	}
}

void GopSetForeColor(int Color)
{
	ForeColor = Color;
}

void GopSetBackColor(int Color)
{
	BackColor = Color;
}