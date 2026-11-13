# Custom cross compilers that we built using the cross-compiler script
# The location of these is setup in that script so adjust as necessary.

CROSS		?= aarch64-none-elf
CROSS_SRC	?= ~/opt/cross/bin

CC = $(CROSS_SRC)/$(CROSS)-gcc
AS = $(CROSS_SRC)/$(CROSS)-as
LD = $(CROSS_SRC)/$(CROSS)-ld
RE = $(CROSS_SRC)/$(CROSS)-readelf

ARCHDIR ?= ./arch/aarch64

TARGET := protos.elf

CCFLAGS ?= -ffreestanding -nostdlib
LDFLAGS ?= -T$(ARCHDIR)

# TODO:
# Seperate each of the commands for seperate rules too, maybe?
# This needs to be cleaner, need to figure out how.
all:
	$(CC) $(CCFLAGS) -c $(ARCHDIR)/boot.S -o boot.o
	$(CC) $(CCFLAGS) -c protos.c -o protos.o
	$(CC) $(CCFLAGS) -c ./uart/uart.c -o uart.o
	$(LD) -nostdlib $(LDFLAGS)/linker.ld boot.o uart.o protos.o -o $(TARGET)

clean:
	rm *.o *.elf

debug:
	$(AS) -g $(ARCHDIR)/boot.S -o boot.o
	$(CC) $(CCFLAGS) -g -O0 -c protos.c -o protos.o
	$(CC) $(CCFLAGS) -g -O0 -c ./uart/uart.c -o uart.o
	$(LD) -nostdlib $(LDFLAGS)/linker.ld boot.o uart.o protos.o -o $(TARGET)

run:$(TARGET)
	qemu-system-aarch64 \
	-machine virt \
	-cpu cortex-a57 \
	-nographic \
	-kernel $(TARGET)

gdb:$(TARGET)
	qemu-system-aarch64 \
	-machine virt \
	-cpu cortex-a57 \
	-nographic \
	-s -S
	-kernel $(TARGET)

sym:$(TARGET)
	$(RE) -s $(TARGET)

.PHONY: all clean run sym
