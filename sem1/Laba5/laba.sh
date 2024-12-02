#!/bin/bash

# Получаем текущую дату в формате
today=$(date +%d.%m.%Y)
# Считаем активные процессы в ОС
total=$(ps -e --no-header | wc -l)
result="${today}_${total}"
# Записываем результат в файл result.txt
echo "$result" > result.txt
echo "Результат записан в файл result.txt: $result"
