/*
    Copyright(C) 2025 NullPotOS Project. All Rights Reserved.

    Module name:
        Bmp.hpp

    Description:
        This header file is used Bmp of the NullPotOS.

    Author:
        LuoYuDian
        MaxSinoh
    Date:
        2025.1.21
*/

#ifndef BMP_HPP
#define BMP_HPP

#include <Types.hpp>

typedef struct 
{
	UINT16 Magic;
	UINT32 FileSize;
	UINT32 Reserved;
	UINT32 BmpDataOffset;

	
	UINT32 BmpInfoSize;
	UINT32 FrameWidth;
	UINT32 FrameHeight;
	UINT16 ReservedValue;
	UINT16 BitsPerPixel;
	UINT32 CompressionMode;
	UINT32 FrameSize;
	UINT32 HorizontalResolution;
	UINT32 VerticalResolution;
	UINT32 UsedColorCount;
	UINT32 ImportantColorCount;
} __attribute__((packed)) BmpT;

void DrawBmp(BmpT *Bmp,UINT32 X,UINT32 Y,bool IsTransparent);

#endif // BMP_HPP