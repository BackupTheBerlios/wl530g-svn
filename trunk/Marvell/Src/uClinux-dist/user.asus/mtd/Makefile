# $Id: Makefile 3198 2006-02-09 03:21:01Z nbd $

LINUX_SRC := ../../uClinux-dist/linux-2.4.x
PKG_BUILD_DIR := $(BUILD_DIR)/$(PKG_NAME)
CC := arm-elf-gcc
CFLAGS	+= -I. -Wall -Dlinux 
LDFLAGS	+= -Wl,-elf2flt=""
INSTALL_TARGET = ../../../../../firmware_files/db90h_edition/rootfs

all: mtd

mtd: mtd.o
	$(CC) -o $@ $^ $(LDFLAGS)

install: mtd
	install $^ $(INSTALL_TARGET)/sbin/$^

clean: mtd
	rm $^
	rm $^.o
	rm $^.gdb
	

	
