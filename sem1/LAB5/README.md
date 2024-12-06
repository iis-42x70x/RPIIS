# Лабораторная работа №5
### Цель: 
 
Освоить командные оболочки shell (для OS семейства Unix) и cmd (для OS семейства MS Windows):
+ изучить основные встроенные команды,
+ научиться писать файлы сценариев,
+ научиться соотносить командные оболочки для разных OS.
+ Освоить командное окружение для OS семейства Unix(утилиты из пакета GNU Core Utilities), и соответствующие им утилиты для OS семейства MS Windows.
### Условия задания
Вариант 53. Создать файл sh и bat, который выполняет следующее: 
На вход пакетному файлу приходит относительный путь к папке (как параметр пакетного файла). Если такой папки нет, то писать “Данной папки нет” и завершить выполнение программы. Если такая папка есть, то в ней и в ее подкаталогах находить все пакетные файлы (файлы sh или bat) и запускаем их в алфавитном порядке (по названию файла). Каждый из скриптов внутри может возвращать какое-то рандомное значение. Вывести все эти рандомные значения по убыванию в файл result.txt.



## Bash файл
- ### Код программы :computer:
```bash
#!/bin/bash

if [ -z "$1" ]; then
    echo "Usage: $0 <folder_path>"
    exit 1
fi
folder="$1"
if [ ! -d "$folder" ]; then
    echo "There is no such folder"
    exit 1
fi

scripts=$(find "$folder" -type f -name "*.sh" | sort)
random_values=""

for script in $scripts; do
    random_value=$(bash "$script")
    echo $random_value
    if echo "$random_value" | grep -q '^[0-9]\+$'; then
        random_values="$random_values$random_value"'\n'
    fi
done

if [ -z "$random_values" ]; then
    echo "No valid random values found."
    exit 1
fi

echo "$random_values" | sort -nr > result.txt
echo "Results have been written to result.txt"
```
## Вспомогательный Bash файл
- ### Код программы :computer:
```bash
#!/bin/bash
echo $((RANDOM % 100 + 1))
```

## Batch файл
- ### Код программы :computer:
```batch
@echo off
setlocal enabledelayedexpansion

if "%~1"=="" (
    echo Please provide a folder path.
    exit /b
)

set "folder=%~1"

if not exist "!folder!" (
    echo There is no such folder.
    exit /b
)
do
set "tempfile=%temp%\batfiles_results.txt"
echo. > "!tempfile!"

for /r "!folder!" %%f in (*.bat) do (
    echo Reading file: %%f
    for /f "delims=" %%v in ('type "%%f"') do (
        echo %%v >> "!tempfile!"
    )
)

sort /r "!tempfile!" >> result.txt
del "!tempfile!"
echo Random values written to result.txt.
exit /b
```
## Вспомогательный Batch файл
- ### Код программы :computer:
```batch
@echo off
set /a "rand=%random% * 1000 / 32768 + 1"
echo %rand%
```
### Выводы: 
 В ходе выполнения лабораторной работы по освоению командных оболочек cmd (для операционных систем семейства MS Windows) и shell (для операционных систем семейства Unix) были получены практические навыки работы с консольными программами и командами в различных операционных системах. 
