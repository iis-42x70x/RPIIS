@echo off
chcp 65001
setlocal enabledelayedexpansion

set size=%1
set content=%2

if "%size%"=="" (
    echo Укажите размер файла в байтах как первый параметр!
    exit /b
)
if "%content%"=="" (
    echo Укажите второй параметр для записи в файл!
    exit /b
)

set outputDir=D:\Study\Pivo

fsutil file createnew "%outputDir%\myfile.txt" %size%
echo %content% > "%outputDir%\myfile.txt"

REM Получаем время создания файла
for /f "tokens=1-5 delims=/: " %%a in ('dir /T:C "%outputDir%\myfile.txt" ^| findstr myfile.txt') do (
    set hour=%%c
    set minute=%%b 
)

REM Вычисляем разницу между минутами и часами
set /a diff=%minute%-%hour%
if %diff% lss 0 (
    set /a diff=-%diff%
)

REM Подсчитываем количество символов в файле
set /a charCount=0
for /F "usebackq delims=" %%i in ("%outputDir%\myfile.txt") do (
    set string=%%i
    :loop
    if not "!string!"=="" (
        set /a charCount+=1
        set string=!string:~0,-1!
        goto loop
    )
)

REM Уменьшаем charCount на 1, так как последний символ был удалён
set /a charCount-=1

REM Вычисляем количество папок для создания
set /a totalFolders=!charCount! * !diff!

REM Создаем вложенные папки
set currentPath=%outputDir%
for /l %%i in (1,1,!totalFolders!) do (
    set currentPath=!currentPath!\folder%%i
    if not exist "!currentPath!" (
        mkdir "!currentPath!"
        echo Создана папка: !currentPath!
    )
    echo. > "!currentPath!\%hour%_%minute%.txt"
)

echo Готово!