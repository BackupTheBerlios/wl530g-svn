#!/bin/sh
#
# called when PPP link goes down.
#
echo "$0: started" | logger -s -p 6 -t '' &
if [ -f "/jffs/etc/on_ppp_down.sh" ]; then
	/jffs/etc/on_ppp_down.sh &
fi
echo "$0: finished" | logger -s -p 6 -t '' &
