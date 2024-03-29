# Makefile from JamesM's kernel tutorials and modified by Aarch64.

AS = nasm
CC = gcc
LD = ld

# -Wall -Wstrict-prototypes
CFLAGS = -nostdlib -nostdinc -fno-builtin \
	 -fno-stack-protector -g -m32 -g
LDFLAGS = -T link.ld -m elf_i386
ASFLAGS = -f elf

SOURCES=boot.o main.o vga.o common.o descriptor_tables.o isr.o interrupt.o gdt.o timer.o \
        kheap.o paging.o ordered_array.o fs.o initrd.o task.o process.o syscall.o

all: $(SOURCES) link

link:
	$(LD) $(LDFLAGS) -o kernel $(SOURCES)
	
clean:
	rm *.o kernel
