#!/bin/bash
if [ "$#" -lt 1 ]; then
echo "The path to storage is missed. Try $0 path"
exit 1
fi
folder_path="$1"
if [ -d "$folder_path" ]; then
filecount=$(find "$folder_path" -type f | wc -l)
echo "Directory exists, $filecount files"
current_date=$(date +%Y%m%d)
maxdate=$(echo "$current_date" | grep -o . | sort -nr | head -n 1)
result=$((filecount * maxdate))
echo "$maxdate - max date, result = $result"
forresult="${folder_path}/${filecount}.txt"
echo "$result" > "$forresult"
else
echo "That directory is missed"
exit 1
fi