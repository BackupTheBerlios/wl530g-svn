#!/bin/sh
echo "$0: started" | logger -s -p 6 -t '' &
/jffs/etc/on_wan_up_begin.sh
echo "$0: finished" | logger -s -p 6 -t '' &
