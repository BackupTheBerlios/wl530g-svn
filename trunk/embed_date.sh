#!/bin/sh
#
# this script embeds the date in document(s) given on command line
# document should have __CURRENT_DATE__ where it wants the revision number
# to be placed. Wildcards okay.
#
if [ $# -lt 1 ]; then
	echo " Invalid usage. Must supply one or more files."
	exit 1
fi
current_date=$(date +%m%d%y)
tempfile=$(mktemp)
echo " Date is $current_date"
echo " Temporary file is $tempfile"
# todo: update to unlimited args
for curfile in $1 $2 $3 $4 $5 $6 $7 $8 $9; do
	echo " Processing $curfile ..."
	cp $curfile $tempfile	
	cat $tempfile | sed s/__CURRENT_DATE__/$current_date/ > $curfile
	rm $tempfile	
done
