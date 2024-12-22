// 创建于、2024.12.22
// NullPotOS 内核
extern "C" 
{
    #include <firmware/UEFI.hpp>
}
#pragma once
#include <boot/elf.hpp>
#include <libs/printf.hpp>
#include <libs/string.hpp>
#include <modules/asm/gdt/gdt.hpp>
#include <drivers/beep/beep.hpp>
#include <drivers/cmos/cmos.hpp>
#include <drivers/common/common.hpp>
#include <drivers/vga/vga.hpp>
#include <drivers/serial/serial.hpp>
#include <modules/bmp/bmp.hpp>
#include <version.hpp>

extern uint8_t klogo[]; // 声明内核Logo数据

extern "C" void _kernelmain(FrameBufferConfig &fbc,EFI_SYSTEM_TABLE &SystemTable,BOOT_CONFIG *BootConfig)
{
	disable_interrupts();
	GetVInfo(fbc);
	VGA_clear();

	VGA_to_serial(1);
	bmp((Bmp *)klogo, fbc.horizontal_resolution - 184 - 20, 20, 1);
	printf("NullPotOS " KERNL_VERS "(build-%d)\n", KERNL_BUID);			// 打印内核信息
	printf(PROJK_COPY "\n");												// 打印版权信息
	printf("This version compiles at " BUILD_DATE " " BUILD_TIME "\n\n");	// 打印编译日期时间

	printf("Initializing operating system kernel components.\n");			// 提示用户正在初始化内核
	_initgdt(); // 初始化GDT

	VGA_to_serial(0);
	while (1);
}
