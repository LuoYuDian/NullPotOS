#
#    Copyright(C) 2025 NullPotOS Project. All Rights Reserved.
#
#    Module name:
#        Bootloader.cpp
#
#    Description:
#        This file is Bootloader of the NullPotOS.
#
#    Author:
#        LuoYuDian
#        MaxSinoh
#
#    Date:
#        2025.1.20
#

OS_NAME 				:= NullPotOS
OS_VERSION 				:= Beta

BIOS_DIR 				:= BIOS
SECURE_DIR 				:= Secure
INCLUDES_DIR 			:= Includes
BOOTLOADER_DIR 			:= Bootloader
CORE_DIR 				:= Core

BUILD_DIR 				:= Build
OBJ_DIR 				:= $(BUILD_DIR)/Object
IMAGE_DIR 				:= $(BUILD_DIR)/Image
EFI_BOOT_DIR 			:= $(IMAGE_DIR)/EFI/Boot
OS_DIR 					:= $(IMAGE_DIR)/$(OS_NAME)

BOOTLOADER_ENTRY 		:= UefiMain

PRINT 					:= echo
CC 						:= gcc
CXX 					:= g++

CROSS_CC 				:= x86_64-w64-mingw32-gcc
CROSS_CXX 				:= x86_64-w64-mingw32-g++

LD 						:= ld
SBSIGN 					:= sbsign
QEMU 					:= qemu-system-x86_64

CFLAGS 					:= -W -Wall -Wextra -g -O3 -std=c17 -I $(INCLUDES_DIR) -nostdinc -nostdlib -fno-builtin
CXXFLAGS 				:= -W -Wall -Wextra -g -O3 -std=c++17 -I $(INCLUDES_DIR) -nostdinc -nostdlib -fno-builtin

CROSS_CFLAGS 			:= -I $(INCLUDES_DIR) -std=c17 -g -O3 -Wall -Wextra -e $(BOOTLOADER_ENTRY) -nostdinc -nostdlib -fno-builtin -Wl,--subsystem,10
CROSS_CXXFLAGS 			:= -I $(INCLUDES_DIR) -std=c++17 -g -O3 -Wall -Wextra -e $(BOOTLOADER_ENTRY) -nostdinc -nostdlib -fno-builtin -Wl,--subsystem,10

# Kernel Directory
KERNEL_DIRS 			:= $(CORE_DIR)/Init \
    $(CORE_DIR)/Hal/Io \
    $(CORE_DIR)/Libs/String \
    $(CORE_DIR)/Libs/Stdlib \
    $(CORE_DIR)/Libs/Math \
    $(CORE_DIR)/Kernel/Graphics/Bmp \
    $(CORE_DIR)/Kernel/Graphics/Font \
	$(CORE_DIR)/Drivers/Communicate/Serial \
    $(CORE_DIR)/Drivers/View/Gop \
	$(CORE_DIR)/Drivers/Sound/Beep \
    $(CORE_DIR)/Kernel/Debug/Print \
    $(CORE_DIR)/Kernel/Asm/A20 \
    $(CORE_DIR)/Kernel/Asm/Gdt

KERNEL_SRCS 			:= $(foreach dir,$(KERNEL_DIRS),$(wildcard $(dir)/*.cpp))

KERNEL_OBJS 			:= $(patsubst %.cpp,$(OBJ_DIR)/%.o,$(KERNEL_SRCS))

KERNEL_OBJ_DIRS 		:= $(sort $(dir $(KERNEL_OBJS)))

.PHONY: Info
Info:
	@$(PRINT) $(OS_NAME) Makefile
	@$(PRINT) Start Build $(OS_NAME)-$(OS_VERSION)
	@$(PRINT)
	@$(PRINT) Tool 			File:
	@$(PRINT) 

	@mkdir -p $(BUILD_DIR)
	@$(PRINT) "\033[32mmkdir\033[0m"				$(BUILD_DIR)

	

	@mkdir -p $(IMAGE_DIR)
	@$(PRINT) "\033[32mmkdir\033[0m"				$(IMAGE_DIR)

	@mkdir -p $(EFI_BOOT_DIR)
	@$(PRINT) "\033[32mmkdir\033[0m"				$(EFI_BOOT_DIR)

	@mkdir -p $(IMAGE_DIR)/Secure
	@$(PRINT) "\033[32mmkdir\033[0m"				$(IMAGE_DIR)/Secure


	@mkdir -p $(IMAGE_DIR)/Secure/Db
	@$(PRINT) "\033[32mmkdir\033[0m"				$(IMAGE_DIR)/Secure/Db

	@mkdir -p $(OS_DIR)
	@$(PRINT) "\033[32mmkdir\033[0m"				$(OS_DIR)

	@mkdir -p $(KERNEL_OBJ_DIRS)
	@$(foreach dir,$(KERNEL_OBJ_DIRS),$(PRINT) "\033[32mmkdir\033[0m"				$(dir);)

.PHONY: Bootloader
Bootloader:
	@$(CROSS_CXX) $(CROSS_CXXFLAGS) -o $(EFI_BOOT_DIR)/BootX64.efi $(BOOTLOADER_DIR)/Bootloader.cpp

.PHONY: Secure
Secure:
	-@$(SBSIGN) --key $(SECURE_DIR)/Db/Db.key --cert $(SECURE_DIR)/Db/Db.crt --output $(EFI_BOOT_DIR)/BootX64.efi $(EFI_BOOT_DIR)/BootX64.efi
	-@$(SBSIGN) --key $(SECURE_DIR)/Db/Db.key --cert $(SECURE_DIR)/Db/Db.crt --output $(OS_DIR)/System/Kernel.elf $(OS_DIR)/System/Kernel.elf
	@cp -r $(SECURE_DIR)/Db/ $(IMAGE_DIR)/Secure/Db
	@cp -r $(SECURE_DIR)/Pk/ $(IMAGE_DIR)/Secure/
	@cp -r $(SECURE_DIR)/Kek/ $(IMAGE_DIR)/Secure/

.PHONY: Kernel
Kernel: $(OS_DIR)/System/Kernel.elf

.PHONY: all
all: Info Bootloader Kernel Secure

.PHONY: Run
Run: all
	@$(QEMU) -bios $(BIOS_DIR)/UEFI.fd -serial stdio -net none -drive file=fat:rw:$(IMAGE_DIR),index=0,format=vvfat

.PHONY: Clean
Clean:
	@rm -rf $(BUILD_DIR)
	@$(PRINT) "\033[31mrm\033[0m"				$(BUILD_DIR)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@$(PRINT) "\033[34mCXX\033[0m"					$<
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/$(CORE_DIR)/%.o: $(CORE_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@$(PRINT) "\033[34mCXX\033[0m"					$<
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(OS_DIR)/System/Kernel.elf: $(KERNEL_OBJS)
	@mkdir -p $(dir $@)
	@$(PRINT) "\033[35mLD\033[0m"					$@
	@$(LD) $(LDFLAGS) $(KERNEL_OBJS) -o $@