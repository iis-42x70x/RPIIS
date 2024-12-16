# Создание вложенных папок и файлов

## Описание задачи
На вход скрипту передаётся число (как параметр). Необходимо:
1. Создать текстовый файл заданного размера (в байтах).
2. Создать иерархию вложенных папок. Количество папок определяется как произведение:
   - Количества символов в созданном файле.
   - Разности (по модулю) между минутами и часами времени создания файла.
3. В каждой папке создать файл с именем, соответствующим времени создания основного файла в формате HH_MM.

## Batch-файл

```batch
@echo off
chcp 65001
setlocal enabledelayedexpansion

set size=%1
set content=%2

if "%size%"=="" (
    echo Укажите размер файла в байтах как первый параметр!
    exit /b
)
if "%content%"=="" (
    echo Укажите второй параметр для записи в файл!
    exit /b
)

set outputDir=D:\Study\Pivo

fsutil file createnew "%outputDir%\myfile.txt" %size%
echo %content% > "%outputDir%\myfile.txt"

REM Получаем время создания файла
for /f "tokens=1-5 delims=/: " %%a in ('dir /T:C "%outputDir%\myfile.txt" ^| findstr myfile.txt') do (
    set hour=%%c
    set minute=%%b 
)

REM Вычисляем разницу между минутами и часами
set /a diff=%minute%-%hour%
if %diff% lss 0 (
    set /a diff=-%diff%
)

REM Подсчитываем количество символов в файле
set /a charCount=0
for /F "usebackq delims=" %%i in ("%outputDir%\myfile.txt") do (
    set string=%%i
    :loop
    if not "!string!"=="" (
        set /a charCount+=1
        set string=!string:~0,-1!
        goto loop
    )
)

REM Уменьшаем charCount на 1, так как последний символ был удалён
set /a charCount-=1

REM Вычисляем количество папок для создания
set /a totalFolders=!charCount! * !diff!

REM Создаем вложенные папки
set currentPath=%outputDir%
for /l %%i in (1,1,!totalFolders!) do (
    set currentPath=!currentPath!\folder%%i
    if not exist "!currentPath!" (
        mkdir "!currentPath!"
        echo Создана папка: !currentPath!
    )
    echo. > "!currentPath!\%hour%_%minute%.txt"
)

echo Готово!
## Shell-файл
```bash
#!/bin/bash

# Проверка параметров
if [ -z "$1" ]; then
    echo "Укажите размер файла в байтах как первый параметр!"
    exit 1
fi

if [ -z "$2" ]; then
    echo "Укажите второй параметр для записи в файл!"
    exit 1
fi

size=$1
content=$2
outputDir="$HOME/Study/Pivo"

# Создание выходной директории
if [ ! -d "$outputDir" ]; then
    mkdir -p "$outputDir"
fi

# Создание файла заданного размера
outputFile="$outputDir/myfile.txt"
truncate -s "$size" "$outputFile"

# Запись содержимого в файл
echo "$content" > "$outputFile"

# Получение времени создания файла
fileTime=$(stat --format='%y' "$outputFile")
hour=$(date -d "$fileTime" +%H)
minute=$(date -d "$fileTime" +%M)

# Расчёт разницы между минутами и часами по модулю
diff=$((minute - hour))
if [ $diff -lt 0 ]; then
    diff=$(( -diff ))
fi

# Подсчёт количества символов в файле
charCount=$(wc -c < "$outputFile")
if [ "$charCount" -gt 0 ]; then
    charCount=$((charCount - 1)) # Учитываем лишний символ новой строки
fi

# Расчёт общего количества папок
totalFolders=$((charCount * diff))

# Создание вложенных папок и файлов
currentPath="$outputDir"
for ((i = 1; i <= totalFolders; i++)); do
    currentPath="$currentPath/folder$i"
    mkdir -p "$currentPath"
    touch "$currentPath/${hour}_${minute}.txt"
    echo "Создана папка: $currentPath"
done

echo "Готово!"