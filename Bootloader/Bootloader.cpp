/*
    Copyright(C) 2025 NullPotOS Project. All Rights Reserved.

    Module name:
        Bootloader.cpp

    Description:
        This file is Bootloader of the NullPotOS.

    Author:
        LuoYuDian
        MaxSinoh

    Date:
        2025.1.20
*/

#include <Bootloader/Bootloader.hpp>
#include <Core/Exec/Elf/Elf.hpp>

Void CalcLoadAddressRange(Elf::Elf64Ehdr *Ehdr, UINT64 *First, UINT64 *Last)
{
    Elf::Elf64Phdr *Phdr = (Elf::Elf64Phdr *) ((UINT64) Ehdr + Ehdr->EPhoff);
    *First = 0xffffffffffffffff; // uint64 at max value
    *Last = 0; // uint64 at min value

    for (UINT16 i = 0; i < Ehdr->EPhnum; i++) 
    { 
        // everyon program header
        if (Phdr[i].PType != PtLoad)
        {
            continue; // if not PT_LOAD, continue
        }
        *First = Min(*First, Phdr[i].PVaddr);
        *Last = Max(*Last, Phdr[i].PVaddr + Phdr[i].PMemsz); // everyon program header
    }
}

Void CopyLoadSegments(Elf::Elf64Ehdr *Ehdr)
{
    Elf::Elf64Phdr *Phdr = (Elf::Elf64Phdr *) ((UINT64) Ehdr + Ehdr->EPhoff);
    for (UINT16 i = 0; i < Ehdr->EPhnum; i++) 
    { 
        // everyon program header
        if (Phdr[i].PType != PtLoad)
        {
            continue; // if not PT_LOAD, continue
        }

        UINT64 SegnInFile = (UINT64) Ehdr + Phdr[i].POffset; // segments at file
        Xmemcpy((void *) Phdr[i].PVaddr, (void *) SegnInFile, Phdr[i].PFilesz);
        UINT64 RemainBytes = Phdr[i].PMemsz - Phdr[i].PFilesz; 
        Xmemset((void *) (Phdr[i].PVaddr + Phdr[i].PFilesz), 0, RemainBytes); // is 0
    }
}

extern "C" EFI_STATUS EFIAPI UefiMain(IN EFI_HANDLE ImageHandle, IN struct EFI_SYSTEM_TABLE *SystemTable)
{

    UefiInit(ImageHandle, SystemTable);

    SystemTable->ConOut->SetAttribute(SystemTable->ConOut, EFI_WHITE);

    SystemTable->ConOut->ClearScreen(SystemTable->ConOut);

    SystemTable->ConOut->OutputString(SystemTable->ConOut, (unsigned short *)L"Copyright (C) 2025 NullPotOS Project, All rights reserved.\r\n\n");

    EFI_STATUS Status;
    EFI_PHYSICAL_ADDRESS EntryAddr;
    struct EFI_FILE_PROTOCOL *Root, *KernelFile;
    UINT64 KernelSize = 4194304;
    Void *KernelBuffer = Malloc(KernelSize);

    Status = SFSP->OpenVolume(SFSP, &Root); // Open root filesystem
    if (EFI_ERROR(Status))
    {
        SystemTable->ConOut->OutputString(SystemTable->ConOut, (unsigned short *)L"[FAIL] Loading File System\r\n");
        while (true)
        {

        }
    }
    SystemTable->ConOut->OutputString(SystemTable->ConOut, (unsigned short *)L"[PASS] Loading File System\r\n");

    Status = Root->Open(Root, &KernelFile, (unsigned short *)L"\\NullPotOS\\System\\Kernel.elf", EFI_FILE_MODE_READ, 0); // Open kernel file
    if (EFI_ERROR(Status))
    {
        SystemTable->ConOut->OutputString(SystemTable->ConOut, (unsigned short *)L"[FAIL] Loading Kernel Files\r\n");
        while (true)
        {

        }
    }
    SystemTable->ConOut->OutputString(SystemTable->ConOut, (unsigned short *)L"[PASS] Loading Kernel Files\r\n");

    Status = KernelFile->Read(KernelFile, &KernelSize, KernelBuffer);
    if (EFI_ERROR(Status))
    {
        SystemTable->ConOut->OutputString(SystemTable->ConOut, (unsigned short *)L"[FAIL] Loading Kernel Files\r\n");
        while (true)
        {

        }
    }
    SystemTable->ConOut->OutputString(SystemTable->ConOut, (unsigned short *)L"[PASS] Loading Kernel Files\r\n");

    Elf::Elf64Ehdr *Ehdr = (Elf::Elf64Ehdr *)KernelBuffer;
    UINT64 KernelFirstAddr, KernelLastAddr;
    CalcLoadAddressRange(Ehdr, &KernelFirstAddr, &KernelLastAddr);

    CopyLoadSegments(Ehdr);
    EntryAddr = Ehdr->EEntry;

    struct FrameBufferConfig config = 
    {
        (UINT8 *)GOP->Mode->FrameBufferBase, GOP->Mode->Info->PixelsPerScanLine,
		GOP->Mode->Info->HorizontalResolution, GOP->Mode->Info->VerticalResolution
    };

    switch (GOP->Mode->Info->PixelFormat)
    {
        case PixelRedGreenBlueReserved8BitPerColor: 
            config.PixelFormat = kRGBR; 
            break;
        case PixelBlueGreenRedReserved8BitPerColor: 
            config.PixelFormat = kBGRR; 
            break;
        default:
            SystemTable->ConOut->OutputString(SystemTable->ConOut, (unsigned short *)L"[FAIL] Loading Graphics\r\n");
            while (true)
            {

            }
    };
    SystemTable->ConOut->OutputString(SystemTable->ConOut, (unsigned short *)L"[PASS] Loading Graphics\r\n");

    BOOT_CONFIG BootConfig;
    BootConfig.MemoryMap.MapSize = 4096;
    BootConfig.MemoryMap.Buffer = NULL;
    BootConfig.MemoryMap.MapKey = 0;
    BootConfig.MemoryMap.DescriptorSize = 0;
    BootConfig.MemoryMap.DescriptorVersion = 0;
    GetMMP(&BootConfig.MemoryMap);
    SystemTable->ConOut->OutputString(SystemTable->ConOut, (unsigned short *)L"[PASS] Getting Memory Map\r\n\n");

    Kernel kernel = (Kernel)EntryAddr;
    SystemTable->ConOut->OutputString(SystemTable->ConOut, (unsigned short *)L"Operating System Boot Success.\r\n");
    kernel(&config, SystemTable, &BootConfig); // Jump to kernel

    SystemTable->ConOut->SetAttribute(SystemTable->ConOut, EFI_RED);

    return EFI_SUCCESS;
}