#!/bin/bash

if [ -z "$1" ]; then
    echo "Folder path is not specified."
    exit 1
fi

if [ ! -d "$1" ]; then
    echo "The folder does not exist."
    exit 1
fi

uniqueChars=""

while IFS= read -r -d '' file; do
    filename="$(basename "$file" .doc)"
    for (( i=0; i<${#filename}; i++ )); do
        char="${filename:i:1}"
        if [[ "$uniqueChars" != *"$char"* ]]; then
            uniqueChars+="$char"
        fi
    done
done < <(find "$1" -type f -name "*.doc" -print0)

outputFile="$(pwd)/result.txt"
echo "Number of unique characters:" > "$outputFile"
echo "$uniqueChars" >> "$outputFile"
echo "Total unique characters count: ${#uniqueChars}" >> "$outputFile"

echo "Done. The result is saved in $outputFile."

