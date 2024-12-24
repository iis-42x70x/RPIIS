#!/bin/bash

read -p "Введите название папки для поиска: " folder_name

SEARCH_PATH="/mnt/windows"

if [ -z "$folder_name" ]; then
    echo "Имя папки не указано. Попробуйте снова."
    exit 1
fi

folder_path=$(find "$SEARCH_PATH" -type d -iname "$folder_name" 2>/dev/null | head -n 1)

if [ -n "$folder_path" ]; then
    echo "Папка с названием '$folder_name' найдена."
    echo "Поиск .txt файлов..."

    > result.txt

    find "$folder_path" -type f -name "*.txt" 2>/dev/null | while read -r file; do
        if [ -f "$file" ]; then
            found_words=$(grep -E -o '\b[Vv][a-zA-Z]*\b' "$file" | sort | uniq)

            if [ -n "$found_words" ]; then
                echo "Файл: $file" >> result.txt
                echo "$found_words" >> result.txt
            else
                echo "Нет слов, начинающихся на 'v' или 'V' в файле $file." >> result.txt
            fi
        else
            echo "Файл $file не найден или нет доступа к нему." >> result.txt
        fi
    done

    echo "Результаты записаны в файл result.txt."
else
    echo "Папка с названием '$folder_name' не найдена."
fi
