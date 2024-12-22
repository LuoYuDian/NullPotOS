# 创建于20224.12.22
# NullPotOS makefile

KERNEL_CPP		= ./kernel/k_main.cpp
KERNEL_O		= ./kernel/k_main.o
KERNEL_ELF		= ./build/NullPotOS/kernel.elf

MINGW_GCC		= x86_64-w64-mingw32-gcc
GPP				= g++
LD				= ld
ASM				= gcc

GCC_FLAGS		= -W -Wno-missing-field-initializers -Wextra -e _bootloadermain -nostdinc -nostdlib -fno-builtin -Wl,--subsystem,10 -I includes -o
GPP_FLAGS		= -O2 -W -m64 -Wimplicit-fallthrough=0 -g -ffreestanding -fno-exceptions -fno-rtti -std=c++17 -I includes -fshort-wchar -c -o
ASM_FLAGS		= -f elf64 -g -F stabs
LD_FLAGS		= -e _kernelmain -z norelro --static -m elf_x86_64 -nostdlib -o

QEMU			= qemu-system-x86_64

BOOTX64_C		= ./boot/boot.cpp
BOOTX64_EFI		= ./build/EFI/boot/bootx64.efi
CPP_SOURCES		= $(shell find . -name "*.cpp" -type f -not -path "./kernel/*")
CPP_OBJECTS		= $(patsubst %.cpp, %.o, $(CPP_SOURCES))
S_SOURCES		= $(shell find . -name "*.s")
S_OBJECTS		= $(patsubst %.s, %.o, $(S_SOURCES))

all: clean info .c.o kernel link done

info:
	@mkdir -p build/EFI/boot
	@mkdir -p build/NullPotOS

.s.o:
	@echo "\033[32m[Build]\033[0m" $< ...
	@$(ASM) $(ASM_FLAGS) $<

.c.o:
	@echo "\033[32m[Build]\033[0m" $(BOOTX64_C) ...
	@$(MINGW_GCC) $(GCC_FLAGS) $(BOOTX64_EFI) $(BOOTX64_C)

kernel:
	@echo "\033[32m[Build]\033[0m" $(KERNEL_CPP) ...
	@$(GPP) $(KERNEL_CPP) $(GPP_FLAGS) $(KERNEL_O)

%.o: %.cpp
	@echo "\033[32m[Build]\033[0m" $< ...
	@$(GPP) ./$< $(GPP_FLAGS) $@

link:$(KERNEL_O) $(CPP_OBJECTS) $(S_OBJECTS)
	@echo
	@echo "\033[32m[Link]\033[0m" 链接中 $(KERNEL_O) ...
	@$(LD) $(LD_FLAGS) $(KERNEL_ELF) $(KERNEL_O) $(CPP_OBJECTS) $(S_OBJECTS) ./libs/klogo.obj

done:
	@echo "\033[32m[Done]\033[0m" 编译完成!
	@echo

.PHONY: clean
clean:
	@rm -rf $(BOOTX64_EFI) $(KERNEL_O) $(KERNEL_ELF) $(CPP_OBJECTS) $(S_OBJECTS) *.o build

.PHONY: qemu_uefi_debug
run: all
	$(QEMU) -bios ./bios/OVMF.fd -serial stdio -net none -drive file=fat:rw:build,index=0,format=vvfat -d in_asm
