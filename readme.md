

 ## FudidOS

https://camo.githubusercontent.com/4f120bbdd1ddd982e7a4c143e6df4d9ff23a5132473156e3a03d96be4b6b0447/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f4172636869746563747572652d693338362d696e666f726d6174696f6e616c3f7374796c653d666c61742d737175617265
https://camo.githubusercontent.com/abb511f218dcb8e39d2fc3bc3f2ac7dd8eac3dc5a43d847261c652a3203f9261/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f5465737465642d51454d552532302532422532305265616c25323048617264776172652d6f72616e67653f7374796c653d666c61742d737175617265
https://camo.githubusercontent.com/87a9316f4bcda1dd5768bf56b5a2ec837448781875d44aefce39b571ce945929/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f4c6963656e73652d47504c2d2d322e302d677265656e3f7374796c653d666c61742d737175617265

# Overview


FudidOS is a kernel developed from scratch for the i386 architecture.

The project focuses on low-level systems programming, x86 architecture, hardware interaction, interrupt handling, memory management, process infrastructure, kernel initialization, and bootloader development.

FudidoOS was originally based on C and assembly at its inception.

Originally, the bootloader was a custom one written in assembly, but in this version, it was adapted to use grub.

The kernel was designed to handle the transition from:

'''Ring 0 -> drivers -> Ring 3'''

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
