@echo off
chcp 65001 

if "%~3"=="" ( 
  
 echo net 3 parametra

    exit /b 1
)

echo point1

set "DIR=%~1"
set "EXT=%~2"
set "MAX_LENGTH=%~3"

:: Проверка, является ли MAX_LENGTH числом

for /l %%i in (0,1,9) do (
if "!MAX_LENGTH:%%i=!"=="!MAX_LENGTH!" (   
 echo Error: MAX_LENGTH must be a number.
    exit /b 1
   )
)

echo point2

if not exist "%DIR%" (
    echo Данной папки нет   
 exit /b 1
)
echo point3

:: Создаем файл с результатами

set "OUTPUT_FILE=%DIR%\result.txt"
if exist "%OUTPUT_FILE%" del "%OUTPUT_FILE%"

echo point4

:: Обрабатываем файлы с указанным расширением
for %%F in ("%DIR%\*.%EXT%") do (
    call :CHECK_LENGTH "%%~nxF"
)

echo point5

:: Проверяем, создался ли файл с результатами

if not exist "%OUTPUT_FILE%" (    
echo No files found with the specified extension.
    exit /b 1
)
echo point6

:: Сортируем файл по алфавиту
sort "%OUTPUT_FILE%" /o "%OUTPUT_FILE%"
echo Файл с результатами создан: "%OUTPUT_FILE%"
exit /b

:CHECK_LENGTH
setlocal enabledelayedexpansion
set "CURRENT_FILENAME=%~1"
echo point7

:: Подсчитываем длину имени файла
set "LENGTH=0"
for /l %%i in (0,1,255) do (
    if "!CURRENT_FILENAME:~%%i,1!"=="" (  
      set "LENGTH=%%i"
        goto :BREAK  
  )
)
:BREAK

echo point8

:: Проверяем длину имени
if !LENGTH! LEQ %MAX_LENGTH% (
    echo !CURRENT_FILENAME! >> "%OUTPUT_FILE%"
)
endlocal
echo point9
exit /b
