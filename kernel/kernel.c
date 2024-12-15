// 创建于2024.12.8
// NullPotOS 内核

#include <arch/x86/boot/multiboot.h>
#include <drivers/view/vga/vga.h>
#include <libs/libc/stdio.h>
#include <kernel/error/error.h>
#include <hal/cpu/cpu.h>
#include <kernel/constants.h>
#include <kernel/mm/page.h>
#include <kernel/mm/vmm.h>

extern void __kernel_start;
extern void __kernel_end;
extern void __init_hhk_end;

void _kernelinit(multiboot_info_t* mb_info)
{
    
    _initidt();

    multiboot_memory_map_t* map = (multiboot_memory_map_t*)mb_info->mmap_addr;

#pragma region INIT_MM
    pmm_init(MEM_1MB + mb_info->mem_upper << 10);
    vmm_init();
#pragma endregion

    // 初始化VGA
    VGA_init(VGA_BUFFER_PADDR);
    VGA_set_theme(VGA_COLOR_CYAN, VGA_COLOR_BLACK);

    printf("[KERNEL] === Initialization === \n");
    unsigned int map_size = mb_info->mmap_length / sizeof(multiboot_memory_map_t);
    printf("[MM] Mem: %d KiB, Extended Mem: %d KiB\n",mb_info->mem_lower,mb_info->mem_upper);

#pragma region MMAP_SCAN_RESERVING_KERNEL_PGS
    for (unsigned int i = 0; i < map_size; i++) 
    {
        multiboot_memory_map_t mmap = map[i];
        printf("[MM] Base: 0x%x, len: %u KiB, type: %u\n",map[i].addr_low,map[i].len_low >> 10,map[i].type);
        if (mmap.type == MULTIBOOT_MEMORY_AVAILABLE) 
        {
            uintptr_t pg = map[i].addr_low + 0x0fffU;
            pmm_mark_chunk_free(pg >> 12, map[i].len_low >> 12);
            printf("[MM] Freed %u pages start from 0x%x\n",
                   map[i].len_low >> 12,
                   pg & ~0x0fffU);
        }
    }

    size_t pg_count = (uintptr_t)(&__kernel_end - &__kernel_start) >> 12;
    pmm_mark_chunk_occupied(V2P(&__kernel_start) >> 12, pg_count);
    printf("[MM] Allocated %d pages for kernel.\n", pg_count);
#pragma endregion
    
    size_t vga_buf_pgs = VGA_BUFFER_SIZE >> 12;
    
    pmm_mark_chunk_occupied(VGA_BUFFER_PADDR >> 12, vga_buf_pgs);
    
    for (size_t i = 0; i < vga_buf_pgs; i++)
    {
        vmm_map_page(VGA_BUFFER_VADDR + (i << 12), VGA_BUFFER_PADDR + (i << 12), PG_PREM_RW, PG_PREM_RW);
    }
    
    VGA_set_buffer(VGA_BUFFER_VADDR);

    printf("[MM] Mapped VGA to %p.\n", VGA_BUFFER_VADDR);

    for (size_t i = 0; i < (K_STACK_SIZE >> 12); i++) 
    {
        vmm_alloc_page(K_STACK_START + (i << 12), PG_PREM_RW, PG_PREM_RW);
    }
    printf("[MM] Allocated %d pages for stack start at %p\n", K_STACK_SIZE>>12, K_STACK_START);

    printf("[KERNEL] === Initialization Done === \n\n");
}


void _kernel_post_init() {
    printf("[KERNEL] === Post Initialization === \n");
    size_t hhk_init_pg_count = ((uintptr_t)(&__init_hhk_end)) >> 12;
    printf("[MM] Releaseing %d pages from 0x0.\n", hhk_init_pg_count);

    for (size_t i = 0; i < hhk_init_pg_count; i++) 
    {
        vmm_unmap_page((i << 12));
    }
    printf("[KERNEL] === Post Initialization Done === \n\n");
}

void _kernelmain()
{
    char buf[60];

    cpu_get_brand(buf);
    printf("CPU: %s\n",buf);

    /*
    printf("NullPotOS V0.05\n@Copyright LuoYuDian 2024\n");
    printf("You see source code at https://github.com/LuoYuDian/NUllPotOS \n");
    printf("Welcome to use NullPotOS!\n");
    */
    
    uintptr_t k_start = vmm_v2p(&__kernel_start);
}