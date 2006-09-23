#!/bin/sh
#
# called when PPP link is established.
#
echo "$0: started" | logger -s -p 6 -t '' &
if [ -f "/jffs/etc/on_ppp_up.sh" ]; then
	/jffs/etc/on_ppp_up.sh
fi
echo "$0: finished" | logger -s -p 6 -t '' &
