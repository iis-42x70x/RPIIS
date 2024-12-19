#!/bin/bash

if [ ! -d "$1" ]; then
  echo "Данной папки нет"
  exit 1
fi

count=0
find "$1" -name "*.$2" -type f -print0 | while IFS= read -r -d $'\0' file; do
  if [ -f "$file" ] && [ $(stat -c %A "$file") == *H* ]; then
    count=$((count + 1))
  fi
done

echo "Найдено скрытых файлов с расширением $2: $count"
