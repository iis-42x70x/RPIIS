#!/bin/bash
if [ "$#" -ne 2 ]; then
    echo "Необходимы два аргумента: путь к первой и второй папке."    exit 1
fi
iz="$1"
v="$2"

if [ ! -d "$iz" ]; then    
   echo "Данной папки нет - $iz"
   exit 1 
fi
if [ ! -d "$v" ]; then
    echo "Данной папки нет - $v"   
    exit 1
fi

if [ -f "$file" ]; then        
    if [[ "$file" == *.txt ]]; then
           echo "Перемещение файла $(basename "$file") в $v"            
           mv "$file" "$v"
        else            
          echo "Устанавливаем атрибут 'только чтение' для файла $(basename "$file")"
          chmod 444 "$file"        
fi
fi 
done
echo "Выполнение завершено."
