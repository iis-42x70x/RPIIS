@echo off
chcp 65001

if "%~1"=="" (
    echo Не указан путь к папке
    exit /b 1
)

set "DIR=%~1"

if not exist "%DIR%" (
    echo Данной папки нет
    exit /b 1
)

if exist result.txt del result.txt

for /r "%DIR%" %%f in (*.txt) do (
    findstr /r /i "\<v[a-z]*" "%%f" >> result.txt
)

echo Результат записан в result.txt
exit /b 0