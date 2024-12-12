#!/bin/bash

# Проверка на количество аргументов
if [ "$#" -ne 2 ]; then
    echo "Использование: \$0 <min_memory> <max_memory>"
    exit 1
fi

min_memory=\$1
max_memory=\$2

# Создание файла для записи имен процессов
output_file="processes.txt"

# Получение списка процессов, фильтрация по размеру памяти и сортировка
ps -eo pid,comm,%mem --sort=%mem | awk -v min="$min_memory" -v max="$max_memory" '\$3 >= min && \$3 <= max {print \$2}' | sort -u > "$output_file"

echo "Имена процессов, использующих память от $min_memory до $max_memory, записаны в $output_file."
