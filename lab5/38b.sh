#!/bin/bash 

# проверяем подкл папки
if [ -z "$1" ]; then
    echo "Please specify the target directory."
    exit 1
fi
# сохр путь в переменну таргет
TARGET_DIR="$1"


# ps 
ps aux | tail -n +2 | while read user pid cpu mem time tty status command; do
    #  извлекает имя команды из полного пути
    process_name=$(basename "$command")
    
  
    # создание подпапок
    process_dir="$TARGET_DIR/$process_name"
    mkdir -p "$process_dir"
    
    # создание файлов 
    file_path="$process_dir/$pid.txt" 
#если файл сущ
    if [ ! -f "$file_path" ]; then 
        # пишем память
        echo "$mem KB" > "$file_path"
    fi
done