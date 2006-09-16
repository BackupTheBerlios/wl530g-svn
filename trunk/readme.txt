This buildroot is still a mess. It's getting better, but you must manually
put new files into the firmware filesystem, which has its advantages and
disadvantages. I'm working on getting all Makefiles set up so they install
to the firmware filesystem (instead of romfs), and do so appropriately.

HowTo build a firmware image (doesn't require compiling):

1.) edit the files in firmware_files/rootfs however you wish.
    These are the files the firmware image contains.
2.) run create_firmware_image.sh to build a firmware with today's date.

HowTo compile your own packages and/or kernel:

1.) Download and install toolchains:
     wget http://ftp.snapgear.org/pub/snapgear/tools/arm-elf/arm-elf-tools-20030314.sh
     sh ./arm-elf-tools-20030314.sh
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
    any you want into the firmware filesystem. You should place new packages
    in the user.asus directory as well.

For help, visit the forums. 

I'm happily extending write access to anyone willing to help with development.
If you are interested, email me. 

- jeremy collake <jeremy.collake@gmail.com>
