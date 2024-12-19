# Лабораторная работа 5
 
### Цель: 
 
Освоить командные оболочки cmd и shell:
+ изучить основные встроенные команды,
+ научиться писать файлы сценариев,
+ научиться соотносить командные оболочки для разных OS.
+ Освоить командное окружение для OS семейства Unix(утилиты из пакета GNU Core Utilities), и соответствующие им утилиты для OS семейства MS Windows.
### Условия задания
Вариант 42: Создать файл sh и bat, который выполняет следующее: 
На вход пакетному файлу приходит число (как параметр пакетного файла). В данном числе найти самую максимальную цифру, создать ровно столько файлов с расширением txt, у каждого второго поменять расширение на doc и записать туда сегодняшнюю дату.
### Алгоритм решения
1) Получить на вход число;
2) Пройтись по каждой цифре и методом выборки найти наибольшую цифру;
3) Извлечь в переменную данные о сегодняшней дате;
4) Создать нужное нам количество файлов учитывая чередование doc и txt файлов;
## Batch файл
- ### Код программы
```batch
@echo off
setlocal enabledelayedexpansion
chcp 65001 
set /p "number=Введите число: "
set max_znach=%number:~0,1%

for /l %%i in (0,1,9) do (
    echo %number% | findstr /c:%%i >nul
    if !errorlevel! equ 0 (
        set max_znach=%%i
    )
)

echo Максимальная цифра: %max_znach%

for /f "tokens=2 delims==" %%i in ('wmic os get localdatetime /value') do set date=%%i
set today=!date:~0,4!-!date:~4,2!-!date:~6,2!

for /l %%j in (1,1,%max_znach%) do (
    set /a count=%%j
    set filename=file!count!
    set /a chetn=count %% 2
   
    if !chetn! equ 0 (
        echo Создан файл !filename!.doc
        echo !today! > !filename!.doc
    ) else (
        echo Создан файл !filename!.txt
        echo !today! > !filename!.txt
    )
)

endlocal
```
### Пример
![](bat.png)

## Bash файл
```bash
#!/bin/bash
export LANG=ru_RU.UTF-8

read -p "Введите число: " number

max_znach=${number:0:1}

for (( i=0; i<=9; i++ )); do
    if [[ $number == *"$i"* ]]; then
        max_znach=$i
    fi
done

echo "Максимальная цифра: $max_znach"

# Получаем текущую дату в формате ГГГГ-ММ-ДД
today=$(date +"%Y-%m-%d")

# Создание файлов
for (( j=1; j<=max_znach; j++ )); do
    filename="file$j"

    if (( j % 2 == 0 )); then
        echo "Создан файл $filename.doc"
        echo "$today" > "$filename.doc"
    else
        echo "Создан файл $filename.txt"
        echo "$today" > "$filename.txt"
    fi
done
```
### Пример
![](bash.png)
### Выводы: 
 В ходе выполнения лабораторной работы ,были обретены навыки работы с консольными программами и командами в таких ОС как Windows и Linux. 