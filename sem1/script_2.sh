#!/bin/bash

if [ -z "$1" ]; then
  echo "Не указан путь к папке"
  exit 1
fi

DIR="$1"

if [ ! -d "$DIR" ]; then
  echo "Данной папки нет"
  exit 1
fi

find "$DIR" -type f -name "*.txt" -exec grep -oE '\b[Vv][a-zA-Z]*\b' {} + > result.txt

echo "Результат записан в result.txt"
exit 0