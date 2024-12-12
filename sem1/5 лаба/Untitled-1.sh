#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "Использование: \$0 <min_memory> <max_memory>"
    exit 1
fi

min_memory=\$1
max_memory=\$2

output_file="processes.txt"
> "$output_file" 

ps -eo pmem,comm --sort=comm | awk -v min="$min_memory" -v max="$max_memory" '\$1 >= min && \$1 <= max {print \$2}' | sort | uniq > "$output_file"

echo "Имена процессов с использованием памяти от $min_memory до $max_memory сохранены в $output_file."
