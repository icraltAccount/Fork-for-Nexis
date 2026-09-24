# Copyright (c) 2026 icarotelesdasilva colauzz-coder saintsHr
# Licensed under the MIT License

ifndef ARCH
$(error Architecture is not set. Use: make ARCH=<architecture>)
endif

ifeq ($(wildcard arch/$(ARCH)/makefile),)
$(error Unknown architecture: $(ARCH))
endif

export TOP   := $(CURDIR)
export BUILD := $(TOP)/build/$(ARCH)

.PHONY: all run info clean bear

all run info:
	$(MAKE) -C arch/$(ARCH) $@

clean:
	rm -rf $(BUILD)

bear:
	rm -rf compile_commands.json
	bear -- make ARCH=$(ARCH) all
