#!/bin/bash
if [ -z "$1" ]; then
    echo "Укажите размер файла в байтах как первый параметр!"
    exit 1
fi

if [ -z "$2" ]; then
    echo "Укажите второй параметр для записи в файл!"
    exit 1
fi

size=$1
content=$2
outputDir="$HOME/Study/Pivo"

if [ ! -d "$outputDir" ]; then
    mkdir -p "$outputDir"
fi

outputFile="$outputDir/myfile.txt"
truncate -s "$size" "$outputFile"

echo "$content" > "$outputFile"

fileTime=$(stat --format='%y' "$outputFile")
hour=$(date -d "$fileTime" +%H)
minute=$(date -d "$fileTime" +%M)

diff=$((minute - hour))
if [ $diff -lt 0 ]; then
    diff=$(( -diff ))
fi

charCount=$(wc -c < "$outputFile")
if [ "$charCount" -gt 0 ]; then
    charCount=$((charCount - 1))
fi

totalFolders=$((charCount * diff))

currentPath="$outputDir"
for ((i = 1; i <= totalFolders; i++)); do
    currentPath="$currentPath/folder$i"
    mkdir -p "$currentPath"
    touch "$currentPath/${hour}_${minute}.txt"
    echo "Создана папка: $currentPath"
done

echo "Готово!"
