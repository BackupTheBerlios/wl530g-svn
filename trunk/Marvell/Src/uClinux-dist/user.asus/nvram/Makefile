#
# Linux NVRAM Makefile
#
# Copyright 2001-2003, Broadcom Corporation
# All Rights Reserved.
# 
# THIS SOFTWARE IS OFFERED "AS IS", AND BROADCOM GRANTS NO WARRANTIES OF ANY
# KIND, EXPRESS OR IMPLIED, BY STATUTE, COMMUNICATION OR OTHERWISE. BROADCOM
# SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS
# FOR A SPECIFIC PURPOSE OR NONINFRINGEMENT CONCERNING THIS SOFTWARE.
#
# $Id$
#
CC=arm-elf-gcc
CFLAGS	+= -I. -I$(SRCBASE)/include -Wall -DASUS
CFLAGS	+= -s -O2
LDFLAGS += -L. -Wl,-elf2flt="-s 64000"
vpath %.c $(SRCBASE)/shared/nvram

INSTALLDIR = ../../../../../../firmware_files

all: nvram

install: all
	install -D nvram $(INSTALLDIR)/usr/sbin/nvram	

clean:
	rm -f *.o *.a *.so nvram *.gdb

libnvram.a: nvram_linux.o
	$(LD) -o $@ $^

nvram: main.o nvram_linux.o
	$(CC) $(CFLAGS) -o $@ main.o nvram_linux.o $(LDFLAGS) 
