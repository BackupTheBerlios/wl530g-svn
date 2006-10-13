#!/bin/sh
#
# prepare uClinux 2.4.32 for Marvell Liberatas board.
# a simple collection of jr--'s instructions and patches.
# requires axel to download from uClinux.org's perpetually near dead server.
#
if [ -f uClinux-dist-20060803.tar.bz2 ]; then
	tar xjf uClinux-dist-20060803.tar.bz2 uClinux-dist/linux-2.4.x 
elif [ -f uClinux-dist-20060803.tar.gz ]; then
	tar xzf uClinux-dist-20060803.tar.gz uClinux-dist/linux-2.4.x 
fi
if [ "$?" != "0" ]; then
	echo "Failure."
	exit 1
fi
rmdir -rf linux-2.4.32-uc0-wl530g
mv uClinux-dist/linux-2.4.x linux-2.4.32-uc0-wl530g
rmdir uClinux-dist
tar xjf mtd-snapshot-20050301.tar.bz2
if [ "$?" != "0" ]; then
	echo "Failure."
	exit 1
fi
srcbase=$(realpath "./linux-2.4.32-uc0-wl530g")
cd mtd_March_1_2005/patches
echo "srcbase is $srcbase"
sh ./patchin.sh -c -j -y "$srcbase/linux-2.4.x/"
cd ../..
cd linux-2.4.32-uc0-wl530g/linux-2.4.x
patch -p1 <../../linux-2.4.32-uc0-wl530g.patch
