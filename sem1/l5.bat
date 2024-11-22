@echo off
chcp 65001
set /p path="Путь: "
set path2=%path:\=.%
if EXIST "%path%" (                     
    echo %path2%> %path%\%date%.txt )
if not EXIST "%path%" (  
echo “Заданной папки нет, создать ее [Y/n]?”
    set /p answer="Y/n: ")
    if "%answer%" equ "Y" (
        echo %answer%        mkdir %path%)
else if "%answer%" equ "n" ( 
echo n)
else if not EXIST "%path%" (
echo неверный ввод)
pause
