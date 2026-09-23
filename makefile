BUILD := build

CC := gcc
LD := ld
AS := nasm
OBJCOPY := objcopy

CFLAGS := \
    -m32 \
    -ffreestanding \
    -fno-pie \
    -fno-stack-protector \
    -fno-builtin \
    -fno-asynchronous-unwind-tables \
    -fno-unwind-tables \
    -Wall \
    -Wextra

LDFLAGS := -m elf_i386 -T linker.ld

SRC := src

C_SOURCES := $(shell find $(SRC) -type f -name '*.c')
ASM_SOURCES := $(shell find $(SRC)/kernel -type f -name '*.asm')

C_OBJECTS := $(C_SOURCES:%.c=$(BUILD)/%.o)
ASM_OBJECTS := $(ASM_SOURCES:%.asm=$(BUILD)/%.o)

KERNEL_OBJECTS := $(ASM_OBJECTS) $(C_OBJECTS)

STAGE1 := $(BUILD)/stage1.bin
STAGE2 := $(BUILD)/stage2.bin

KERNEL_ELF := $(BUILD)/kernel.elf
KERNEL_BIN := $(BUILD)/kernel.bin

IMAGE := $(BUILD)/os.img

.PHONY: all clean run info

all: $(IMAGE)

$(BUILD)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/%.o: %.asm
	@mkdir -p $(dir $@)
	$(AS) -f elf32 $< -o $@

$(STAGE2): $(SRC)/boot/stage2.asm
	@mkdir -p $(BUILD)
	$(AS) -f bin $< -o $@

$(KERNEL_ELF): $(KERNEL_OBJECTS) linker.ld
	@mkdir -p $(BUILD)
	$(LD) $(LDFLAGS) -o $@ $(KERNEL_OBJECTS)

$(KERNEL_BIN): $(KERNEL_ELF)
	$(OBJCOPY) -O binary $< $@

$(STAGE1): $(SRC)/boot/stage1.asm $(STAGE2) $(KERNEL_BIN)
	@mkdir -p $(BUILD)
	$(eval KERNEL_SIZE := $(shell stat -c%s $(KERNEL_BIN)))
	$(eval KERNEL_SECTORS := $(shell echo $$(( ($(KERNEL_SIZE) + 511) / 512 ))))
	$(eval TOTAL_SECTORS := $(shell echo $$(( $(KERNEL_SECTORS) + 1 ))))
	$(AS) -f bin -dTOTAL_SECTORS=$(TOTAL_SECTORS) $< -o $@

$(IMAGE): $(STAGE1) $(STAGE2) $(KERNEL_BIN)
	@mkdir -p $(BUILD)
	cat $(STAGE1) $(STAGE2) $(KERNEL_BIN) > $@
	truncate -s $$(( ($$(stat -c%s $@) + 511) / 512 * 512 )) $@

info: $(IMAGE)
	@echo
	@stat -c '%n %s bytes' $(STAGE1)
	@stat -c '%n %s bytes' $(STAGE2)
	@stat -c '%n %s bytes' $(KERNEL_BIN)
	@stat -c '%n %s bytes' $(IMAGE)

run: $(IMAGE)
	qemu-system-i386 -drive format=raw,file=$(IMAGE)

clean:
	rm -rf $(BUILD)
