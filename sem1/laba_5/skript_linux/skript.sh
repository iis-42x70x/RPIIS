#!/bin/bash

if [ -z "$1" ]
then
  echo "Вы не ввели параметр!"
  exit 
fi

rel_path="$1"
abs_path=$(realpath "$rel_path")

if [ ! -d "$abs_path" ]
then
  echo "Данной папки нет"
  exit 
fi

unsort_file="unsort.txt"
result_file="result_numbers.txt"

find "$abs_path" -type f -name "*.sh" | sort | while read -r file
do
  echo "Запускаем $file"
  random_number=$(bash "$file")
  echo "$random_number" >> "$unsort_file" 
done

echo "Случайные числа в порядке убывания : " > "$result_file"

sort -nr "$unsort_file" >> "$result_file"

echo "Результаты записаны в файл $result_file"

rm -f "$unsort_file"

exit