# NullPotOS 项目

# 目录

``` Bash
GRUB_TEMPLATE  README.md  config-grub.sh  drivers  includes  libs
LICENSE        arch       docs            hal      kernel    makefile
```

# 文件

``` Bash
.
├── GRUB_TEMPLATE
├── LICENSE      
├── README.md    
├── arch
│   └── x86
│       ├── asm
│       │   ├── gdt
│       │   │   └── gdt.c
│       │   ├── idt
│       │   │   └── idt.c
│       │   └── interrupts
│       │       ├── interrupts.S
│       │       └── interrupts.c
│       ├── boot
│       │   └── boot.S
│       ├── hhk
│       │   ├── hhk.S
│       │   └── hhk.c
│       └── linker.lds
├── config-grub.sh
├── docs
│   ├── NullPotos.md
│   └── img
│       └── logo
│           └── logo.bmp
├── drivers
│   └── view
│       └── vga
│           └── vga.c
├── hal
│   └── cpu
│       └── cpu.c
├── includes
│   ├── arch
│   │   └── x86
│   │       ├── asm
│   │       │   ├── gdt
│   │       │   │   └── gdt.h
│   │       │   ├── idt
│   │       │   │   ├── idt.h
│   │       │   │   └── types.h
│   │       │   └── interrupts
│   │       │       └── interrupts.h
│   │       └── boot
│   │           └── multiboot.h
│   ├── drivers
│   │   └── view
│   │       └── vga
│   │           └── vga.h
│   ├── hal
│   │   ├── cpu
│   │   │   └── cpu.h
│   │   ├── hal.h
│   │   └── io
│   │       └── io.h
│   ├── kernel
│   │   ├── constants.h
│   │   ├── error
│   │   │   └── error.h
│   │   └── mm
│   │       ├── page.h
│   │       ├── pmm.h
│   │       └── vmm.h
│   └── libs
│       └── libc
│           ├── stdio.h
│           ├── stdlib.h
│           └── string.h
├── kernel
│   ├── error
│   │   └── error.c
│   ├── kernel.c
│   └── mm
│       ├── pmm.c
│       └── vmm.c
├── libs
│   └── libc
│       ├── stdio
│       │   ├── printf.c
│       │   └── sprintf.c
│       ├── stdlib
│       │   └── itoa.c
│       └── string
│           ├── mem.c
│           ├── strcpy.c
│           └── strlen.c
└── makefile

43 directories, 44 files
```