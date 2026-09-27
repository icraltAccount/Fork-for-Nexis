

 ## FudidOS

<svg xmlns="http://www.w3.org/2000/svg" width="110" height="20" role="img" aria-label="Architecture: i386"><title>Architecture: i386</title><g shape-rendering="crispEdges"><rect width="77" height="20" fill="#555"/><rect x="77" width="33" height="20" fill="#007ec6"/></g><g fill="#fff" text-anchor="middle" font-family="Verdana,Geneva,DejaVu Sans,sans-serif" text-rendering="geometricPrecision" font-size="110"><text x="395" y="140" textLength="670" transform="scale(.1)">Architecture</text><text x="925" y="140" textLength="230" transform="scale(.1)">i386</text></g></svg>
<svg xmlns="http://www.w3.org/2000/svg" width="188" height="20" role="img" aria-label="Tested: QEMU + Real Hardware"><title>Tested: QEMU + Real Hardware</title><g shape-rendering="crispEdges"><rect width="47" height="20" fill="#555"/><rect x="47" width="141" height="20" fill="#ea7233"/></g><g fill="#fff" text-anchor="middle" font-family="Verdana,Geneva,DejaVu Sans,sans-serif" text-rendering="geometricPrecision" font-size="110"><text x="245" y="140" textLength="370" transform="scale(.1)">Tested</text><text x="1165" y="140" textLength="1310" transform="scale(.1)">QEMU + Real Hardware</text></g></svg>
<svg xmlns="http://www.w3.org/2000/svg" width="106" height="20" role="img" aria-label="License: GPL-2.0"><title>License: GPL-2.0</title><g shape-rendering="crispEdges"><rect width="51" height="20" fill="#555"/><rect x="51" width="55" height="20" fill="#67ac09"/></g><g fill="#fff" text-anchor="middle" font-family="Verdana,Geneva,DejaVu Sans,sans-serif" text-rendering="geometricPrecision" font-size="110"><text x="265" y="140" textLength="410" transform="scale(.1)">License</text><text x="775" y="140" textLength="450" transform="scale(.1)">MIT</text></g></svg>

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
