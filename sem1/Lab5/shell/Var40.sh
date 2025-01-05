@echo off

REM Проверка входных параметров
if "%~2"=="" (
    echo Usage: %~nx0 ^<folder_path^> ^<output_file^>
    exit /b 1
)

set "FOLDER_PATH=%~1"
set "OUTPUT_FILE=%~2"

REM Проверка существования папки
if not exist "%FOLDER_PATH%" (
    echo The folder does not exist
    exit /b 1
)

set "total_size=0"
set "total_files=0"

REM Обработка файлов
for /r "%FOLDER_PATH%" %%f in (*) do (
    set /a total_files+=1
    for %%s in (%%~zf) do set /a total_size+=%%s
)

REM Запись результатов
echo %FOLDER_PATH%, %total_size% bytes, %total_files% files > "%OUTPUT_FILE%"
