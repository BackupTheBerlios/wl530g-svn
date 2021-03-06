# Generated automatically from Makefile.in by configure.
##
##  Makefile -- smtpclient makefile
##  Copyright (c) 1997 Ralf S. Engelschall, All Rights Reserved. 
##


# ------------------------------------------------
#   DEFINITIONS
# ------------------------------------------------

# CC              = gcc
# CFLAGS          = -g
# LDFLAGS         = 
LIBS            = 

INSTALL         = /usr/bin/install -c
INSTALL_PROGRAM = ${INSTALL} -s -m 755
INSTALL_SCRIPT  = ${INSTALL} -m 755
INSTALL_DATA    = ${INSTALL} -m 644
MKDIR           = ./etc/mkinstalldirs

prefix          = /usr/local

# ------------------------------------------------
#   THE DEFAULT TARGETS
# ------------------------------------------------

all: config mail smtpclient.1

# ------------------------------------------------
#   THE CONFIGURATION SUPPORT
# ------------------------------------------------

config: configure config.h.in

configure: configure.in 
	rm -f configure
	autoconf configure.in >configure
	chmod 770 configure

config.h.in: configure.in
	rm -f config.h.in
	autoheader configure.in >config.h.in

# ------------------------------------------------
#   THE RELEASE STUFF
# ------------------------------------------------

_GETDISTINFO = \
    _version=`./etc/newvers -lc -d smtpclient_vers.c`; \
    _date=`date '+%y%m%d_%H%M'`

_BUILDDIST = \
    echo "Creating tarball..."; \
    tar cvf - * |\
    tardy --user_number=1000  --user_name=rse \
          --group_number=1000 --group_name=en \
          --prefix=$${_distname} - |\
    gzip >$${_tarball}; \
    echo "Done"; \
    ls -l $${_tarball}

_NEWVERS = \
    ./etc/newvers -lc -p SMTPclient $$OPT smtpclient_vers.c; \
    V=`./etc/newvers -lc -D gfont_vers.c`;\
    sed -e "s/Version .*(.*)/Version $$V/g" <README >README.n && mv README.n README

_UPDATEVERS = \
    V=`./etc/newvers -lc -d smtpclient_vers.c`;\
    ./etc/newvers -lc -p SMTPclient -r $$V smtpclient_vers.c; \
    V=`./etc/newvers -lc -D smtpclient_vers.c`;\
    sed -e "s/Version .*(.*)/Version $$V/g" <README >README.n && mv README.n README

release: distclean fixperm
	@$(_GETDISTINFO) \
    _distname="smtpclient-$${_version}"; \
    _tarball="/tmp/$${_distname}.tar.gz"; \
    echo "Release Distribution: SMTPclient Version $$_version"; \
    $(_BUILDDIST); \
    mv /tmp/$${_distname}.tar.gz $${_distname}.tar.gz; \

new-version:
	OPT=-iv; $(_NEWVERS)

new-revision:
	OPT=-ir; $(_NEWVERS)

new-betalevel:
	OPT=-ib; $(_NEWVERS)

new-patchlevel:
	OPT=-iP; $(_NEWVERS)

new-release:
	OPT=-r$(R); $(_NEWVERS)

update-version:
	$(_UPDATEVERS)

fixperm:
	./etc/fixperm *

# ------------------------------------------------
#   THE PROGRAM
# ------------------------------------------------

mail: smtpclient_main.o smtpclient_getopt.o smtpclient_errno.o smtpclient_vers.o 
	$(CC) $(LDFLAGS) -o $@ smtpclient_main.o smtpclient_getopt.o smtpclient_errno.o smtpclient_vers.o $(LIBS) $(LDLIBS)

smtpclient_main.o: smtpclient_main.c
	$(CC) $(CFLAGS) -o smtpclient_main.o -c smtpclient_main.c

smtpclient_getopt.o: smtpclient_getopt.c
	$(CC) $(CFLAGS) -o smtpclient_getopt.o -c smtpclient_getopt.c

smtpclient_errno.o: smtpclient_errno.c
	$(CC) $(CFLAGS) -o smtpclient_errno.o -c smtpclient_errno.c

smtpclient_vers.o: smtpclient_vers.c
	$(CC) $(CFLAGS) -o smtpclient_vers.o -c smtpclient_vers.c

# ------------------------------------------------
#   THE DOCUMENTATION
# ------------------------------------------------

smtpclient.1: smtpclient.pod
	V=`./etc/newvers -l c -D smtpclient_vers.c`; \
    sed -e "s|\@V\@|$$V|g" \
        <smtpclient.pod >/tmp/smtpclient.pod; \
    pod2man --section=1 \
            --center="Ralf S. Engelschall" \
            --release="EN" \
            /tmp/smtpclient.pod >smtpclient.1 && \
    rm -f /tmp/smtpclient.pod

# ------------------------------------------------
#   INSTALLATION
# ------------------------------------------------

install: all
	$(MKDIR) $(prefix)/bin
	$(MKDIR) $(prefix)/man/man1
	$(INSTALL_PROGRAM) smtpclient $(prefix)/bin/smtpclient
	$(INSTALL_DATA) smtpclient.1 $(prefix)/man/man1/smtpclient.1

romfs:
	$(ROMFSINST) /bin/mail

# ------------------------------------------------
#   CLEANUP
# ------------------------------------------------

clean:
	-rm -f *.o
	-rm -f smtpclient smtpclient.gdb smtpclient.elf
	-rm -f core *.core

distclean:
	-@make clean
	-rm -f config.h
	-rm -f config.status config.cache config.log
	-rm -f Makefile

##EOF##
