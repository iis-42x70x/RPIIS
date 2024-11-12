#!/bin/bash

# Проверяем, что юзер передал оба параметра
if [ -z "$1" ]; then
    echo "Ошибка: Не указан путь к папке."
    exit 1
fi

if [ -z "$2" ]; then
    echo "Ошибка: Не указан формат файла."
    exit 1
fi

# Сохраняем параметры
folder_path="$1"
file_format="$2"

# Ищем файлы с заданным форматом в указанной папке
file_count=$(find "$folder_path" -type f -name "*.$file_format" | wc -l)
echo "Количество файлов с форматом .$file_format в папке $folder_path: $file_count"

# Проверяем условие
if (($file_count % 2 == 0 )); then # число нужных файлов четное
    number_of_processes=$(ps -e --no-headers | wc -l) # число процессов
    echo "Число активных процессов - $number_of_processes"
else # число нужных файлов нечетное
    for (( i=7; i>=1; i-- ))
    do
        echo "Завершение программы через $i"
        sleep 1
    done
    echo "Программа завершена."
fi
exit 0
