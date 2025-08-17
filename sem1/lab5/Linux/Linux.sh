#!/bin/bash

# Подсчет суммарного объема памяти и числа активных процессов
total_memory=$(ps -eo rss | awk '{sum+=$1} END {print sum}')
process_count=$(ps -e | wc -l)

# Сохранение результатов в файл
output_file="system_memory_usage.txt"
echo "Суммарный объем памяти (в KB): $total_memory" > "$output_file"
echo "Число активных процессов: $process_count" >> "$output_file"

echo "Результаты сохранены в файл $output_file"
