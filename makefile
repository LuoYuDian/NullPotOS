# 创建于2024.12.8
# NullPotOS makefile

OS_NAME = NullPotOS
OS_ARCH := x86
OS_VERSION := Beta-V0.0.1
OS_BIN = kernel.bin
OS_ISO = $(OS_NAME)-$(OS_VERSION).iso

ARCH_DIR := arch
DRIVERS_DIR := drivers
BUILD_DIR := build
KERNEL_DIR := kernel
OBJECT_DIR := $(BUILD_DIR)/obj
BIN_DIR := $(BUILD_DIR)/bin
ISO_DIR := $(BUILD_DIR)/iso
OS_DIR 	:= $(ISO_DIR)/$(OS_NAME)
ISO_BOOT_DIR := $(ISO_DIR)/boot
ISO_GRUB_DIR := $(ISO_BOOT_DIR)/grub
INCLUDES_DIR := includes
DEBUG_DIR := $(BUILD_DIR)/debug

INCLUDES := $(patsubst %, -I %, $(INCLUDES_DIR))

TIME := 0.125

CC := gcc
PP := g++
AS := $(CC)

O := -O3
W := -Wall -Wextra

CFLAGS := -std=c17 -ffreestanding $(O) $(W) -fno-pie -g
PPFLAGS := -std=c++17 -ffreestanding $(O) $(W) -fno-pie -g
LDFLAGS := -ffreestanding $(O) -nostdlib -m32 -fno-pie -g

SOURCE_FILES := $(shell find . -name "*.[cS]" -o -name "*.cpp")
SRC := $(patsubst ./%, $(OBJECT_DIR)/%.o, $(SOURCE_FILES))

$(OBJECT_DIR):
	@echo "\033[32m[Create]\033[0m" ...
	@mkdir -p $(OBJECT_DIR)
	@sleep $(TIME)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

$(ISO_DIR):
	@mkdir -p $(ISO_DIR)
	@mkdir -p $(DEBUG_DIR)
	@mkdir -p $(OS_DIR)/sys
	@mkdir -p $(ISO_BOOT_DIR)
	@mkdir -p $(ISO_GRUB_DIR)

$(OBJECT_DIR)/%.S.o: %.S
	@mkdir -p $(@D)
	@echo "\033[32m[Compiler]\033[0m" $< ...
	@$(CC) $(INCLUDES) -c $< -o $@ -m32
	@sleep $(TIME)

$(OBJECT_DIR)/%.c.o: %.c
	@mkdir -p $(@D)
	@echo "\033[32m[Compiler]\033[0m" $< ...
	@$(CC) $(INCLUDES) -c $< -o $@ $(CFLAGS) -m32
	@sleep $(TIME)

$(OBJECT_DIR)/%.cpp.o: %.cpp
	@mkdir -p $(@D)
	@echo "\033[32m[Compiler]\033[0m" $<...
	@$(PP) $(INCLUDES) -c $< -o $@ $(PPFLAGS) -m32
	@sleep $(TIME)

$(BIN_DIR)/$(OS_BIN): $(OBJECT_DIR) $(BIN_DIR) $(SRC)
	@echo "\033[32m[Link]\033[0m" $(BIN_DIR)/$(OS_BIN) ...
	@$(CC) -T $(ARCH_DIR)/$(OS_ARCH)/linker.lds -o $(BIN_DIR)/$(OS_BIN) $(SRC) $(LDFLAGS) -m32

$(BUILD_DIR)/$(OS_ISO): $(ISO_DIR) $(BIN_DIR)/$(OS_BIN) GRUB_TEMPLATE
	@echo "\033[32m[Image]\033[0m" $(ISO_DIR)/$(OS_ISO) ...
	@chmod u+x config-grub.sh
	@./config-grub.sh ${OS_NAME} > $(ISO_GRUB_DIR)/grub.cfg
	@cp $(BIN_DIR)/$(OS_BIN) $(OS_DIR)/sys/$(OS_BIN)
	@grub-mkrescue -o $(BUILD_DIR)/$(OS_ISO) $(ISO_DIR)

all: clean $(BUILD_DIR)/$(OS_ISO)

debug: all
	@echo "\033[32m[Run]\033[0m"
	@qemu-system-x86_64 -S -s -cdrom $(BUILD_DIR)/$(OS_ISO) &
	@gdb -ex "target remote 127.0.0.1:1234" -ex "symbol-file $(OS_DIR)/sys/$(OS_BIN)"
	@echo "\033[32m[End]\033[0m"
	@${MAKE} clean
	@clear

.PHONY: clean help
clean:
	@echo "\033[32m[Clean]\033[0m" ...
	@rm -rf $(BUILD_DIR)

help:
	@echo $(OS_NAME) makefile
	@echo "\033[32mall\033[0m" "--> 编译 $(OS_NAME)"
	@sleep $(TIME)
	@echo "\033[32mclean\033[0m" "--> 清理 $(OS_NAME)"
	@sleep $(TIME)
	@echo "\033[32mdebug\033[0m" "--> 调试 $(OS_NAME)"