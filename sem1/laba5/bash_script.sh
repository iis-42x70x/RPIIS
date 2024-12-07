#!/bin/bash
folder="$1"

if [ -d "$folder" ]; then
  echo "Данной папки нет"
  exit 1
fi

txt_files=$(find "$folder" -type f -name "*.txt" -size -500k)
smallest_file=""
smallest_size=500000

for file in $txt_files; do
  file_size=$(stat -c "%s" "$file")
  if [ "$file_size" -lt "$smallest_size" ]; then
    smallest_file="$file"
    smallest_size="$file_size"
  fi
done

if [ -n "$smallest_file" ]; then
  echo "Удаляем файл: $smallest_file"
  rm "$smallest_file"
else
  echo "Не удалось найти подходящий файл для удаления."
fi
