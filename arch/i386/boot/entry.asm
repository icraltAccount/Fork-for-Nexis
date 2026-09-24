; Copyright (c) 2026 icarotelesdasilva colauzz-coder saintsHr
; Licensed under the MIT License

bits 32

global _start
extern kmain

_start:
    call kmain

    .hang:
        cli
        hlt
        jmp .hang
