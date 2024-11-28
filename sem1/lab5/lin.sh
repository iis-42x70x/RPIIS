export LANG=ru_RU.UTF-8 
read -p "Введите числовое значение для N (интервал в секундах): " N 
read -p "Введите числовое значение для M (максимальное время работы в секундах): " M 
total_time=0 
counter=1 
current_path="$(pwd)/folder_$counter" 
mkdir -p "$current_path" 
sleep "$N" 
((total_time+=N)) 
while ((total_time < M)); do 
    file_path="$current_path/$counter.txt"  
    echo "Общее время работы скрипта: $total_time секунд" > "$file_path" 
    echo "Новый файл $counter был создан" 
    ((counter++)) 
    current_path="$current_path/folder_$counter" 
    mkdir -p "$current_path" 
    ((total_time+=N)) 
    sleep "$N" 
done 
total_folders=$((counter - 1)) 
echo "Скрипт завершил работу. Общее количество созданных папок: $total_folders"


