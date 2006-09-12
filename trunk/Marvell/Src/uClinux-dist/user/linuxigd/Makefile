LDLIBS= -lpthread -lixml -lthreadutil -lupnp -lthreadutil
#LDFLAGS += -D_REENTRANT
CFLAGS += -D_REENTRANT

EXEC = upnpd
OBJS = main.o gatedevice.o pmlist.o util.o config.o

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) -o $@  $(OBJS) $(LDLIBS$(LDLIBS-$(@)))

romfs:	
	$(ROMFSINST) upnpd     			/bin/upnpd
	$(ROMFSINST) etc/upnpd.conf			/etc/upnpd.conf
	$(ROMFSINST) etc/gatedesc.xml 			/etc/linuxigd/gatedesc.xml
	$(ROMFSINST) etc/gateconnSCPD.xml 	/etc/linuxigd/gateconnSCPD.xml
	$(ROMFSINST) etc/gateicfgSCPD.xml 	/etc/linuxigd/gateicfgSCPD.xml
	$(ROMFSINST) etc/dummy.xml 			/etc/linuxigd/dummy.xml
	$(ROMFSINST) etc/ligd.gif 			/etc/linuxigd/ligd.gif
clean:
	-rm -f $(EXEC) *.elf *.gdb *.o
