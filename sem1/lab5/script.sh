#!/bin/sh

# Проверяем, переданы ли все необходимые параметры 
if [ "$#" -ne 3 ]; then
echo "Недостаточно параметров"
exit 1
fi

# Чтение аргументов 
keywords_file="$1"
directory="$2"
numb="$3"

# Проверяем, существует ли указанный файл с ключевыми словами
if [ ! -f "$keywords_file" ]; then
echo "Файл '$keywords_file' не найден!"
exit 1
fi

# Проверяем, существует ли указанная директория
if [ ! -d "$directory" ]; then
echo "Директория '$directory' не найдена!"
exit 1
fi

# Получаем имя директории без пути
base_dir_name=$(basename "$directory")

# Создаем подпапку с именем <имя_папки>_search
search_directory="${directory}/${base_dir_name}_search"
mkdir -p "$search_directory"

# Чтение ключевых слов из файла
keywords=$(cat "$keywords_file")

# Цикл по всем текстовым файлам в указанной директории
for file in "$directory"/*.txt; do
if [ -f "$file" ]; then
# Подсчет количества ключевых слов
count=0
for keyword in $keywords; do
count=$(($count + $(grep -o -i -w "$keyword" "$file" | wc -l)))
done

# Если количество ключевых слов больше или равно порогу, копируем файл
if [ "$count" -ge "$numb" ]; then
cp "$file" "$search_directory/"
echo "Копируем '$file' в '$search_directory/' (найдено $count ключевых слов)"
fi
fi
done

echo "Поиск завершен."
