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

# Проверяем, что передан путь к папке
if [ -z "$1" ]; then
    echo "Ошибка: Не указан путь к папке."
    exit 1
fi

DIRECTORY=$1

# Проверяем, существует ли папка
if [ ! -d "$DIRECTORY" ]; then
    echo "Ошибка: Указанная папка не существует."
    exit 1
fi

# Ищем самый маленький txt файл в папке
SMALLEST_FILE=$(find "$DIRECTORY" -type f -name "*.txt" -printf "%s %p\n" | sort -n | head -n 1 | awk '{print $2}')

# Проверяем, найден ли файл
if [ -z "$SMALLEST_FILE" ]; then
    echo "Ошибка: В папке нет txt файлов."
    exit 1
fi

# Создаём result.txt и записываем содержимое найденного файла в обратном порядке
if [ -f "result.txt" ]; then
    rm result.txt
fi
tac "$SMALLEST_FILE" > result.txt

echo "Результат записан в result.txt."
```
## Вспомогательный Bash файл
- ### Код
```bash
#!/bin/bash
echo $((RANDOM % 100 + 1))
```

## Batch файл
- ### Код
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
- ### Код
```batch
@echo off
set /a "rand=%random% * 1000 / 32768 + 1"
echo %rand%
```
### Выводы: 
 В ходе выполнения лабораторной работы по освоению командных оболочек cmd (для операционных систем семейства MS Windows) и shell (для операционных систем семейства Unix) были получены практические навыки работы с консольными программами и командами в различных операционных системах. 
