#!/bin/bash
if [ $# -ne 1 ]; then
    echo "Неверное количество аргументов! Укажите размер файла в байтах."
    exit 1
fi
file_size=$1
dd if=text_template.txt of=generated_file.txt bs=1 count=$file_size
minutes=$(stat -f "%SB" generated_file.txt|cut -d ":" -f 2)
hours=$(stat -f "%SB" generated_file.txt|cut -d " " -f 3|cut -d ":" -f 1)
if [ "$hours" -lt "$minutes" ]; then
    mod_value_h_m=$((10#$minutes - 10#$hours))
else
    mod_value_h_m=$((10#$hours - 10#$minutes))
fi
number_of_directories=$((mod_value_h_m*file_size))
for ((i=1;i<=number_of_directories;i++))
do
	path_dir="./$i"
	mkdir -p "$path_dir"
	cd "./$i"
	touch "$hours"_"$minutes.txt"
done
echo "Гатово"
