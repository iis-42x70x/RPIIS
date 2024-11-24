#!/bin/bash

# Проверка на наличие аргумента
if [ -z "$1" ]; then
    echo "Не указан путь к папке"
    exit 1
fi

# Абсолютный путь к папке передан как первый аргумент
DIR="$1"

# Проверка существования папки
if [ ! -d "$DIR" ]; then
    echo "Данной папки нет"
    exit 1
fi

tempFile=$(mktemp)

# Найти все .txt файлы и извлечь 5-ю строку каждого
find "$DIR" -type f -name "*.txt" | while IFS= read -r file; do
    # Извлекаем пятую строку файла (если она существует)
    line=$(sed -n '5p' "$file")
    if [ -n "$line" ]; then
        echo "$line" >> "$tempFile"
    fi
done

# Сортируем строки и записываем в log.txt
sort "$tempFile" > log.txt
rm "$tempFile"
echo "Результат записан в log.txt"