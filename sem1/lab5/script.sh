#!/bin/bash

path=$1
daynow=$(date +%d)


if test -f $path; then

	numsymb=$(wc -m $path | grep -o '[0-9]*')
	numword=$(wc -w $path | grep -o '[0-9]*')
	echo $path
	expr $(($numsymb*$daynow*$numword)) >> result.txt

else

    echo $1 does not exist or file

fi
