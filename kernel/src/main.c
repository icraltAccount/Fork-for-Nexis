// Copyright (c) 2026 icarotelesdasilva colauzz-coder saintsHr
// Licensed under the MIT License

#include "console/console.h"

void kinit() {
    console_clear();
}

void kmain() {
    kinit();

    console_write_string("Hello Kernel!");

    while(1);
}
