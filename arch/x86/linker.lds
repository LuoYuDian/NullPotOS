/*
创建于2024.12.8
NullPotOS x86 链接脚本 
*/

ENTRY(start_)

SECTIONS 
{
    . = 0x100000;
    
    .text BLOCK(4K) : 
    {
        * (.header)
        * (.text)
    }
    
    .bss BLOCK(4K) : 
    {
        * (COMMON)
        * (.bss)
    }
    
    .data BLOCK(4k) : 
    {
        * (.data)
    }

    .rodata BLOCK(4K) : 
    {
        * (.rodata)
    }
}