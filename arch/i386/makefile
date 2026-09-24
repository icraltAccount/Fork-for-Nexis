# Copyright (c) 2026 icarotelesdasilva colauzz-coder saintsHr
# Licensed under the MIT License

ifndef TOP
$(error Run make from the project root: make ARCH=i386)
endif

CC      := i686-elf-gcc
LD      := i686-elf-ld
OBJCOPY := i686-elf-objcopy
AS      := nasm
QEMU    := qemu-system-i386

INCLUDES := -I$(TOP)/kernel/include -I$(TOP)/drivers/include -Iinclude

CFLAGS := -m32 -ffreestanding -fno-pie -fno-stack-protector \
          -fno-builtin -fno-asynchronous-unwind-tables \
          -fno-unwind-tables -Wall -Wextra -O2 -g $(INCLUDES)

LDFLAGS := -m elf_i386 -T linker.ld

KERNEL_SRC := $(shell find $(TOP)/kernel/src $(TOP)/drivers/src -name '*.c')
ARCH_SRC   := $(shell find src -name '*.c')
ASM_SRC    := boot/entry.asm $(shell find src -name '*.asm')

OBJECTS := \
	$(patsubst $(TOP)/%.c,$(BUILD)/%.o,$(KERNEL_SRC)) \
	$(patsubst %.c,$(BUILD)/%.o,$(ARCH_SRC)) \
	$(patsubst %.asm,$(BUILD)/%.o,$(ASM_SRC))

STAGE1     := $(BUILD)/stage1.bin
STAGE2     := $(BUILD)/stage2.bin
KERNEL_ELF := $(BUILD)/kernel.elf
KERNEL_BIN := $(BUILD)/kernel.bin
IMAGE      := $(BUILD)/kernel.img

.PHONY: all run info
.DELETE_ON_ERROR:

all: $(IMAGE)

$(BUILD)/kernel/%.o: $(TOP)/kernel/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/drivers/%.o: $(TOP)/drivers/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/%.o: %.asm
	@mkdir -p $(dir $@)
	$(AS) -f elf32 $< -o $@

$(KERNEL_ELF): $(OBJECTS) linker.ld
	$(LD) $(LDFLAGS) -o $@ $(OBJECTS)

$(KERNEL_BIN): $(KERNEL_ELF)
	$(OBJCOPY) -O binary $< $@

$(STAGE2): boot/stage2.asm
	@mkdir -p $(dir $@)
	$(AS) -f bin $< -o $@

$(STAGE1): boot/stage1.asm $(STAGE2) $(KERNEL_BIN)
	@mkdir -p $(dir $@)
	$(AS) -f bin \
		-dKERNEL_SECTORS=$$(( ($$(stat -c%s $(KERNEL_BIN)) + 511) / 512 )) \
		$< -o $@
	@[ $$(stat -c%s $@) -eq 512 ] || { echo "stage 1 must be exactly 512 bytes"; exit 1; }

$(IMAGE): $(STAGE1) $(STAGE2) $(KERNEL_BIN)
	cat $^ > $@
	truncate -s %512 $@

info: $(IMAGE)
	@stat -c '%n : %s bytes' $(STAGE1) $(STAGE2) $(KERNEL_BIN) $(IMAGE)

run: $(IMAGE)
	$(QEMU) -drive format=raw,file=$(IMAGE)
