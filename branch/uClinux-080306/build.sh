#!/bin/sh
rm -rf bin
mkdir bin
cd linux-2.4.32-uc0-wl530g
ARCH=armnommu CROSS_COMPILE=arm-elf- make oldconfig &&
ARCH=armnommu CROSS_COMPILE=arm-elf- make dep &&
ARCH=armnommu CROSS_COMPILE=arm-elf- make bzImage &&
cp arch/armnommu/boot/zImage ../bin/zImage
cd ..
