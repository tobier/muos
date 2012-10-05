## MuOS (Micro Operating System)

__Note__: This is work in progress.

This project implements a simple hobbyist operating system, mainly meant to be used as a learning tool.
The design is based on Unix, specifically the __xv6__ operating system.

## Building

You'll need GNU Make and GCC to build the bootable disk image. Just run 'make' in the top directory to build.
If the build host is not a 32-bit x86 machine, a cross-compiler will be needed.

## Running

The disk image can be written to a flash drive and booted on a real x86 machine. However, using QEMU instead
is very recommended, in case there are some serious bugs that may break something. MuOS can be run in QEMU as follows:

   qemu muos.img