#!\bin\bash

if [ -z "$1" ]
then
echo "Не указан путь к каталогу"
exit
fi

if [ ! -d "$1" ]
then
echo "Данной папки нет"
exit
fi

if [ -z "$2" ]
then
echo "Не указан путь к новому файлу для записи"
exit
fi

direct="$1"
output_file="$2"

temp_file=$(mktemp)

find "$direct" -type f -exec stat --format="%n %s" {} \; | while read name size
do
base_name=$(basename "$name")
echo "$base_name $size"
done > "$temp_file"

if [ ! -s "$temp_file" ]
then
echo "Каталог пустой"
exit
fi

sort -nr -k2 "$temp_file" > "$output_file"

rm "$temp_file"

exit