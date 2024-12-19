# Лабораторная работа №5
### Цель: 
 
Освоить командные оболочки shell (для OS семейства Unix) и cmd (для OS семейства MS Windows):
+ изучить основные встроенные команды,
+ научиться писать файлы сценариев,
+ научиться соотносить командные оболочки для разных OS.
+ Освоить командное окружение для OS семейства Unix(утилиты из пакета GNU Core Utilities), и соответствующие им утилиты для OS семейства MS Windows.
### Условия задания
Вариант 78. Создать файл sh и bat, который выполняет следующее: 
На вход пакетному файлу приходит путь к папке (как параметр пакетного файла). В заданной папке найти самый маленький txt файл. Создать файл result.txt и вывести в него содержимое найденного файла в обратном порядке.




## Bash файл
- ### Код
```bash
#!/bin/bash

if [ -z "$1" ]; then
    echo "Usage: $0 <folder_path>"
    exit 1
fi

folder="$1"

if [ ! -d "$folder" ]; then
    echo "There is no such folder."
    exit 1
fi

smallest_file=$(find "$folder" -type f -name "*.txt" -exec ls -lS {} + | head -n 1 | awk '{print $NF}')

if [ -z "$smallest_file" ]; then
    echo "No txt files found in the folder."
    exit 1
fi

tac "$smallest_file" > result.txt
echo "The reversed content of the smallest file has been written to result.txt."
```

## Batch файл
- ### Код
```batch
@echo off

if "%~1"=="" (
    echo Please provide a folder path.
    exit /b
)

set "folder=%~1"

if not exist "%folder%" (
    echo There is no such folder.
    exit /b
)

set "smallest_file="
for /r "%folder%" %%f in (*.txt) do (
    if not defined smallest_file (
        set "smallest_file=%%f"
    ) else (
        for %%a in ("%%f") do for %%b in ("%smallest_file%") do (
            if %%~za lss %%~zb (
                set "smallest_file=%%f"
            )
        )
    )
)

if not defined smallest_file (
    echo No txt files found in the folder.
    exit /b
)

type "%smallest_file%" | more /e | findstr /v "^" > result.txt
echo The reversed content of the smallest file has been written to result.txt.
```
### Выводы: 
 В ходе выполнения лабораторной работы по освоению командных оболочек cmd (для операционных систем семейства MS Windows) и shell (для операционных систем семейства Unix) были получены практические навыки работы с консольными программами и командами в различных операционных системах. 
