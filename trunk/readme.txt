
This buildroot is a total mess right now, mostly because the vendor firmware was a total mess. As things progress, it'll be cleaned up. For now, you're going to have to manually copy built target files to the firmware filesystem before and invoke ./create_firmware.sh. Not really that much trouble since for any given build most files won't change, but eventually it will all be automated.

jr has completed patches for uClinux 2.4.32, but I haven't integrated them in yet.

HowTo:

1.) extract latest firmware image with extract_firmware.sh
2.) go build whatever new packages you want, and/or kernel
3.) if desired, install built packages into extracted filesystem (working_dir/rootfs/).
4.) if desired, install new kernel into extracted filesystem (working_dir/image_parts/segment1)
5.) rebuild firmware image with ./create_firmware_image.sh or use the firmware mod kit.


- jeremy collake <jeremy.collake@gmail.com>
