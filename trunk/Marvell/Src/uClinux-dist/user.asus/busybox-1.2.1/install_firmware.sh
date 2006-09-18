#!/bin/sh
echo "Installing to firmware filesystem ..."
echo "Deleting all existing files in bin/ ..."
rm ../../../../../firmware_files/rootfs/bin/*
echo "Installing busybox ..."
make install PREFIX=../../../../../firmware_files/rootfs/
cd ../../user/shutils
make
./installall.sh
cd ../fileutils
make
./installall.sh
cd ../../user.asus/busybox-1.2.1
