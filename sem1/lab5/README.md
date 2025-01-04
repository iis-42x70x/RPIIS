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

# Проверяем, был ли передан аргумент
if [ -z "$1" ]; then
    echo "Please provide a folder path."
    exit 1
fi

# Сохраняем путь к папке
folder="$1"

# Проверяем, существует ли папка
if [ ! -d "$folder" ]; then
    echo "There is no such folder."
    exit 1
fi

# Ищем самый маленький файл
smallest_file=""
smallest_size=""

while IFS= read -r -d '' file; do
    current_size=$(stat -c%s "$file")
    if [ -z "$smallest_file" ] || [ "$current_size" -lt "$smallest_size" ]; then
        smallest_file="$file"
        smallest_size="$current_size"
    fi
done < <(find "$folder" -type f -name "*.txt" -print0)

# Проверяем, был ли найден файл
if [ -z "$smallest_file" ]; then
    echo "No txt files found in the folder."
    exit 1
fi

# Читаем и записываем содержимое файла с правильной кодировкой
cat "$smallest_file" > result.txt
echo "The content of the smallest file has been written to result.txt."
```

## Batch файл
- ### Код
```batch
@echo off

:: Проверяем, был ли передан аргумент
if "%~1"=="" (
    echo Please provide a folder path.
    exit /b
)

:: Сохраняем путь к папке
set "folder=%~1"

:: Проверяем, существует ли папка
if not exist "%folder%" (
    echo There is no such folder.
    exit /b
)

:: Ищем самый маленький файл
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

:: Проверяем, был ли найден файл
if not defined smallest_file (
    echo No txt files found in the folder.
    exit /b
)

:: Читаем и записываем содержимое файла с правильной кодировкой
powershell -Command "Get-Content -LiteralPath '%smallest_file%' -Encoding UTF8 | Out-File -FilePath 'result.txt' -Encoding UTF8"
echo The content of the smallest file has been written to result.txt.

```
### Выводы: 
 В ходе выполнения лабораторной работы по освоению командных оболочек cmd (для операционных систем семейства MS Windows) и shell (для операционных систем семейства Unix) были получены практические навыки работы с консольными программами и командами в различных операционных системах. 
