# Generated automatically from Makefile.in by configure.
#
# Minimum environment and virtual path setup
#
SHELL		= /bin/sh
srcdir		= .
top_srcdir	= ..


#
# Paths
#
prefix		= /usr/local
exec_prefix	= /usr/local
bindir		= ${exec_prefix}/bin
sbindir		= ${exec_prefix}/sbin
libdir		= ${exec_prefix}/lib
datadir		= ${prefix}/share
includedir	= ${prefix}/include/ucd-snmp
mandir		= ${prefix}/man
man1dir		= $(mandir)/man1
man3dir		= $(mandir)/man3
man5dir		= $(mandir)/man5
man8dir		= $(mandir)/man8
snmplibdir	= $(datadir)/snmp
mibdir		= $(snmplibdir)/mibs
persistentdir	= /tmp


#
# Programs
#
INSTALL		= /usr/bin/install -c
SED		= sed
#RANLIB		= ranlib
LN_S		= ln -s

#
# Compiler arguments
#
# CFLAGS		= -g -O2 -Dlinux
EXTRACPPFLAGS	= -x c
# LDFLAGS		=  

#
# Shared library commands (or not)
#
SHLIB_CFLAGS		= 
SHLIB_EXTENSION		= a
SHLIB_VERSION		= 
SHLIB_LDCONFIG_CMD	= :
SHLIB_LD_CMD		= $(AR) cr
SHLIB_LD_LIBS		= 
CC_RUNTIME_ARG		= 

#
# Makefile for snmplib
#

TARG=	libsnmp.$(SHLIB_EXTENSION)$(SHLIB_VERSION)

#all but md5.h, vacm.h, libsnmp.h, and read_config.h are copied to the installed
#include directory
INSTALLHEADERS=\
	asn1.h \
	callback.h \
	default_store.h \
	int64.h \
	keytools.h \
	mib.h \
	parse.h \
	read_config.h \
	scapi.h \
	snmp.h \
	snmp_alarm.h \
	snmp_api.h \
	snmp_client.h \
	snmp_debug.h \
	snmp_impl.h \
	snmp_logging.h \
	snmpv3.h \
	system.h \
	tools.h \
	transform_oids.h \
	ucd-snmp-includes.h

CSRCS=	snmp_client.c mib.c parse.c snmp_api.c snmp.c 		\
	snmp_auth.c asn1.c md5.c 				\
	system.c vacm.c int64.c read_config.c 			\
	snmp_debug.c tools.c  snmp_logging.c			\
	snmpv3.c snmpusm.c lcd_time.c keytools.c		\
	scapi.c callback.c default_store.c snmp_alarm.c	mt_support.c

OBJS=	snmp_client.o mib.o parse.o snmp_api.o snmp.o 		\
	snmp_auth.o asn1.o md5.o 				\
	system.o vacm.o int64.o read_config.o 			\
	snmp_debug.o tools.o  snmp_logging.o			\
	snmpv3.o snmpusm.o lcd_time.o keytools.o		\
	scapi.o callback.o default_store.o snmp_alarm.o	mt_support.o

# CFLAGS	 = -g -O2 -Dlinux 
CPPFLAGS = -I. -I.. -I$(srcdir) -I$(srcdir)/.. $(INCS)
# CC	 = $(CC) $(CPPFLAGS)

all: $(TARG)
romfs:

libsnmp.$(SHLIB_EXTENSION)$(SHLIB_VERSION):    ${OBJS}
	$(SHLIB_LD_CMD) libsnmp.$(SHLIB_EXTENSION)$(SHLIB_VERSION) ${OBJS}
	$(RANLIB) libsnmp.$(SHLIB_EXTENSION)$(SHLIB_VERSION)

installdirs:
	@$(SHELL) $(srcdir)/../mkinstalldirs $(libdir) $(includedir)

install:	$(TARG) installdirs
	@for i in $(TARG) ; do $(INSTALL) $$i $(libdir) ; $(RANLIB) $(libdir)/$$i ; echo "install:  installed $$i in $(libdir)" ; done
	@for i in $(INSTALLHEADERS) ; do $(INSTALL) $(srcdir)/$$i $(includedir) ; echo "install:  installed $$i in $(includedir)" ; done
	$(SHLIB_LDCONFIG_CMD)

