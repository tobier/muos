# Makefile for muos

# Cross-compiling prefix
TOOLSPREFIX=i386-unknown-elf-

CC = $(TOOLSPREFIX)gcc
AS = $(TOOLSPREFIX)as
LD = $(TOOLSPREFIX)ld
CFLAGS = -fno-pic -static -nostdlib -fno-builtin -nostartfiles -nodefaultlibs -fno-strict-aliasing -Wall -Wextra -Werror -fno-omit-frame-pointer -Iinclude
ASFLAGS = -m32 -gdwarf-2 -Wa,-divide
OBJCOPY = $(TOOLSPREFIX)objcopy

# Object files to link
OBJS=main.o

muos.img: bootblock kernel
	dd if=/dev/zero of=muos.img count=10000
	dd if=bootblock of=muos.img conv=notrunc
	dd if=kernel of=muos.img seek=1 conv=notrunc

bootblock: bootasm.S bootmain.c sign.pl
	$(CC) $(CFLAGS) -fno-pic -O -nostdinc -c bootmain.c
	$(CC) $(CFLAGS) -fno-pic -nostdinc -c bootasm.S
	$(LD) $(LDFLAGS) -N -e start -Ttext 0x7C00 -o bootblock.o bootasm.o bootmain.o
	$(OBJCOPY) -S -O binary -j .text bootblock.o bootblock
	./sign.pl bootblock

kernel: $(OBJS) kernel.ld
	$(LD) $(LDFLAGS) -T kernel.ld -o kernel $(OBJS)

clean:
	rm -rf muos.img kernel bootblock *~ include/*~ *.o