deps_config := \
	sysklogd/Config.in \
	shell/Config.in \
	procps/Config.in \
	networking/udhcp/Config.in \
	networking/Config.in \
	miscutils/Config.in \
	util-linux/Config.in \
	modutils/Config.in \
	e2fsprogs/Config.in \
	loginutils/Config.in \
	init/Config.in \
	findutils/Config.in \
	editors/Config.in \
	debianutils/Config.in \
	console-tools/Config.in \
	coreutils/Config.in \
	archival/Config.in \
	libbb/Config.in \
	/home/db90h/llf/trunk/Marvell/Src/uClinux-dist/user/busybox-1.2.1/Config.in

.config include/config.h: $(deps_config)

$(deps_config):