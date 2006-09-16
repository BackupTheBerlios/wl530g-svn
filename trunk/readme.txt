This buildroot is still a mess. It's getting better, but you must manually
put new files into the firmware filesystem, which has its advantages and
disadvantages. I'm working on getting all Makefiles set up so they install
to the firmware filesystem (instead of romfs), and do so appropriately.

HowTo build a firmware image (doesn't require compiling):

1.) edit the files in firmware_files/rootfs however you wish.
    These are the files the firmware image contains.
2.) run create_firmware_image.sh to build a firmware with today's date.

HowTo compile your own packages and/or kernel:

1.) Follow the instructios in Marvell/ReadMe.txt but put built files in the
    above mentioned directory instead of the 'filesystem' directory it
    mentions.
2.) The kernel can be replaced by storing the new zImage as 
    firmware_files/image_parts/segment1. Note that the size should be
    <= 0xA0000 bytes.

- jeremy collake <jeremy.collake@gmail.com>
