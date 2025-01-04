/*
创建于2024.12.8
NullPotOS x86 链接脚本 
*/

ENTRY(start_)

SECTIONS 
{
    . = 0x100000;
    
    .hhk_init_text BLOCK(4K) : 
    {
        * (.header)
        build/obj/arch/x86/*.o (.hhkinit)
        build/obj/arch/x86/*.o (.text)
    }

    .hhk_init_bss BLOCK(4K) : 
    {
        build/obj/arch/x86/*.o (.bss)
    }

    .hhk_init_data BLOCK(4K) : 
    {
        build/obj/arch/x86/*.o (.data)
    }

    .hhk_init_rodata BLOCK(4K) : 
    {
        build/obj/arch/x86/*.o (.rodata)
    }
    __init_hhk_end = ALIGN(4K);

    . += 0xC0000000;

    .text BLOCK(4K) : AT ( ADDR(.text) - 0xC0000000 ) 
    {
        __kernel_start = .;
        build/obj/kernel/*.o (.text)
        build/obj/hal/*.o (.text)
    }

    .bss BLOCK(4K) : AT ( ADDR(.bss) - 0xC0000000 ) 
    {
        build/obj/kernel/*.o (.bss)
        build/obj/hal/*.o (.bss)
    }

    .data BLOCK(4k) : AT ( ADDR(.data) - 0xC0000000 ) 
    {
        build/obj/kernel/*.o (.data)
        build/obj/hal/*.o (.data)
    }

    .rodata BLOCK(4K) : AT ( ADDR(.rodata) - 0xC0000000 ) 
    {
        build/obj/kernel/*.o (.rodata)
        build/obj/hal/*.o (.rodata)
    }

    .kpg BLOCK(4K) : AT ( ADDR(.kpg) - 0xC0000000 ) 
    {
        build/obj/arch/x86/*.o (.kpg)
    }

    __kernel_end = ALIGN(4K);
    __heap_start = ALIGN(4K);
}