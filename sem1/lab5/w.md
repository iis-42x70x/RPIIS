@echo off
chcp 65001 >nul
setlocal enabledelayedexpansion

:: Проверка на наличие аргумента
if "%~1"=="" (
    echo Укажите путь к каталогу
    exit /b 1
)

:: Создание целевого каталога
set "TARGET_DIR=%~1"
if not exist "%TARGET_DIR%" mkdir "%TARGET_DIR%"

:: Получение списка процессов
for /f "skip=3 tokens=1,2,5 delims=," %%A in ('tasklist /fo csv /nh') do (
    set "NAME=%%~A"
    set "PID=%%~B"
    set "MEMORY=%%~C"

    :: Удаляем кавычки из имени процесса
    set "NAME=!NAME:"=!"

    :: Преобразуем память в числовой формат (удаляем "K")
    set "MEMORY=!MEMORY:K=!"

    :: Удаляем пробелы из памяти
    set "MEMORY=!MEMORY: =!"

    :: Создание каталога по имени процесса
    set "PROCESS_DIR=%TARGET_DIR%!NAME!"
    if not exist "!PROCESS_DIR!" mkdir "!PROCESS_DIR!"

    :: Запись размера памяти в файл с именем PID
    echo !MEMORY! > "!PROCESS_DIR!!PID!.txt"
)
