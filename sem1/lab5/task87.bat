@echo off

chcp 65001 > null
rem позволяет использ переменные в циклах и менять их
setlocal enabledelayedexpansion

rem %1 первый аргумент тильда чтоб без кавычек
set "directory=%~1"

if not exist "%directory%" (
    echo Такой папки нет!
    exit /b 1
)

echo Папка %directory% существует!


set /a files=0

for /r "%directory%" %%f in (*) do (
set /a files+=1
)

echo Количество файлов в папке и ее подкаталогах: !files!

set /a process=0

rem скипаем тк первая строка команды это названия процессов, /f для обработки строк
for /f "skip=1" %%p in ('tasklist') do (
set /a process+=1
)
echo Количество включенных процессов: !process!

set /a result=process*files

rem получаем текущее время hh:mm:ss.ms
set "time=%time%"

rem 6й символ 2 значения после него берем
set "second=%time:~6,2%"
set "minute=%time:~3,2%"
set "hour=%time:~0,2%"

set "namefile=%second%_%minute%_%hour%.txt"


echo %result% > "%namefile%"

echo Результат записан в файл "%namefile%"

pause

