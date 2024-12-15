// 创建于2024.12.15
// NullPotOS hhk

#include <arch/x86/boot/multiboot.h>
#include <arch/x86/asm/gdt/gdt.h>
#include <arch/x86/asm/idt/idt.h>
#include <kernel/mm/page.h>
#include <kernel/constants.h>
#include <libs/libc/stdio.h>

#define PT_ADDR(ptd, pt_index)                       ((ptd_t*)ptd + (pt_index + 1) * 1024)
#define SET_PDE(ptd, pde_index, pde)                 *((ptd_t*)ptd + pde_index) = pde;
#define SET_PTE(ptd, pt_index, pte_index, pte)       *(PT_ADDR(ptd, pt_index) + pte_index) = pte;
#define sym_val(sym)                                 (uintptr_t)(&sym)

#define KERNEL_PAGE_COUNT           ((sym_val(__kernel_end) - sym_val(__kernel_start) + 0x1000 - 1) >> 12);
#define HHK_PAGE_COUNT              ((sym_val(__init_hhk_end) - 0x100000 + 0x1000 - 1) >> 12)

#define PG_TABLE_IDENTITY           0

#define PG_TABLE_KERNEL             1

#define PG_TABLE_STACK              4

extern uint8_t __kernel_start;
extern uint8_t __kernel_end;
extern uint8_t __init_hhk_end;
extern uint8_t _k_stack;

void _initpage(ptd_t* ptd)
{
    SET_PDE(ptd, 0, PDE(PG_PRESENT, ptd + PG_MAX_ENTRIES))
    
    for (uint32_t i = 0; i < 256; i++)
    {
        SET_PTE(ptd, PG_TABLE_IDENTITY, i, PTE(PG_PREM_RW, (i << 12)))
    }

    for (uint32_t i = 0; i < HHK_PAGE_COUNT; i++)
    {
        SET_PTE(ptd, PG_TABLE_IDENTITY, 256 + i, PTE(PG_PREM_RW, 0x100000 + (i << 12)))
    }
    
    uint32_t kernel_pde_index = PD_INDEX(sym_val(__kernel_start));
    uint32_t kernel_pte_index = PT_INDEX(sym_val(__kernel_start));
    uint32_t kernel_pg_counts = KERNEL_PAGE_COUNT;
    
    for (uint32_t i = 0; i < PG_TABLE_STACK - PG_TABLE_KERNEL; i++)
    {
        SET_PDE(ptd, kernel_pde_index + i, PDE(PG_PREM_RW, PT_ADDR(ptd, PG_TABLE_KERNEL + i))
        )
    }
    
    if (kernel_pg_counts > (PG_TABLE_STACK - PG_TABLE_KERNEL) * 1024) {
        printf("Not enable pages!");
        while (1)
        {

        }
    }
    
    uintptr_t kernel_pm = V2P(&__kernel_start);
    
    for (uint32_t i = 0; i < kernel_pg_counts; i++)
    {
        SET_PTE(ptd,PG_TABLE_KERNEL,kernel_pte_index + i, PTE(PG_PREM_RW, kernel_pm + (i << 12)))
    }

    SET_PDE(ptd,1023,PDE(T_SELF_REF_PERM, ptd));

}

uint32_t __save_subset(uint8_t* destination, uint8_t* base, unsigned int size) 
{
    unsigned int i = 0;
    for (; i < size; i++)
    {
        *(destination + i) = *(base + i);
    }
    return i;
}

void _save_multiboot_info(multiboot_info_t* info, uint8_t* destination)
{
    uint32_t current = 0;
    uint8_t* info_b = (uint8_t*) info;
    for (; current < sizeof(multiboot_info_t); current++)
    {
        *(destination + current) = *(info_b + current);
    }

    ((multiboot_info_t*) destination)->mmap_addr = (uintptr_t)destination + current;
    current += __save_subset(destination + current, (uint8_t*)info->mmap_addr, info->mmap_length);

    if (present(info->flags, MULTIBOOT_INFO_DRIVE_INFO)) 
    {
        ((multiboot_info_t*) destination)->drives_addr = (uintptr_t)destination + current;
        current += __save_subset(destination + current, (uint8_t*)info->drives_addr, info->drives_length);
    }
}

void _hhkinit(ptd_t* ptd, uint32_t kpg_size)
{
    // 清除GRUB留下的垃圾!!!
    uint8_t* kpg = (uint8_t *)ptd;

    for(uint32_t i = 0; i < kpg_size; i++)
    {
        *(kpg + i) = 0;
    }

    _initpage(ptd);
}