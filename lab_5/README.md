# Лабораторная работа №5
# Цель: в рамках ЛР 5 необходимо создать исполняемый файл в соответствии с заданным вариантом. 

Вариант 42: Создать файл sh и bat, который выполняет следующее: 
На вход пакетному файлу приходит число (как параметр пакетного файла). В данном числе найти самую максимальную цифру, создать ровно столько файлов с расширением txt, у каждого второго поменять расширение на doc и записать туда сегодняшнюю дату.

Код для Windows:

```@echo off
setlocal enabledelayedexpansion

set num=%1
set max=0
for /L %%i in (0,1,9) do (
    echo %num% | findstr /C:"%%i" >nul && if %%i gtr !max! set max=%%i
)

set /a fileCount=0
for /L %%i in (1,1,!max!) do (
    set /a mod=%%i %% 2
    if !mod! equ 0 (
        echo %date% > "file%%i.doc"
    ) else (
        echo %date% > "file%%i.txt"
    )
    set /a fileCount+=1
)

echo Created !fileCount! files.
endlocal```

rsdf
