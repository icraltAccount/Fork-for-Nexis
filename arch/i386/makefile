# Copyright (c) 2026 icarotelesdasilva colauzz-coder saintsHr
# Licensed under the MIT License

ifndef TOP
$(error Run make from the project root: make ARCH=i386)
endif

CC      := gcc
LD      := ld
OBJCOPY := objcopy
AS      := nasm
QEMU    := qemu-system-i386

INCLUDES := \
	-I$(TOP)/kernel/include -I$(TOP)/drivers/include \
	-I$(TOP)/lib/include -Iinclude 
CFLAGS := \
	-m32 -ffreestanding -fno-pie -fno-stack-protector \
	-fno-builtin -fno-asynchronous-unwind-tables \
    -fno-unwind-tables -Wall -Wextra -O2 -g $(INCLUDES)

LDFLAGS := \
	-m elf_i386 -T linker.ld --no-warn-rwx-segments

KERNEL_SRC := \
	$(shell find $(TOP)/kernel -name '*.c') \
	$(shell find $(TOP)/drivers -name '*.c') \
	$(shell find $(TOP)/lib -name '*.c') \
	$(shell find $(TOP)/arch -name '*.c')
ASM_SRC := \
	$(shell find $(TOP)/kernel -name '*.asm') \
	$(shell find $(TOP)/drivers -name '*.asm') \
	$(shell find $(TOP)/lib -name '*.asm') \
	$(shell find $(TOP)/arch -name '*.asm' ! -path '*/boot/*')
OBJ_C := \
	$(patsubst $(TOP)/%.c,$(BUILD)/%.c.o,$(KERNEL_SRC))
OBJ_ASM := \
	$(patsubst $(TOP)/%.asm,$(BUILD)/%.asm.o,$(ASM_SRC))

OBJECTS := \
	$(BUILD)/kernel/src/main.c.o \
    $(filter-out $(BUILD)/kernel/src/main.c.o, $(OBJ_C)) \
    $(OBJ_ASM)

STAGE1 := $(BUILD)/stage1.bin
STAGE2 := $(BUILD)/stage2.bin
KERNEL_ELF := $(BUILD)/kernel.elf
KERNEL_BIN := $(BUILD)/kernel.bin
IMAGE := $(BUILD)/kernel.img

.PHONY: all run info
.DELETE_ON_ERROR:

all: $(IMAGE)
$(BUILD)/arch/%.c.o: $(TOP)/arch/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/arch/%.asm.o: $(TOP)/arch/%.asm
	@mkdir -p $(dir $@)
	$(AS) -f elf32 $< -o $@

$(BUILD)/kernel/%.c.o: $(TOP)/kernel/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/drivers/%.c.o: $(TOP)/drivers/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/lib/%.c.o: $(TOP)/lib/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/kernel/%.asm.o: $(TOP)/kernel/%.asm
	@mkdir -p $(dir $@)
	$(AS) -f elf32 $< -o $@

$(BUILD)/drivers/%.asm.o: $(TOP)/drivers/%.asm
	@mkdir -p $(dir $@)
	$(AS) -f elf32 $< -o $@

$(BUILD)/lib/%.asm.o: $(TOP)/lib/%.asm
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
