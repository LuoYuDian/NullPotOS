/*
    Copyright(C) 2025 NullPotOS Project. All Rights Reserved.

    Module name:
        Main.cpp

    Description:
        This file is the main file of the NullPotOS kernel.

    Author:
        LuoYuDian
        MaxSinoh

    Date:
        2025.1.21
 */

#include <Types.hpp>
#include <Version.hpp>
#include <Logo.hpp>
#include <Core/Kernel/Kernel.hpp>
#include <Firmware/Uefi/Uefi.hpp>
#include <Core/Exec/Elf/Elf.hpp>
#include <Core/Libs/Stdlib/Stdlib.hpp>
#include <Core/Drivers/View/Gop/Gop.hpp>
#include <Core/Kernel/Debug/Print/Print.hpp>
#include <Core/Kernel/Asm/A20/A20.hpp>
#include <Core/Kernel/Asm/Gdt/Gdt.hpp>
#include <Core/Kernel/Graphics/Bmp/Bmp.hpp>

// Kernel init
extern "C" void _KernelEntry(FrameBufferConfig &Fbc,EFI_SYSTEM_TABLE &SystemTable,BOOT_CONFIG *BootConfig)
{
    GetVInfo(Fbc); // Get video information
    GopClear(); // Clear screen

    // Draw logo
    DrawBmp((BmpT *)Logo, Fbc.HorizontalResolution - 184 - 20, 20, 1);

    // Print kernel version
    PrintColor(GOP_COLOR_CYAN, "NullPotOS %s\n", KERNEL_VERSION);
	PrintColor(GOP_COLOR_CYAN, PROJECKT_COPY);

    // Enable A20
    EnableA20();
    // Load Gdt
    _InitGdt();

    _KernelMain(); // Jump kernel main
}

// Kernel main
extern "C" void _KernelMain()
{
    KernelHalt();
}