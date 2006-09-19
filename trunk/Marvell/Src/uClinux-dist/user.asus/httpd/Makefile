#
# milli_httpd Makefile
#
# Copyright (C) 2001 Broadcom Corporation
#
# $Id $
#
CC=arm-elf-gcc

INSTALLDIR=../../../../../firmware_files/rootfs
CFLAGS	+= -I. -I../shared/include -I../../uClinux-dist/uClibc/include -Wall -Dlinux -DLinux -DEMBED -DASUS
CFLAGS	+= -s -O2
LDFLAGS	+= -Wl,-elf2flt=""
vpath %.c $(TOP)/shared
vpath %.c $(TOP)/shared_common

all: httpd

clean:
	rm -f *.o *~ httpd

install: all
	install -D httpd $(INSTALLDIR)/sbin/httpd

httpd: httpd.o ej.o cgi.o web_ex.o ../shared/shutils.o common.o nvram_f.o nvmap.o utility.o ../shared/nvram_linux.o ../netconf/netconf_linux.o
	$(CC) $(CFLAGS) -o $@ $^  $(LDFLAGS) ../iptables/libiptc/libiptc.a
