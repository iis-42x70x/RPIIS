#!/bin/bash
directory=$1
min_size=$2
max_size=$3 
name=$4
file_result="scriptt.txt"
> $file_result
if [ ! -d "$directory" ]; then
echo "this name of directory is not in this computer"
exit 1
fi
counter=0
for file in $(find "$directory" -type f); do
file_size=$(stat -c%s "$file")
file_name=$(stat -c '%U' "$file")
if [ "$file_size" -ge "$min_size" ] && [ "$file_size" -le "$max_size" ] && [ "$file_name" == "$name" ]; then
echo "$file, $file_size" >>"$file_result"
counter=$((counter+1))
fi
done	
echo $counter


