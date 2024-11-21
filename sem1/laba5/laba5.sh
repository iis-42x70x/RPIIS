#!/bin/bash

dir1="$1"
dir2="$2"

for file in "$dir1"/*; do
    filename=$(basename "$file")
    if [[ ! -e "$dir2/$filename" ]]; then
        rm "$file"
        echo "Удаление $filename из $dir1"
    fi
done
for file in "$dir2"/*; do
    filename=$(basename "$file")
    if [[ ! -e "$dir1/$filename" ]]; then
        cp "$file" "$dir1/$filename"
        echo "Копирование $filename в $dir1"
    fi
done
echo "done"