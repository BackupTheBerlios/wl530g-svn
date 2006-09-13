#!/bin/sh
#
# (c) 2006 Jeremy Collake <jeremy@bitsum.com>
# Released under GPL 2 license
#
# This script builds a new firmware image.
#
current_date=$(date +%m%d%y)
OUTPUT_FILE=wl530g_db90h_"$current_date"_en.bin
cd firmware-mod-kit
./build_firmware.sh ../firmware_images/temp ../firmware_files/db90h_edition/
cd ..
if [ -f "firmware_images/$OUTPUT_FILE" ]; then
	echo " WARNING: over-writing old $OUTPUT_FILE"
	rm "firmware_images/$OUTPUT_FILE"
fi
mv firmware_images/temp/custom_image-wl530g.trx firmware_images/$OUTPUT_FILE
rm firmware_images/latest_db90h_firmware_image.bin
ln -s firmware_images/$OUTPUT_FILE latest_db90h_firmware_image.bin
rm -rf firmware_images/temp
