# $Id: Makefile 3198 2006-02-09 03:21:01Z nbd $

LINUX_SRC := ../../uClinux-dist/linux-2.4.x
PKG_BUILD_DIR := $(BUILD_DIR)/$(PKG_NAME)
CC := arm-elf-gcc
CFLAGS	+= -I. -Wall -Dlinux 
LDFLAGS	+= -Wl,-elf2flt="-s 1024"
INSTALL_TARGET = ../../../../../firmware_files/rootfs

all: reboot

reboot: reboot.o
	$(CC) -o $@ $^ $(LDFLAGS)

install: reboot
	install $^ $(INSTALL_TARGET)/sbin/$^

clean: reboot
	rm $^
	rm $^.o
	rm $^.gdb
	

	
