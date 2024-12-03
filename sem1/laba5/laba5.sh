#!/bin/bash

read -p "Введите путь к каталогу (например, /mnt/c/temp): " directory
read -p "Введите минимальный PID: " min_pid
read -p "Введите максимальный PID: " max_pid

# Создание каталога, если его нет
if [ ! -d "$directory" ]; then
    mkdir -p "$directory" || { echo "Ошибка создания каталога $directory"; exit 1; }
fi

# Перебор каталогов в /proc
for pid in $(ls /proc | grep -E '^[0-9]+$'); do
    # Убедимся, что pid числовой
    if [[ "$pid" =~ ^[0-9]+$ ]]; then
        if (( pid >= min_pid && pid <= max_pid )); then
            if [ -d "/proc/$pid" ]; then
                # Попытка прочитать имя процесса
                if [ -f "/proc/$pid/comm" ]; then
                    process_name=$(cat /proc/$pid/comm)
                else
                    process_name="Неизвестно"
                fi
                
                # Получение пользователя
                user=$(stat -c '%U' /proc/$pid 2>/dev/null || echo "Неизвестно")

                # Создание файла
                file_path="$directory/$pid.txt"
                echo "Имя процесса: $process_name" > "$file_path"
                echo "Пользователь: $user" >> "$file_path"
            fi
        fi
    fi
done

echo "Скрипт завершён. Проверьте файлы в каталоге $directory."
