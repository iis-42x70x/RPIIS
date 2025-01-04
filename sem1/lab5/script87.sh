#проверяем, что передан абсолютный путь к папке
# -z является ли строка пустой, $1 первый агрумент 
if [ ! -d "$1" ]; then
    echo "Данной папки нет"
    exit 1
fi


countFiles=0
for file in "$1"/*; do
    [ -e "$file" ] && countFiles=$((countFiles + 1))    
done


countProcesses=0
for process in $(ps -e | awk '{print $1}' | tail -n +2); do
    countProcesses=$((countProcesses + 1)) # Увеличиваем счетчик для каждого процесса
done

echo "Количество файлов: $countFiles"
echo "Количество процессов: $countProcesses"

# Запись результата в файл с текущим временем
file="$(date +%S_%M_%H).txt"
{
    echo "Результат: $((countFiles * countProcesses))"
} > "$file"

echo "Результат записан в файл \"$file\""