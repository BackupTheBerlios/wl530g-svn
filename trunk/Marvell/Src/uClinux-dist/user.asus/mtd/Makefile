# $Id: Makefile 3198 2006-02-09 03:21:01Z nbd $

LINUX_SRC := ../../linux-2.4.x
PKG_BUILD_DIR := $(BUILD_DIR)/$(PKG_NAME)
CC := arm-elf-gcc
CFLAGS	+= -O2 -Os -I. -nostdinc -Wall -Dlinux -I../../linux-2.4.x/include/asm-armnommu -I../../uClibc/include
LDFLAGS	+= -Wl,-elf2flt=""
INSTALL_TARGET = ../../../../../firmware_files/rootfs

all: mtd

mtd: mtd.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

install: mtd
	install $^ $(INSTALL_TARGET)/sbin/$^

clean: mtd
	rm $^
	rm $^.o
	rm $^.gdb
	

	
