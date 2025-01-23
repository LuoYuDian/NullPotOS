/*
    Copyright(C) 2025 NullPotOS Project. All Rights Reserved.
        
    Module name:
        Elf.hpp

    Description:
        This header file is used to define the Elf of the NullPotOS.

    Author:
        LuoYuDian
        MaxSinoh

    Date:
        2025.1.20
*/

#ifndef ELF_HPP
#define ELF_HPP

#include <Firmware/Uefi/Uefi.hpp>

namespace Elf
{

    typedef struct
    {
        UINT32 PType;        // Segment type
        UINT32 PFlags;       // Segment flags
        UINT64 POffset;      // Segment file offset
        UINT64 PVaddr;       // Segment virtual address
        UINT64 PPaddr;       // Segment physical address
        UINT64 PFilesz;      // Segment size in file
        UINT64 PMemsz;       // Segment size in memory
        UINT64 PAlign;       // Segment alignment
    } Elf64Phdr;

    typedef struct
    {
        UINT8  EIdent[16];   // Magic number and other info
        UINT16 EType;        // Object file type
        UINT16 EMachine;     // Architecture
        UINT32 EVersion;     // Object file version
        UINT64 EEntry;       // Entry point virtual address
        UINT64 EPhoff;       // Program header table file offset
        UINT64 EShoff;       // Section header table file offset
        UINT32 EFlags;       // Processor-specific flags
        UINT16 Eehsize;      // ELF header size in bytes
        UINT16 EPhentsize;   // Program header table entry size
        UINT16 EPhnum;       // Program header table entry count
        UINT16 Eshentsize;   // Section header table entry size
        UINT16 Eshnum;       // Section header table entry count
        UINT16 Eshstrndx;    // Section header string table index 
    } Elf64Ehdr;
}
#endif // ELF_HPP