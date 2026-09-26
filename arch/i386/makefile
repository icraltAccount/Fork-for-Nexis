# Copyright (c) 2026 icarotelesdasilva colauzz-coder saintsHr
# Licensed under the MIT License

# --= Guards =--------------------------------------------------------------------------------------

ifndef TOP
$(error Run make from the project root.)
endif
ifndef BUILD
$(error Run make from the project root.)
endif

# --= Tools =---------------------------------------------------------------------------------------

CC := gcc
LD := ld
AS := nasm
OBJCOPY := objcopy
QEMU := qemu-system-i386
MKRESCUE := grub-mkrescue
GRUBFILE := grub-file

# --= Flags =---------------------------------------------------------------------------------------

INCLUDES := \
	-I$(TOP)/kernel/include -I$(TOP)/drivers/include \
	-I$(TOP)/lib/include -Iinclude

FLAGS_C := \
	-m32 -ffreestanding -fno-pie -fno-stack-protector \
	-fno-builtin -fno-asynchronous-unwind-tables \
	-fno-unwind-tables -Wall -Wextra -O2 -g \
	-MMD -MP $(INCLUDES)

FLAGS_LD := \
	-m elf_i386 -T linker.ld --no-warn-rwx-segments

# --= Sources =-------------------------------------------------------------------------------------

SRC_C := \
	$(shell find $(TOP)/kernel -name '*.c') \
	$(shell find $(TOP)/drivers -name '*.c') \
	$(shell find $(TOP)/lib -name '*.c') \
	$(shell find $(TOP)/arch -name '*.c')
SRC_ASM := \
	$(shell find $(TOP)/kernel -name '*.asm') \
	$(shell find $(TOP)/drivers -name '*.asm') \
	$(shell find $(TOP)/lib -name '*.asm') \
	$(shell find $(TOP)/arch -name '*.asm')

OBJ_C   := $(patsubst $(TOP)/%.c,$(BUILD)/%.c.o,$(SRC_C))
OBJ_ASM := $(patsubst $(TOP)/%.asm,$(BUILD)/%.asm.o,$(SRC_ASM))
DEPS    := $(OBJ_C:.o=.d)

OBJ_BOOT := $(BUILD)/arch/i386/boot/boot.asm.o
ifeq ($(filter $(OBJ_BOOT),$(OBJ_ASM)),)
$(error boot.asm not found under $(TOP)/arch/i386/boot — check ARCH layout)
endif

OBJ := \
	$(OBJ_BOOT) \
	$(BUILD)/kernel/src/main.c.o \
	$(filter-out $(OBJ_BOOT) $(BUILD)/kernel/src/main.c.o, $(OBJ_C) $(OBJ_ASM))

KERNEL_ELF := $(BUILD)/kernel.elf
ISODIR     := $(BUILD)/isodir
ISO        := $(BUILD)/kernel.iso
GRUB_CFG   := $(TOP)/arch/i386/boot/grub.cfg

# --= Rules Config =--------------------------------------------------------------------------------

.PHONY: all run info clean check-deps
.DELETE_ON_ERROR:
.SECONDARY: $(OBJ)

all: check-deps $(ISO)

# --- Sanity Check ---------------------------------------------------------------------------------

check-deps:
	@command -v $(CC) >/dev/null || { echo "ERROR: $(CC) not found"; exit 1; }
	@command -v $(LD) >/dev/null || { echo "ERROR: $(LD) not found"; exit 1; }
	@command -v $(AS) >/dev/null || { echo "ERROR: $(AS) not found"; exit 1; }
	@command -v $(QEMU) >/dev/null || { echo "ERROR: $(QEMU) not found"; exit 1; }
	@command -v $(MKRESCUE) >/dev/null || { echo "ERROR: $(MKRESCUE) not found (install grub + xorriso)"; exit 1; }
	@command -v $(GRUBFILE) >/dev/null || { echo "ERROR: $(GRUBFILE) not found (install grub)"; exit 1; }

# --- Rules ----------------------------------------------------------------------------------------

$(BUILD)/arch/%.c.o: $(TOP)/arch/%.c
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS_C) -c $< -o $@

$(BUILD)/arch/%.asm.o: $(TOP)/arch/%.asm
	@mkdir -p $(dir $@)
	$(AS) -f elf32 $< -o $@

$(BUILD)/kernel/%.c.o: $(TOP)/kernel/%.c
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS_C) -c $< -o $@

$(BUILD)/drivers/%.c.o: $(TOP)/drivers/%.c
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS_C) -c $< -o $@

$(BUILD)/lib/%.c.o: $(TOP)/lib/%.c
	@mkdir -p $(dir $@)
	$(CC) $(FLAGS_C) -c $< -o $@

$(BUILD)/kernel/%.asm.o: $(TOP)/kernel/%.asm
	@mkdir -p $(dir $@)
	$(AS) -f elf32 $< -o $@

$(BUILD)/drivers/%.asm.o: $(TOP)/drivers/%.asm
	@mkdir -p $(dir $@)
	$(AS) -f elf32 $< -o $@

$(BUILD)/lib/%.asm.o: $(TOP)/lib/%.asm
	@mkdir -p $(dir $@)
	$(AS) -f elf32 $< -o $@

# --- Linkage --------------------------------------------------------------------------------------
$(KERNEL_ELF): $(OBJ) $(TOP)/arch/i386/linker.ld
	$(LD) $(FLAGS_LD) -o $@ $(OBJ)
	@$(GRUBFILE) --is-x86-multiboot $@ && echo "Multiboot OK" || \
		{ echo "ERROR: $@ is not a valid multiboot kernel"; exit 1; }

# --- ISO Image ------------------------------------------------------------------------------------
$(ISO): $(KERNEL_ELF) $(GRUB_CFG)
	rm -rf $(ISODIR)
	@mkdir -p $(ISODIR)/boot/grub
	cp $(KERNEL_ELF) $(ISODIR)/boot/kernel.elf
	cp $(GRUB_CFG) $(ISODIR)/boot/grub/grub.cfg
	$(MKRESCUE) -o $@ $(ISODIR) 2>/dev/null

# --- Rules ----------------------------------------------------------------------------------------

info: $(ISO)
	@stat -c '%n : %s bytes' $(KERNEL_ELF) $(ISO)

run: $(ISO)
	$(QEMU) -cdrom $(ISO)

clean:
	ifeq ($(strip $(BUILD)),)
	    $(error refusing to clean: BUILD is empty)
	endif
	    rm -rf $(BUILD)

-include $(DEPS)
