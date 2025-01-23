/*
    Copyright(C) 2025 NullPotOS Project. All Rights Reserved.

    Module name:
        Gop.hpp

    Description:
        This header file is the GOP driver of the NullPotOS kernel.

    Author:
        LuoYuDian
        MaxSinoh

    Date:
        2025.1.21
 */

#ifndef GOP_HPP
#define GOP_HPP

extern "C" 
{
	#include <Firmware/UEFI/Uefi.hpp>
}

// Color
#define GOP_COLOR_WHITE 	0xffffff
#define GOP_COLOR_GREEN 	0x00ff00
#define GOP_COLOR_RED   	0xff0000
#define GOP_COLOR_BLUE  	0x0000ff
#define GOP_COLOR_YELLOW 	0xffff00
#define GOP_COLOR_BLACK 	0x000000
#define GOP_COLOR_CYAN 		0x00ffff
#define GOP_COLOR_PURPLE 	0xff00ff
#define GOP_COLOR_ORANGE 	0xffff00

void GetVInfo(FrameBufferConfig &Fbc);

void GopClear(void);

void GopClearColor(int Color);

void GopWriteNewline(void);

void GopScroll(void);

void GopDrawPixel(UINT32 X,UINT32 Y,UINT32 Color);

void GopDrawRect(int X0,int Y0,int X1,int Y1,int Color);

void GopDrawChar(char C,INT32 X,INT32 Y,int Color);

void GopPutChar(char C,int Color);

void GopPutString(const char *Str);

void GopPutStringColor(const char *Str,int Color);

void GopToSerial(int Op);

void GopSetForeColor(int Color);

void GopSetBackColor(int Color);

#endif // GOP_HPP