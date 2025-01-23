/*
    Copyright(C) 2025 NullPotOS Project. All Rights Reserved.

    Module name:
        Kernel.hpp

    Description:
        This header file is the kernel of the NullPotOS kernel.

    Author:
        LuoYuDian
        MaxSinoh

    Date:
        2025.1.22
 */

#ifndef KERNEL_HPP
#define KERNEL_HPP

#include <Types.hpp>
#include <Firmware/Uefi/Uefi.hpp>

extern "C" void _KernelEntry(FrameBufferConfig &Fbc,EFI_SYSTEM_TABLE &SystemTable,BOOT_CONFIG *BootConfig);
extern "C" void _KernelMain();

#endif // KERNEL_HPP