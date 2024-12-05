#!/bin/bash
 
if [ -z "$1" ]; then
    echo "Укажите путь к каталогу"
    exit 1
fi
 
TARGET_DIR="$1"
mkdir -p "$TARGET_DIR"
 
ps -eo comm,pid,rss --no-headers | while read -r name pid rss; do
    name=$(echo "$name" | tr -d ' ')
 
    process_dir="$TARGET_DIR/$name"
    mkdir -p "$process_dir"

    echo "$rss" > "$process_dir/$pid"
done
