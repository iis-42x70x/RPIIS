#!/bin/bash

# Проверяем, передан ли параметр N
if [ -z "$1" ]; then
    echo "Ошибка: Параметр N не передан. Использование: ./top_memory_processes.sh N"
    exit 1
fi

N=$1

# Проверяем, является ли N числом
if ! [[ "$N" =~ ^[0-9]+$ ]]; then
    echo "Ошибка: $N - не является числом."
    exit 1
fi

# Получаем текущую дату в формате ГГГГ-ММ-ДД
date=$(date +"%Y-%m-%d")

# Имя выходного файла
output_file="top_processes_$date.txt"

# Получаем список процессов через tasklist и выводим только PID и имя процесса
tasklist | tail -n +4 | sort -k 5 -n -r | head -n "$N" | awk '{print $2, $1}' > "$output_file"

# Сообщение об успешном выполнении
if [ -s "$output_file" ]; then
    echo "Топ $N процессов сохранен в файл $output_file."
else
    echo "Ошибка: не удалось создать файл $output_file или он пуст."
    exit 1
fi
