@echo off
 chcp 65001 > nul  

setlocal enabledelayedexpansion
set TARGET_DIR=%1

:: проверка подкл папки
if "%TARGET_DIR%"=="" exit /b

::создаем папки и в них текстовые и пишем память в файл
for /f "skip=3 tokens=1,2,5 delims=," %%A in ('tasklist /fo csv /nh') do (
    mkdir "%TARGET_DIR%\%%~A" 2>nul 
:: переменная для мемори
    set "mem=%%C"
    echo !mem! > "%TARGET_DIR%\%%~A\%%~B.txt"
)