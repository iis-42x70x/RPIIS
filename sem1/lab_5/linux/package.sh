#!/bin/bash

number=$1
file_path=$2

rm $(date '+%d-%m-%Y').txt
touch $(date '+%d-%m-%Y').txt

while read -r line; do

    str_num=$(echo "$line" | awk '{print $1}')

    if [[ $str_num -ge $number ]]; then
        echo "$line" >> $(date '+%d-%m-%Y').txt
    fi

done < "$file_path"

echo "Done. Output file created: $(date '+%d-%m-%Y').txt"