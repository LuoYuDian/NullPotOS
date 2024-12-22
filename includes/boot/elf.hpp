// 创建于2024.12.22
// NullPotOS elf头文件

#ifndef ELF_HPP
#define ELF_HPP
#pragma once
namespace elf
{

    typedef struct
    {
        uint32 p_type;        // Segment type
        uint32 p_flags;       // Segment flags
        uint64 p_offset;      // Segment file offset
        uint64 p_vaddr;       // Segment virtual address
        uint64 p_paddr;       // Segment physical address
        uint64 p_filesz;      // Segment size in file
        uint64 p_memsz;       // Segment size in memory
        uint64 p_align;       // Segment alignment
    } elf64_phdr;

    typedef struct
    {
        uint8  e_ident[16];   // Magic number and other info
        uint16 e_type;        // Object file type
        uint16 e_machine;     // Architecture
        uint32 e_version;     // Object file version
        uint64 e_entry;       // Entry point virtual address
        uint64 e_phoff;       // Program header table file offset
        uint64 e_shoff;       // Section header table file offset
        uint32 e_flags;       // Processor-specific flags
        uint16 e_ehsize;      // ELF header size in bytes
        uint16 e_phentsize;   // Program header table entry size
        uint16 e_phnum;       // Program header table entry count
        uint16 e_shentsize;   // Section header table entry size
        uint16 e_shnum;       // Section header table entry count
        uint16 e_shstrndx;    // Section header string table index 
    } elf64_ehdr;
}
#endif