#!/bin/bash
if [ "$#" -ne 1 ]; then
    echo "Использование: $0 <абсолютный_путь_к_папке>"
    exit 1
fi

directory="$1"

if [ ! -d "$directory" ]; then
    echo "Данной папки нет"
    exit 1
fi

log_file="log1.txt"
> "$log_file"

find "$directory" -type f -name "*.txt" | while read -r file; do
    fifth_line=$(sed -n '5p' "$file")
    if [ ! -z "$fifth_line" ]; then
        echo "$fifth_line" >> "$log_file"
    fi
done

sort -u "$log_file" -o "$log_file"
