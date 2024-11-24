@echo off
setlocal enabledelayedexpansion
chcp 1251

rem Проверка на наличие аргумента
if "%~1"=="" (
    echo Не указан путь к папке
    exit /b 1
)

rem Абсолютный путь к папке передан как первый аргумент
set "DIR=%~1"

rem Проверка существования папки
if not exist "%DIR%" (
    echo Данной папки нет
    exit  1
)

if exist log.txt del log.txt
if exist "%tempFile%" del "%tempFile%"
set "tempFile=%DIR%\temp_log.txt"
rem Находим все .txt файлы и извлекаем 5-ю строку
for /r "%DIR%" %%f in (*.txt) do (
    set "lineCounter=0"
    set "line="

    rem Читаем строки из текущего файла и извлекаем 5-ю строку
    for /f "usebackq delims=" %%l in ("%%f") do (
        set /a lineCounter+=1
        if !lineCounter! equ 5 (
            set "line=%%l"
            echo !line! >> "%tempFile%"
            rem Прерываем внутренний цикл после нахождения 5-й строки
            break
        )
    )
)

        

rem Сортируем строки и записываем в log.txt
sort "%tempFile%" /o log.txt
del "%tempFile%"
echo Результат записан в log.txt