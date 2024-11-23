# Лабараторная работа №5
### Цель:
* Освоить командные оболочки shell (для OS семейства Unix) и cmd (для OS семейства MS Windows): изучить основные встроенные команды, научиться писать файлы сценариев, научиться соотносить командные оболочки для разных OS.
* Освоить командное окружение для OS семейства Unix(утилиты из пакета GNU Core Utilities), и соответствующие им утилиты для OS семейства MS Windows.
### Задание:
Вариант 44:

Создать файл sh и bat, который выполняет следующее: 

На вход пакетному файлу приходит относительный путь к папке (как параметр пакетного файла). Если такой папки нет, то писать “Данной папки нет” и завершить выполнение программы. Если такая папка есть, то в ней и ее подкаталогах переименовать все файлы, добавив перед исходным названием файла число слов в этом файле.
### Bat файл:
```
@echo off
Setlocal EnableDelayedExpansion
set "filename=%~1"

if exist "%~dp0!filename!" (
cd /d %~dp0!filename!
) else ( 
echo "You don't have this dir" 
exit /b
)

for /R %%i in (*) do (
set /a n=0
for /f "usebackq delims=" %%y in (%%i) do (
 for %%j in (%%y) do (
  set /a n+=1
 )
 
)
rename "%%i" "!n!_%%~ni%%~xi"
)
exit /b

```
### Sh файл:
```
#!/bin/bash

folder="$1"

if [ ! -d "$folder" ]; then
    echo "Данной папки нет"
    exit 1
fi

find "$folder" -type f -name "*.txt" | while read -r file; do
    n=$(wc -w < "$file")  
    dir=$(dirname "$file")
    base=$(basename "$file")

    mv "$file" "$dir/${n}_$base"
done

exit 0
```