../lib/libsnmp.$(SHLIB_EXTENSION)$(SHLIB_VERSION):	libsnmp.$(SHLIB_EXTENSION)$(SHLIB_VERSION)
	cp libsnmp.$(SHLIB_EXTENSION)$(SHLIB_VERSION) ../lib
	ranlib ../lib/libsnmp.$(SHLIB_EXTENSION)$(SHLIB_VERSION) $(SHLIB_LD_LIBS)

parse:  mib.o parse.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -DTEST parse.c mib.o -o parse

lint:
	lint -nhx $(CSRCS)

clean:
	rm -f ${OBJS} ${TARG}
	rm -f ../lib/${TARG}

depend: 
	makedepend $(CPPFLAGS) $(srcdir)/*.c

nosysdepend:
	makedepend $(CPPFLAGS) *.c
	perl -n -i.bak $(top_srcdir)/makenosysdepend.pl Makefile

makefileindepend: nosysdepend
	perl $(top_srcdir)/makefileindepend.pl

# DO NOT DELETE THIS LINE -- make depend depends on it.

asn1.o: ../config.h ../s/linux.h ../s/sysv.h ../s/generic.h ../m/generic.h
asn1.o:   asn1.h int64.h
asn1.o: snmp_debug.h mib.h snmp_api.h snmp_impl.h
callback.o: ../config.h ../s/linux.h ../s/sysv.h ../s/generic.h
callback.o: ../m/generic.h  
callback.o:   tools.h
callback.o: callback.h asn1.h snmp_api.h snmp_debug.h
default_store.o: ../config.h ../s/linux.h ../s/sysv.h ../s/generic.h
default_store.o: ../m/generic.h 
default_store.o:   asn1.h
default_store.o: snmp_api.h snmp_debug.h snmp_logging.h 
default_store.o: tools.h read_config.h default_store.h system.h
int64.o: ../config.h ../s/linux.h ../s/sysv.h ../s/generic.h ../m/generic.h
int64.o: asn1.h int64.h
keytools.o: ../config.h ../s/linux.h ../s/sysv.h ../s/generic.h
keytools.o: ../m/generic.h  
keytools.o: asn1.h snmp_api.h 
keytools.o:  scapi.h keytools.h
keytools.o: tools.h snmp_debug.h snmp_logging.h 
keytools.o:  transform_oids.h
lcd_time.o: ../config.h ../s/linux.h ../s/sysv.h ../s/generic.h
lcd_time.o: ../m/generic.h  
lcd_time.o:   asn1.h
lcd_time.o: snmp_api.h snmpusm.h lcd_time.h snmp_debug.h tools.h scapi.h
lcd_time.o: transform_oids.h
md5.o: ../config.h ../s/linux.h ../s/sysv.h ../s/generic.h ../m/generic.h
md5.o:   md5.h
mib.o: ../config.h ../s/linux.h ../s/sysv.h ../s/generic.h ../m/generic.h
mib.o:  asn1.h snmp_api.h mib.h snmp.h snmp_impl.h
mib.o: parse.h int64.h system.h read_config.h snmp_debug.h default_store.h
mt_support.o: ../config.h ../s/linux.h ../s/sysv.h ../s/generic.h
mt_support.o: ../m/generic.h  
mt_support.o:  mt_support.h
parse.o: ../config.h ../s/linux.h ../s/sysv.h ../s/generic.h ../m/generic.h
parse.o: snmp_logging.h  
parse.o:   system.h
parse.o:   parse.h asn1.h
parse.o: mib.h snmp_api.h snmp_debug.h default_store.h tools.h
read_config.o: ../config.h ../s/linux.h ../s/sysv.h ../s/generic.h
read_config.o: ../m/generic.h  
read_config.o:  ./getopt.h
read_config.o:   asn1.h
read_config.o: mib.h parse.h system.h snmp_api.h snmp_debug.h snmp_logging.h
read_config.o:   snmp_impl.h
read_config.o: default_store.h callback.h read_config.h tools.h
scapi.o: ../config.h ../s/linux.h ../s/sysv.h ../s/generic.h ../m/generic.h
scapi.o:   asn1.h tools.h
scapi.o: snmp_api.h snmpusm.h keytools.h snmp_debug.h scapi.h callback.h
scapi.o: snmp_impl.h 
scapi.o:  system.h transform_oids.h
snmp.o: ../config.h ../s/linux.h ../s/sysv.h ../s/generic.h ../m/generic.h
snmp.o:  asn1.h snmp.h snmp_api.h snmp_impl.h
snmp.o: snmp_logging.h   mib.h
snmp_alarm.o: ../config.h ../s/linux.h ../s/sysv.h ../s/generic.h
snmp_alarm.o: ../m/generic.h  
snmp_alarm.o:  ./getopt.h 
snmp_alarm.o:   asn1.h
snmp_alarm.o: snmp_api.h snmp_debug.h tools.h default_store.h callback.h
snmp_alarm.o: snmp_alarm.h
snmp_api.o: ../config.h ../s/linux.h ../s/sysv.h ../s/generic.h
snmp_api.o: ../m/generic.h  
snmp_api.o: ./getopt.h  
snmp_api.o:   asn1.h snmp.h
snmp_api.o: snmp_api.h snmp_client.h snmp_impl.h parse.h mib.h system.h
snmp_api.o: int64.h snmpv3.h read_config.h snmp_debug.h snmpusm.h tools.h
snmp_api.o: keytools.h lcd_time.h callback.h snmp_alarm.h snmp_logging.h
snmp_api.o:   default_store.h
snmp_api.o: mt_support.h transform_oids.h
snmp_auth.o: ../config.h ../s/linux.h ../s/sysv.h ../s/generic.h
snmp_auth.o: ../m/generic.h  
snmp_auth.o:   asn1.h
snmp_auth.o: snmp.h snmp_api.h snmp_impl.h mib.h md5.h system.h tools.h
snmp_auth.o: snmp_debug.h scapi.h
snmp_client.o: ../config.h ../s/linux.h ../s/sysv.h ../s/generic.h
snmp_client.o: ../m/generic.h  
snmp_client.o: ./getopt.h  
snmp_client.o:  asn1.h snmp.h snmp_api.h snmp_impl.h
snmp_client.o: snmp_client.h mib.h
snmp_debug.o: ../config.h ../s/linux.h ../s/sysv.h ../s/generic.h
snmp_debug.o: ../m/generic.h  
snmp_debug.o:  asn1.h mib.h snmp_api.h
snmp_debug.o: read_config.h snmp_debug.h snmp_impl.h snmp_logging.h
snmp_logging.o: ../config.h ../s/linux.h ../s/sysv.h ../s/generic.h
snmp_logging.o: ../m/generic.h  
snmp_logging.o:   asn1.h
snmp_logging.o: default_store.h snmp_logging.h
snmpusm.o: ../config.h ../s/linux.h ../s/sysv.h ../s/generic.h ../m/generic.h
snmpusm.o:   asn1.h
snmpusm.o: snmp_api.h snmp_debug.h callback.h tools.h keytools.h snmp.h
snmpusm.o: read_config.h snmpv3.h snmp-tc.h lcd_time.h scapi.h snmpusm.h
snmpusm.o: transform_oids.h
snmpv3.o: ../config.h ../s/linux.h ../s/sysv.h ../s/generic.h ../m/generic.h
snmpv3.o:  ./getopt.h 
snmpv3.o:  system.h asn1.h snmpv3.h snmpusm.h snmp.h
snmpv3.o: snmp_api.h snmp_impl.h read_config.h lcd_time.h scapi.h tools.h
snmpv3.o: keytools.h snmp_debug.h snmp_logging.h 
snmpv3.o:  callback.h default_store.h
snmpv3.o: transform_oids.h
system.o: ../config.h ../s/linux.h ../s/sysv.h ../s/generic.h ../m/generic.h
system.o: ./getopt.h  
system.o:  asn1.h snmp_api.h system.h snmp_logging.h
tools.o: ../config.h ../s/linux.h ../s/sysv.h ../s/generic.h ../m/generic.h
tools.o:  asn1.h system.h snmp_api.h snmp_debug.h
tools.o: tools.h mib.h scapi.h
vacm.o: ../config.h ../s/linux.h ../s/sysv.h ../s/generic.h ../m/generic.h
vacm.o:   ./getopt.h
vacm.o:  asn1.h snmp.h snmp_api.h vacm.h
vacm.o: snmp_debug.h
