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

.PHONY: all run info clean

all run info:
	$(MAKE) -C arch/$(ARCH) $@

clean:
	rm -rf $(BUILD)/$(ARCH)
