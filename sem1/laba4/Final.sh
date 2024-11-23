#!/bin/bash


folder="$1"


if [ ! -d "$folder" ]; then
    echo "Данной папки нет"
    exit 1
fi


find "$folder" -type f -name "*.txt" | while read -r file; do
    n=$(wc -w < "$file")  
    dir=$(dirname "$file")
    base=$(basename "$file")

    mv "$file" "$dir/${n}_$base"
done

exit 0
