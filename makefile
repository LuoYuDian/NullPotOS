# 创建于2024.12.8
# NullPotOS makefile

OS_ARCH := x86
ARCH_DIR := arch
DRIVERS_DIR := drivers
BUILD_DIR := build
KERNEL_DIR := kernel
OBJECT_DIR := $(BUILD_DIR)/obj
BIN_DIR := $(BUILD_DIR)/bin
ISO_DIR := $(BUILD_DIR)/iso
ISO_BOOT_DIR := $(ISO_DIR)/boot
ISO_GRUB_DIR := $(ISO_BOOT_DIR)/grub
INCLUDES_DIR := includes
DEBUG_DIR := $(BUILD_DIR)/debug

INCLUDES := $(patsubst %, -I %, $(INCLUDES_DIR))

OS_NAME = NullPotOS
OS_BIN = $(OS_NAME).bin
OS_ISO = $(OS_NAME).iso

CC := gcc
AS := as

O := -O3
W := -Wall -Wextra

CFLAGS := -std=gnu99 -ffreestanding $(O) $(W)
LDFLAGS := -ffreestanding $(O) -nostdlib -m32

SOURCE_FILES := $(shell find -name "*.[cS]")
SRC := $(patsubst ./%, $(OBJECT_DIR)/%.o, $(SOURCE_FILES))

$(OBJECT_DIR):
	@mkdir -p $(OBJECT_DIR)

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

$(ISO_DIR):
	@mkdir -p $(ISO_DIR)
	@mkdir -p $(DEBUG_DIR)
	@mkdir -p $(ISO_BOOT_DIR)
	@mkdir -p $(ISO_GRUB_DIR)

$(OBJECT_DIR)/%.S.o: %.S
	@mkdir -p $(@D)
	@$(CC) $(INCLUDES) -c $< -o $@ -m32

$(OBJECT_DIR)/%.c.o: %.c 
	@mkdir -p $(@D)
	@$(CC) $(INCLUDES) -c $< -o $@ $(CFLAGS) -m32

$(BIN_DIR)/$(OS_BIN): $(OBJECT_DIR) $(BIN_DIR) $(SRC)
	$(CC) -T $(ARCH_DIR)/$(OS_ARCH)/linker.lds -o $(BIN_DIR)/$(OS_BIN) $(SRC) $(LDFLAGS) -m32

$(BUILD_DIR)/$(OS_ISO): $(ISO_DIR) $(BIN_DIR)/$(OS_BIN) GRUB_TEMPLATE
	@chmod u+x config-grub.sh
	@./config-grub.sh ${OS_NAME} > $(ISO_GRUB_DIR)/grub.cfg
	@cp $(BIN_DIR)/$(OS_BIN) $(ISO_BOOT_DIR)
	@grub-mkrescue -o $(BUILD_DIR)/$(OS_ISO) $(ISO_DIR)

all: clean $(BUILD_DIR)/$(OS_ISO)

all-debug: O := -O0
all-debug: CFLAGS := -g -std=gnu99 -ffreestanding $(O) $(W) -fomit-frame-pointer
all-debug: LDFLAGS := -ffreestanding $(O) -nostdlib -m32
all-debug: clean $(BUILD_DIR)/$(OS_ISO)
	@objdump -D $(BIN_DIR)/$(OS_BIN) > $(DEBUG_DIR)/dump

clean:
	@rm -rf $(BUILD_DIR)

run: all-debug
	@objcopy --only-keep-debug $(BIN_DIR)/$(OS_BIN) $(DEBUG_DIR)/kernel.dbg
	@qemu-system-i386 -s -S -cdrom $(BUILD_DIR)/$(OS_ISO) &
	@gdb -s $(BUILD_DIR)/kernel.dbg -ex "target remote localhost:1234"