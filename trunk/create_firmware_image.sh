#!/bin/sh
#
# This script builds a firmware image.
#
#############################################################

#############################################################
# stupid - export is more appropriate, but I have my reasons
rmsvn()
{
	for i in $(find $1 | grep .svn); do
		rm -rf $i
	done
}

#############################################################
current_date=$(date +%m%d%y)
OUTPUT_FILE=wl530g_db90h_"$current_date"_en.bin
echo " Final output image will be $OUTPUT_FILE"
echo " Log for $OUTPUT_FILE" > build.log
#
# export/prepare the filesystem
#
echo " Exporting filesystem ..."
rm -rf build_temp
#svn export firmware_files/ build_temp/
mkdir build_temp
cp -r firmware_files/* build_temp
rmsvn build_temp/
echo " Extracting devfs ..."
cd build_temp
tar -xzvf dev.tar.gz -C rootfs/ 2>&1 >> ../build.log
cd ..
#
# embed revision number and date
#
./embed_rev.sh build_temp/rootfs/etc/banner build_temp/rootfs/www/index.asp
./embed_date.sh build_temp/rootfs/etc/banner build_temp/rootfs/www/index.asp
#
# build the firmware image
#
echo " Building firmware image.."
cd firmware-mod-kit
./build_firmware.sh ../firmware_images/temp ../build_temp
cd ..
if [ -f "firmware_images/$OUTPUT_FILE" ]; then
	echo " WARNING: over-writing old $OUTPUT_FILE"
	rm "firmware_images/$OUTPUT_FILE"
fi
#
# delete devices
#
rm -rf firmware_files/rootfs/dev
mv firmware_images/temp/custom_image-wl530g.trx firmware_images/$OUTPUT_FILE
rm firmware_images/latest_db90h_firmware_image.bin
cd firmware_images
ln -s $OUTPUT_FILE latest_db90h_firmware_image.bin
cd ..
rm -rf firmware_images/temp
rm -rf build_temp
