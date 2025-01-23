/*
    Copyright(C) 2025 NullPotOS Project. All Rights Reserved.

    Module name:
        Bmp.cpp

    Description:
        This file is the Bmp module of the NullPotOS kernel.

    Author:
        LuoYuDian
        MaxSinoh

    Date:
        2025.1.22
 */

#include <Types.hpp>
#include <Core/Kernel/Graphics/Bmp/Bmp.hpp>
#include <Core/Drivers/View/Gop/Gop.hpp>
#include <Core/Kernel/Debug/Print/Print.hpp>

void DrawBmp(BmpT *Bmp,UINT32 X,UINT32 Y,bool IsTransparent)
{
    if (Bmp->Magic != 0x4d42)
    {
        PrintErro("Is noy a BMP file!");
        return;
    }

    UINT8 *Data = (UINT8 *)Bmp + Bmp->BmpDataOffset;

    if (Bmp->BitsPerPixel == 24)
    {
        for (UINT32 YOffset = 0; YOffset < Bmp->FrameHeight; ++YOffset)
        {
            for (UINT32 XOffset = 0; XOffset < Bmp->FrameWidth; ++XOffset)
            {
                UINT32 Offset = (YOffset * Bmp->FrameWidth + XOffset) * 3;
                UINT8 B = Data[Offset + 0];
                UINT8 G = Data[Offset + 1];
                UINT8 R = Data[Offset + 2];
                UINT32 Color = (R << 16) | (G << 8) | B;
                if (IsTransparent && Color == 0)
                {
                    continue;
                }
                GopDrawPixel(X + XOffset, Y + Bmp->FrameHeight - 1 - YOffset, Color);
            }
        }
    }
    else if (Bmp->BitsPerPixel == 32)
    {
        for (UINT32 YOffset = 0; YOffset < Bmp->FrameHeight; ++YOffset)
        {
            for (UINT32 XOffset = 0; XOffset < Bmp->FrameWidth; ++XOffset)
            {
                UINT32 Offset = (YOffset * Bmp->FrameWidth + XOffset) * 4;
                UINT8 B = Data[Offset + 0];
                UINT8 G = Data[Offset + 1];
                UINT8 R = Data[Offset + 2];
                UINT8 A = Data[Offset + 3];
                UINT32 Color = (R << 16) | (G << 8) | B;
                if (IsTransparent && A == 0)
                {
                    continue;
                }
                GopDrawPixel(X + XOffset, Y + Bmp->FrameHeight - 1 - YOffset, Color);
            }
        }
    }
}