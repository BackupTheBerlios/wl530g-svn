

This buildroot is still a mess, but it's getting better.



HowTo build a firmware image (doesn't require compiling):

1.) edit the files in firmware_files/rootfs however you wish.
    These are the files the firmware image contains.
2.) run create_firmware_image.sh to build a firmware with today's date.



HowTo compile your own packages and/or kernel:

1.) Download and install toolchains built specifically for this firmware:
    http://sukkamehulinko.romikselle.com/wl530g/arm-elf-tools-20060917.tar.gz   
    	tar -xzvf arm-elf-tools-20060917.tar.gz
    If this fails, use dd to extract the tar.gz to / (root).
2.) Go to Marvell/Src/uClinux-dist.
3.) Run 'make menuconfig' to configure the kernel and user packages to build.
4.) Copy built packages the changed into firmware filesystem (firmware_files/rootfs).
5.) The kernel can be replaced by storing the new zImage as 
    firmware_files/image_parts/segment1. Note that the size should be
    <= 0xA0000 bytes.
6.) Some packages aren't in the primary makefile and can be found in:
     	uClinux-dist/user.asus
    At present, you must build these packages individually and install 
    any you want into the firmware filesystem. You should place packages that have
    vendor/board specific extensions here.


For help, visit the forums. 

I'm happily extending write access to anyone willing to help with development.
If you are interested, email me. 

- jeremy collake <jeremy.collake@gmail.com>



Advanced HowTo:

In order to build BusyBox 1.21 you must rebuild the arm-elf uClibc toolchains so that appropriate
settings are made. 

	Rebuilding the toolchains:

		See build-uclinux-tools.sh in the uCLinux-dist folder. Do NOT use the standard
		one since I've patched this copy up as necessary for our needs. Prequisites can
		be found here (download all of them, except the build-uclinix-tools.sh):		

			http://www.uclinux.org/pub/uClinux/arm-elf-tools/tools-20030314/

				
		Alternatively, you can check out the newer GCC 3.4.0 toolchains here:
		
			http://www.uclinux.org/pub/uClinux/arm-elf-tools/gcc-3/

		Note: GCC 3.4.0 may not work right with this uClinux-dist. Minor code
		 tweaks here and there seem required.		

		There are also experimental GCC 4.0 toolchains.
			






