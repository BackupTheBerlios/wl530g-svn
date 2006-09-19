# $Id$

CC := arm-elf-gcc
INSTALL_TARGET = ../../../../../firmware_files/rootfs

all: 
	make -C mtd	
	make -C rc
	make -C httpd

install: 
	make -C mtd install
	make -C rc install
	make -C httpd install
	

clean: 
	make -C mtd clean
	make -C rc clean
	make -C httpd clean

	
