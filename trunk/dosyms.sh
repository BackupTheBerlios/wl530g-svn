#!/bin/sh
# stupid script to set up some symlinks 
cd firmware_files/rootfs/bin
rm -f pppd pptp_callmgr pppoe pppoe-relay bpalogin
ln -s ../sbin/pppd pppd
ln -s ../sbin/pptp_callmgr pptp_callmgr
ln -s ../sbin/pppoe pppoe
ln -s ../sbin/pppoe-relay pppoe-relay
ln -s ../sbin/bpalogin bpalogin
cd ../../..
