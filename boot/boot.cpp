// 创建于2024.12.22
// NullPotOS bootloader

#include <boot/boot.hpp>
#include <boot/elf.hpp>
#pragma once

namespace elf
{ 
    void calc_load_address_range(elf64_ehdr *ehdr, uint64 *first, uint64 *last)
    {
        elf::elf64_phdr *phdr = (elf64_phdr *) ((uint64) ehdr + ehdr->e_phoff);
        *first = 0xffffffffffffffff; // uint64 at max value
        *last = 0; // uint64 at min value

        for (uint16 i = 0; i < ehdr->e_phnum; i++) 
        { 
            // everyon program header
            if (phdr[i].p_type != PT_LOAD)
            {
                continue; // if not PT_LOAD, continue
            }
            *first = min(*first, phdr[i].p_vaddr);
            *last = max(*last, phdr[i].p_vaddr + phdr[i].p_memsz); // everyon program header
        }
    }

    void copy_load_segments(elf64_ehdr *ehdr)
    {
        elf64_phdr *phdr = (elf64_phdr *) ((uint64) ehdr + ehdr->e_phoff);
        for (uint16 i = 0; i < ehdr->e_phnum; i++) 
        { 
            // everyon program header
            if (phdr[i].p_type != PT_LOAD)
            {
                continue; // if not PT_LOAD, continue
            }

            uint64 segm_in_file = (uint64) ehdr + phdr[i].p_offset; // segments at file
            xmemcpy((void *) phdr[i].p_vaddr, (void *) segm_in_file, phdr[i].p_filesz);
            uintn remain_bytes = phdr[i].p_memsz - phdr[i].p_filesz; 
            xmemset((void *) (phdr[i].p_vaddr + phdr[i].p_filesz), 0, remain_bytes); // is 0
        }
    }
}
extern "C" EFI_STATUS EFIAPI _bootloadermain(EFI_HANDLE ImageHandle,struct EFI_SYSTEM_TABLE *SystemTable)
{
    // 初始化UEFI
    efi_init(ImageHandle, SystemTable);

    // 清屏
    systemtable->ConOut->ClearScreen(systemtable->ConOut);

    // 打印信息
    puts((unsigned short *)L"NullPotOS Bootloader\r\n");
    puts((unsigned short *)L"Copyright (C) 2024 LuoYuDian, All rights reserved.\r\n\n");

    EFI_STATUS status;
    EFI_PHYSICAL_ADDRESS entry_addr;
    struct EFI_FILE_PROTOCOL *root, *kernel_file;
    uint64 kernel_size = 4194304;
    VOID *kernel_buffer = malloc(kernel_size);

    status = SFSP->OpenVolume(SFSP, &root);
    if (EFI_ERROR(status))
    {
        puts((unsigned short *)L"[FAIL] Loading File System\r\n");
        while (1)
        {

        }
    }
    puts((unsigned short *)L"[PASS] Loading File System\r\n");

    status = root->Open(root, &kernel_file, (unsigned short *)L"\\NullPotOS\\kernel.elf", EFI_FILE_MODE_READ, 0);
    if (EFI_ERROR(status))
    {
        puts((unsigned short *)L"[FAIL] Loading Kernel Files\r\n");
        while (1)
        {

        }
    }
    puts((unsigned short *)L"[PASS] Loading Kernel Files\r\n");

    status = kernel_file->Read(kernel_file, &kernel_size, kernel_buffer);
    if (EFI_ERROR(status))
    {
        puts((unsigned short *)L"[FAIL] Loading Kernel Files\r\n");
        while (1)
        {

        }
    }
    puts((unsigned short *)L"[PASS] Loading Kernel Files\r\n");

    elf::elf64_ehdr *ehdr = (elf::elf64_ehdr *)kernel_buffer;
    uint64 kernel_first_addr, kernel_last_addr;
    elf::calc_load_address_range(ehdr, &kernel_first_addr, &kernel_last_addr);

    elf::copy_load_segments(ehdr);
    entry_addr = ehdr->e_entry;

    struct  FrameBufferConfig config = 
    {
        (uint8 *)GOP->Mode->FrameBufferBase, GOP->Mode->Info->PixelsPerScanLine,
		GOP->Mode->Info->HorizontalResolution, GOP->Mode->Info->VerticalResolution
    };

    switch (GOP->Mode->Info->PixelFormat)
    {
        case PixelRedGreenBlueReserved8BitPerColor: 
            config.pixel_format = kRGBR; 
            break;
        case PixelBlueGreenRedReserved8BitPerColor: 
            config.pixel_format = kBGRR; 
            break;
        default:
            puts((unsigned short *)L"[FAIL] Loading Graphics\r\n");
            while (1)
            {

            }
    };
    puts((unsigned short *)L"[PASS] Loading Graphics\r\n");

    BOOT_CONFIG BootConfig;
    BootConfig.MemoryMap.MapSize = 4096;
    BootConfig.MemoryMap.Buffer = NULL;
    BootConfig.MemoryMap.MapKey = 0;
    BootConfig.MemoryMap.DescriptorSize = 0;
    BootConfig.MemoryMap.DescriptorVersion = 0;
    GetMMP(&BootConfig.MemoryMap);
    puts((unsigned short *)L"[PASS] Getting Memory Map\r\n\n");

    Kernel kernel = (Kernel)entry_addr;
    puts((unsigned short *)L"Operating System Boot Success.\r\n");
    kernel(&config, SystemTable, (BOOT_CONFIG *)&BootConfig);

    while (1)
    {

    }
}