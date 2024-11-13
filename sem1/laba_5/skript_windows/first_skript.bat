@echo off
chcp 65001

set "rel_path=%1"

if "%rel_path%" equ "" (
    echo Вы не ввели параметр!
    pause
    exit /b 
)

set "abs_path=%cd%\%rel_path%"

if not exist "%abs_path%" (
    echo Данной папки нет.
    pause
    exit /b
)
set "list=list.txt"

for /f "delims=" %%a in (' dir "%abs_path%\*.bat" /a-d/b/s/o:n') do (
    echo Запускаем "%%a"
    call "%%a" >> "%list%"
)
pause

echo Случайные числа в порядке убывания : > result.txt

sort /R %list% >> result.txt
del %list%

echo Результаты записаны в result.txt

exit /b