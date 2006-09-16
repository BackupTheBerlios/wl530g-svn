#!/bin/sh
#
# This script builds a new firmware image.
#
current_date=$(date +%m%d%y)
OUTPUT_FILE=wl530g_db90h_"$current_date"_en.bin
echo " Final output image will be $OUTPUT_FILE"
echo " Log for $OUTPUT_FILE" > build.log
echo " Extracting devices.."
cd firmware_files
tar -xzvf dev.tar.gz -C rootfs/ 2>&1 >> ../build.log
cd ..
echo " Building firmware image.."
cd firmware-mod-kit
./build_firmware.sh ../firmware_images/temp ../firmware_files
cd ..
if [ -f "firmware_images/$OUTPUT_FILE" ]; then
	echo " WARNING: over-writing old $OUTPUT_FILE"
	rm "firmware_images/$OUTPUT_FILE"
fi
# delete devices again..
rm -rf firmware_files/rootfs/dev
mv firmware_images/temp/custom_image-wl530g.trx firmware_images/$OUTPUT_FILE
rm firmware_images/latest_db90h_firmware_image.bin
cd firmware_images
ln -s $OUTPUT_FILE latest_db90h_firmware_image.bin
cd ..
rm -rf firmware_images/temp
