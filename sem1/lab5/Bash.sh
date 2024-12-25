#!/bin/bash

# Проверка количества параметров
If [ «$#» -ne 4 ]; then
    Echo «Использование: $0 <каталог> <min_size> <max_size> <владелец>»
    Exit 1
Fi

Dir=»$1»
Min_size=»$2»
Max_size=»$3»
Owner=»$4»

# Проверка существования каталога
If [ ! -d «$dir» ]; then
    Echo «Данной папки нет»
    Exit 1
Fi

# Поиск файлов и вывод результатов
Find «$dir» -type f -size +$min_sizec -size -$max_sizec -user «$owner» -exec ls -ld {} \; > results.txt
Total_files=$(find «$dir» -type f | wc -l)
Echo «Общее число просмотренных файлов: $total_files» >> results.txt

