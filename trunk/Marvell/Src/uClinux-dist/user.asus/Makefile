# $Id$

CC := arm-elf-gcc
CFLAGS := -I../../linux-2.4.x/include/asm-armnommu -I../../uClibc/include
INSTALL_TARGET = ../../../../../firmware_files/rootfs

all: 
	#make -C mtd	
	make -C rc
	make -C httpd

romfs:
	#make -C mtd install
	make -C rc install
	make -C httpd install

install: 
	#make -C mtd install
	make -C rc install
	make -C httpd install
	

clean: 
	#make -C mtd clean
	make -C rc clean
	make -C httpd clean

	
