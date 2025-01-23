/*
    Copyright(C) 2025 NullPotOS Project. All Rights Reserved.

    Module name:
        Bootloader.hpp

    Description:
        This header file is used Bootloader of the NullPotOS.

    Author:
        LuoYuDian
        MaxSinoh

    Date:
        2025.1.20
*/

#ifndef BOOTLOADER_HPP
#define BOOTLOADER_HPP

#include <Types.hpp>
#include <Firmware/Uefi/Uefi.hpp>

struct EFI_SYSTEM_TABLE                *ST;
struct EFI_BOOT_SERVICES               *BS;
struct EFI_GRAPHICS_OUTPUT_PROTOCOL    *GOP;
struct EFI_SIMPLE_FILE_SYSTEM_PROTOCOL *SFSP;
struct EFI_LOADED_IMAGE_PROTOCOL       *LIP;
EFI_HANDLE                              IM;

struct EFI_GUID gop_guid = 
{
    0x9042a9de, 0x23dc, 0x4a38, {0x96, 0xfb, 0x7a, 0xde, 0xd0, 0x80, 0x51, 0x6a}
};

struct EFI_GUID lip_guid = 
{
    0x5b1b31a1, 0x9562, 0x11d2, {0x8e, 0x3f, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}
};

struct EFI_GUID sfsp_guid = 
{
    0x964e5b22, 0x6459, 0x11d2, {0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b}
};

struct EFI_GUID spp_guid = 
{
    0x31878c87, 0xb75, 0x11d5, {0x9a, 0x4f, 0x0, 0x90, 0x27, 0x3f, 0xc1, 0x4d}
};

void Print(unsigned short *s) 
{
    ST->ConOut->OutputString(ST->ConOut, s);
}

void *Malloc(UINTN BufSize) 
{
    void              *Res;
    unsigned long long Status;

    Status = BS->AllocatePool(LIP ? LIP->ImageDataType : EfiLoaderData, BufSize,&Res);
    if (Status!=EFI_SUCCESS)
    {
        return NULL;
    }

    return Res;
}

void Free(void *Buf) 
{
    BS->FreePool(Buf);
}

EFI_STATUS MallocAt(EFI_PHYSICAL_ADDRESS Addr, UINTN Size) 
{
    EFI_STATUS           Status;
    EFI_PHYSICAL_ADDRESS Allocated_Addr = Addr;
    Status = BS->AllocatePages(AllocateAnyPages, LIP ? LIP->ImageDataType : EfiLoaderData,(Size + 0xfff) / 0x1000, &Allocated_Addr);
    return Status;
}

void UefiInit(EFI_HANDLE ImageHandle, struct EFI_SYSTEM_TABLE *SystemTable) 
{
    ST = SystemTable;
    BS = ST->BootServices;
    IM = ImageHandle;

    // Init
    
    BS->SetWatchdogTimer(0, 0, 0, NULL);
    BS->LocateProtocol(&gop_guid, NULL, (void **)&GOP);

    BS->OpenProtocol(ImageHandle, &lip_guid, (void **)&LIP, ImageHandle, NULL,EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    BS->OpenProtocol(LIP->DeviceHandle, &sfsp_guid, (void **)&SFSP, ImageHandle, NULL,EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
}

EFI_STATUS GetMMP(MEMORY_MAP *MemoryMap) 
{
    EFI_STATUS GetMemoryMapStatus = EFI_SUCCESS;

    MemoryMap->Buffer = Malloc(MemoryMap->MapSize);

    while(BS->GetMemoryMap(&MemoryMap->MapSize,(EFI_MEMORY_DESCRIPTOR*)MemoryMap->Buffer,&MemoryMap->MapKey,&MemoryMap->DescriptorSize,(UINT32 *)&MemoryMap->DescriptorVersion) == EFI_BUFFER_TOO_SMALL) 
    {
        if (MemoryMap->Buffer) 
        {
            Free(MemoryMap->Buffer);
            MemoryMap->Buffer = NULL;
        }

        MemoryMap->Buffer = Malloc(MemoryMap->MapSize);
    }

    if (!MemoryMap->Buffer) 
    {
        GetMemoryMapStatus = EFI_OUT_OF_RESOURCES;
    }

    return GetMemoryMapStatus;
}

void SwitchToResolution(unsigned int X, unsigned int Y)
{
    unsigned long long sizeofInfo = 0;
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *Info;
    for (unsigned int i = 0; i < GOP->Mode->MaxMode; i++) 
    {
        GOP->QueryMode(GOP, i, &sizeofInfo, &Info);

        if (Info->HorizontalResolution == X && Info->VerticalResolution == Y) 
        {
            GOP->SetMode(GOP, i);
        }
    }
}

typedef void (*__attribute__((sysv_abi)) Kernel)(const struct FrameBufferConfig *,struct EFI_SYSTEM_TABLE *, BOOT_CONFIG *);

#endif // BOOTLOADER_HPP