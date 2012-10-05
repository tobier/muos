# Makefile for the boot sector

objs += mupp

default:
	@echo $(objs)

OBJCOPY = $(TOOLSPREFIX)objcopy

bootblock: bootasm.S bootmain.c
	$(CC) $(CFLAGS) -fno-pic -O -nostdinc -c bootmain.c
	$(CC) $(CFLAGS) -fno-pic -nostdinc -c bootasm.S
	$(LD) $(LDFLAGS) -N -e start -Ttext 0x7C00 -o bootblock.o bootasm.o bootmain.o
	$(OBJCOPY) -S -O binary -j .text bootblock.o bootblock
	$(ROOT)/util/sign.pl bootblock

clean:
	rm -rf *.o *~