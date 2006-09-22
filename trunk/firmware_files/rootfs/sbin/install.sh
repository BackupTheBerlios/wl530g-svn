#!/bin/sh
INSTALL_DIR="/jffs/bin"
if [ $# -lt 1 ]; then
	echo " This script installs packages from .tar.gz files."
	echo
	echo " USAGE: "
	echo "   $0 SOMEPACKAGEURL"
	echo "   Packages are installed to $INSTALL_DIR"
	echo
	exit 1
fi
packagename=`basename "$1"`
echo " Installing $packagename ..."
mkdir /jffs/bin 2>&1 >> /dev/null
wget $1 -P /tmp
if [ $? != 0 ]; then
	echo " Error retrieving $1."
	exit 1
fi
tar -xzf /tmp -C /jffs/bin
if [ $? != 0 ]; then
	echo " Error extracting $1."
	exit 1
fi
chmod +x /jffs/bin/$packagename
echo " Package installed!"
