#!/bin/sh
rm ../../../../../firmware_files/rootfs/bin/$1
cp $1 ../../../../../firmware_files/rootfs/bin/$1
chmod +x ../../../../../firmware_files/rootfs/bin/$1
