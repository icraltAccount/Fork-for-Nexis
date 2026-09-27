

 ## FudidOS

<p align="center">
  <strong>An x86 kernel built from scratch.</strong>
</p>

<p align="center">
  <img src="https://img.shields.io/badge/Architecture-i386-informational?style=flat-square" alt="Architecture">
  <img src="https://img.shields.io/badge/Language-C%20%2F%20NASM-blue?style=flat-square" alt="Language">
  <img src="https://img.shields.io/badge/Build-Make-000000?style=flat-square" alt="Build">
  <img src="https://img.shields.io/badge/Tested-QEMU%20%2B%20Real%20Hardware-orange?style=flat-square" alt="Testing">
  <img src="https://img.shields.io/badge/License-MIT-green?style=flat-square" alt="License">
</p>

# Overview


FudidOS is a kernel developed from scratch for the i386 architecture.

The project focuses on low-level systems programming, x86 architecture, hardware interaction, interrupt handling, memory management, process infrastructure, kernel initialization, and bootloader development.

FudidoOS was originally based on C and assembly at its inception.

Originally, the bootloader was a custom one written in assembly, but in this version, it was adapted to use grub.

The kernel was designed to handle the transition from:

`Ring 0 -> drivers -> Ring 3`

It is a kernel designed to serve as the foundation for an operating system; it comes complete with memory management, drivers, gdt, a bootloader, and more.


> The project is a real kernel built from scratch.


# What does the kernel actually include?

The kernel aims to provide complete memory management, along with initialization and the transition from 16-bit to 32-bit protection.


# authors

The authors of this project are low-level enthusiasts who love challenges; they created this project for the sake of learning and to approach the work with seriousness.

The authors below are:

@saintshr
@icarotelesdasilva
@collauzz-coder

# LICENSE

The kernel is licensed under the MIT License; check the LICENSE file for more information.

# MIT

MIT License

Copyright (c) 2026 icarotelesdasilva colauzz-coder saintsHr

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
