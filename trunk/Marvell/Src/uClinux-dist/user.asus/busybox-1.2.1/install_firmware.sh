#!/bin/sh
echo "Installing to firmware filesystem ..."
echo "Deleting all existing files in bin/ ..."
rm ../../../../../firmware_files/rootfs/bin/*
echo "Installing busybox ..."
make install PREFIX=../../../../../firmware_files/rootfs/
