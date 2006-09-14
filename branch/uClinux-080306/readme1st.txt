# Download and install arm cross-compiler
  mkdir -p /src/wl530g
  cd /src/wl530g
  wget http://ftp.snapgear.org/pub/snapgear/tools/arm-elf/arm-elf-tools-20030314.sh
  sh ./arm-elf-tools-20030314.sh
  # this fails on newer linux distros, use dd to extract tar.gz and extract it to /

# Download uClinux-dist-20060803.tar.gz
  cd /src/wl530g
  wget http://80.81.183.101/uclinux/uClinux-dist-20060803.tar.gz

# We only want kernel
  tar xzf uClinux-dist-20060803.tar.gz uClinux-dist/linux-2.4.x
  mv uClinux-dist/linux-2.4.x linux-2.4.32-uc0-wl530g
  rmdir uClinux-dist

# Apply last 2.4 compatible linux-mtd cvs snapshot (March 1st 2005)
  wget http://80.81.183.101/wl530g/mtd-snapshot-20050301.tar.bz2
  tar xjf mtd-snapshot-20050301.tar.bz2
  cd mtd_March_1_2005/patches
  sh ./patchin.sh -c -j -y /src/wl530g/linux-2.4.32-uc0-wl530g
  cd ../..

# Apply Asus WL-530G support patch (Marvell Firefox/Libertas ARM946)
  wget http://80.81.183.101/wl530g/linux-2.4.32-uc0-wl530g.patch
  cd linux-2.4.32-uc0-wl530g
  patch -p1 <../linux-2.4.32-uc0-wl530g.patch

# Compile kernel
  ARCH=armnommu CROSS_COMPILE=arm-elf- make oldconfig
  ARCH=armnommu CROSS_COMPILE=arm-elf- make dep
  ARCH=armnommu CROSS_COMPILE=arm-elf- make bzImage

# New kernel is saved as arch/armnommu/boot/zImage

