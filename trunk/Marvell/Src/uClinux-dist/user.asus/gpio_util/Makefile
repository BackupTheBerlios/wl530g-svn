
CC=arm-elf-gcc
INSTALLDIR=../../../../../firmware_files/rootfs/
CFLAGS	+= -I. -I../shared/include -I/Marvell/Src/uClinux-dist/uClibc/include -Wall -Dlinux -DLinux
CFLAGS	+= -s -O2
LDFLAGS	+= -Wl,-elf2flt="-s 4096"

EXEC = gpio
OBJS = gpio.o

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

romfs: all
	install -D $INSTALLDIR/bin/$(EXEC)	

install: all
	install -D /bin/$(EXEC)

clean:
	-rm -f $(EXEC) *.elf *.o *.gdb

