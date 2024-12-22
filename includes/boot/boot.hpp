// 创建于2024.12.22
// NullPotOS bootloader头文件

#ifndef INCLUDES_BOOT_BOOT_HPP_
#define INCLUDES_BOOT_BOOT_HPP_

#include <firmware/UEFI.hpp>

#ifdef __cplusplus
    #define NULL 0
#else
    #define NULL ((void *)0)
#endif

struct EFI_SYSTEM_TABLE                *systemtable;
struct EFI_BOOT_SERVICES               *bootservices;
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

void puts(unsigned short *s) 
{
    systemtable->ConOut->OutputString(systemtable->ConOut, s);
}

void *malloc(int buf_size) 
{
    void              *res;
    unsigned long long status;

    status = bootservices->AllocatePool(LIP ? LIP->ImageDataType : EfiLoaderData, buf_size,&res);
    if (status!=EFI_SUCCESS)
    {
        return NULL;
    }

    return res;
}

void free(void *buf) 
{
    bootservices->FreePool(buf);
}

EFI_STATUS malloc_at(EFI_PHYSICAL_ADDRESS addr, uintn size) 
{
    EFI_STATUS           status;
    EFI_PHYSICAL_ADDRESS allocated_addr=addr;
    status = bootservices->AllocatePages(AllocateAnyPages, LIP ? LIP->ImageDataType : EfiLoaderData,(size + 0xfff) / 0x1000, &allocated_addr);
    return status;
}

void efi_init(EFI_HANDLE ImageHandle, struct EFI_SYSTEM_TABLE *SystemTable) 
{
    systemtable = SystemTable;
    bootservices = SystemTable->BootServices;
    IM = ImageHandle;

    // init
    bootservices->SetWatchdogTimer(0, 0, 0, NULL);
    bootservices->LocateProtocol(&gop_guid, NULL, (void **)&GOP);

    bootservices->OpenProtocol(ImageHandle, &lip_guid, (void **)&LIP, ImageHandle, NULL,EFI_OPEN_PROTOCOL_GET_PROTOCOL);
    bootservices->OpenProtocol(LIP->DeviceHandle, &sfsp_guid, (void **)&SFSP, ImageHandle, NULL,EFI_OPEN_PROTOCOL_BY_HANDLE_PROTOCOL);
}

EFI_STATUS GetMMP(MEMORY_MAP *MemoryMap) 
{
    EFI_STATUS GetMemoryMapStatus = EFI_SUCCESS;

    MemoryMap->Buffer = malloc(MemoryMap->MapSize);

    while(bootservices->GetMemoryMap(&MemoryMap->MapSize,(EFI_MEMORY_DESCRIPTOR*)MemoryMap->Buffer,&MemoryMap->MapKey,&MemoryMap->DescriptorSize,(uint32 *)&MemoryMap->DescriptorVersion) == EFI_BUFFER_TOO_SMALL) 
    {
        if (MemoryMap->Buffer) 
        {
        free(MemoryMap->Buffer);
        MemoryMap->Buffer = NULL;
        }

        MemoryMap->Buffer = malloc(MemoryMap->MapSize);
    }

    if (!MemoryMap->Buffer) 
    {
        GetMemoryMapStatus = EFI_OUT_OF_RESOURCES;
    }

    return GetMemoryMapStatus;
}

void switch_to_resolution(unsigned int x, unsigned int y)
{
    unsigned long long sizeofInfo = 0;
    EFI_GRAPHICS_OUTPUT_MODE_INFORMATION *info;
    for (unsigned int i = 0; i < GOP->Mode->MaxMode; i++) 
    {
        GOP->QueryMode(GOP, i, &sizeofInfo, &info);

        if (info->HorizontalResolution == x && info->VerticalResolution == y) 
        {
            GOP->SetMode(GOP, i);
        }
    }
}

typedef void (*__attribute__((sysv_abi)) Kernel)(const struct FrameBufferConfig *,struct EFI_SYSTEM_TABLE *, BOOT_CONFIG *);
#endif