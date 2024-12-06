@echo off
chcp 65001

if "%~1"=="" (
echo Не указан путь к каталогу
exit /b
)

if not exist "%~1" (
echo Данной папки нет
exit /b 
)

if "%~2"=="" (
echo Не указан путь к новому файлу для записи
exit /b
)

setlocal enabledelayedexpansion
set "direct=%~1"
set "output=%~2"
set "temp_file=temp_file.txt"
set "sort_temp_file=sort_temp_file.txt"

for /r "%direct%" %%f in (*) do (
    set "size=%%~zf"
    set "name=%%~nxf"
    echo !size! !name! >> "%temp_file%"
)
sort /r "%temp_file%" > "%sort_temp_file%"

for /f "tokens=1,2 delims= " %%a in (%sort_temp_file%) do (
    echo %%b %%a 
) >> "%output%"

del "%temp_file%"
del "%sort_temp_file%"

echo Результаты сохранены в "%output%"
endlocal
exit /b
