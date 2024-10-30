#!/bin/bash

fileName=$1

while read currentString; do
	fileText[$i]=$currentString
	i=$(($i+1))
done < $fileName

readarray -td '' sortedFile < <(printf '%s\0' "${fileText[@]}" | sort -z)

for i in ${!sortedFile[@]}; do
	if [[ $(($i%2)) -eq 0 ]]; then
		echo "${sortedFile[$i]}" >> oddStrings.txt;
	else
		echo "${sortedFile[$i]}" >> evenStrings.txt;
	fi
done
