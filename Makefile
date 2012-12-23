# This is the main Makefile for muos. It sets up variables that are needed
# when doing the recursive make down into the subdirectories.

# Save the source directory
src_tree = $(CURDIR)

# Cross-compiling
# ---------------------------------------------------------------------------
# muos is a 32-bit operating system for the x86 architecture. If the build
# host is not a 32-bit x86 machine, muos needs to be cross-compiled.

# Uncomment when doing using a cross compiler. The prefix may need to be
# adjusted depending on the host machine configuration.
CROSS_COMPILE 	= i386-unknown-elf-

# Global variables
# ---------------------------------------------------------------------------
# We are doing a recursive build, so we need to set up some global variables
# so we don't have to redefine CC etc. in the sub-directories.

# Make variables
CC		= $(CROSS_COMPILE)gcc
AS		= $(CROSS_COMPILE)nasm
LD		= $(CROSS_COMPILE)ld
OBJCOPY		= $(CROSS_COMPILE)objcopy

CFLAGS		= -fno-pic -static -nostdlib -fno-builtin \
                  -nostartfiles -nodefaultlibs -fno-strict-aliasing \
                  -Wall -Wextra -Werror -fno-omit-frame-pointer -I$(src_tree)/include
ASFLAGS 	= -t elf32

# Object files that to be linked into mukernel. It'll be populated
# by the includes below.
OBJECTS=

include drivers/Makefile
include kernel/Makefile
include lib/Makefile

# Beautify output
# ---------------------------------------------------------------------------
QUIET_CC = @echo    '   ' CC'      '$<;
QUIET_AS = @echo    '   ' AS'      '$<;

# Build targets
# ---------------------------------------------------------------------------
default: image

bootblock: boot/bootmain.c boot/bootasm.S util/sign.pl
	@$(CC) -I./boot $(CFLAGS) -fno-pic -O -nostdinc -c boot/bootmain.c
	@$(CC) -I./boot $(CFLAGS) -fno-pic -nostdinc -c boot/bootasm.S
	@$(LD) $(LDFLAGS) -N -e start -Ttext 0x7C00 -o bootblock.o bootasm.o bootmain.o
	@$(OBJCOPY) -S -O binary -j .text bootblock.o bootblock
	@./util/sign.pl bootblock 2> /dev/null 

mukernel: $(OBJECTS) util/kernel.ld
	@$(LD) $(LDFLAGS) -T util/kernel.ld -o mukernel $(OBJECTS)

image: bootblock mukernel
	@dd if=/dev/zero of=muos.img count=10000 2> /dev/null
	@dd if=bootblock of=muos.img conv=notrunc 2> /dev/null	
	@dd if=mukernel of=muos.img seek=1 conv=notrunc 2> /dev/null

qemu: image
	@qemu muos.img

clean:
	@rm -rf muos.img mukernel bootblock *~ include/*~ $(OBJECTS) *.o

.s.o:
	$(QUIET_AS)$(AS) -o $*.o $<
.c.o:
	$(QUIET_CC)$(CC) $(CFLAGS) -c -o $*.o $<