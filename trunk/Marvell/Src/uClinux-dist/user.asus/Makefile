#
#	Makefile -- Build instructions for user level apps
#

.EXPORT_ALL_VARIABLES:

#
# Include architecture specific build rules.
#

ifndef ROOTDIR
ROOTDIR=..
endif

UCLINUX_BUILD_USER=1
-include $(LINUX_CONFIG)
-include $(CONFIG_CONFIG)
-include $(ARCH_CONFIG)
-include $(MODULES_CONFIG)

VEND=$(ROOTDIR)/vendors

#
# must run the vendor build first
#
dir_v = $(VEND)/$(CONFIG_VENDOR)/$(CONFIG_PRODUCT)/. $(ROOTDIR)/prop

dir_y =
dir_n =
dir_  =

dir_$(CONFIG_USER_GPIO_UTIL)        	    += gpio_util

all:
	for i in $(sort $(dir_y)) $(dir_v) ; do \
		[ ! -d $$i ] || make -C $$i || exit $? ; \
	done

romfs:
	for i in $(dir_v) $(sort $(dir_y)) ; do \
		[ ! -d $$i ] || make -C $$i romfs || exit $? ; \
	done

clean:
	-for i in $(dir_v) $(sort $(dir_y) $(dir_n) $(dir_)) ; do \
		[ ! -d $$i ] || make -C $$i clean && rm $$i/*.gdb && rm $$i/*.elf; \
	done
	
convert:
	-for i in $(dir_v) $(sort $(dir_y) $(dir_n) $(dir_)) ; do \
		[ ! -d $$i ] || make -C $$i convert; \
	done

prune:
	-for i in $(sort $(dir_n) $(dir_)) ; do \
		found=0; \
		for j in $(sort $(dir_y)) ; do \
			if [ $$i == $$j ]; then \
				found=1; \
			fi; \
		done; \
		if [ $$found == 0 ]; then \
			rm -r $$i; \
		fi; \
	done
