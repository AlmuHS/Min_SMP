
KERNEL_ADDR=0x01000000

PROG=minsmp

OBJ= boot.o main.o video.o mem.o acpi.o mp.o lapic.o ioapic.o cpu.o

S=.

INC=$(S)/include

CC=gcc
CFLAGS= -m32 -O2
CFLAGS+= -Wall -Wextra -Werror
CFLAGS+= -fno-stack-protector
CFLAGS+= -ffreestanding
CFLAGS+= -no-pie
CFLAGS+= -I$(INC)
ASFLAGS= -m32

LD=ld
LDFLAGS= --script link.ld
LDFLAGS+= -n
LDFLAGS+= --defsym=_KERNEL_ADDR=$(KERNEL_ADDR)


all : $(PROG)

$(PROG) : $(OBJ)
	$(LD) $(LDFLAGS) -o $(PROG) $(OBJ)

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^

%.o : %.S
	$(CC) $(ASFLAGS) -c -o $@ $^

clean:
	rm -rf $(PROG) $(OBJ)
	@rm -rf *~ .*~
	@cd include && rm -rf *~ .*~ && cd ..

qemu: $(PROG)
	qemu-system-i386 -m 512 -enable-kvm \
		-cpu coreduo \
		-smp 4		\
		-kernel $(PROG) \
		-curses
		#-monitor telnet:127.0.0.1:5565,server,nowait

debug: $(PROG)
	qemu-system-i386 -m 512 -enable-kvm \
		-cpu core2duo \
		-smp 2 \
		-kernel $(PROG) \
		-curses \
		-S -s \
		-monitor telnet:127.0.0.1:5565,server,nowait 

