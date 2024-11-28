@echo off
setlocal enabledelayedexpansion

REM Проверка количества параметров
if "%~4"=="" (
    echo Использование: %0 путь мин_размер макс_размер владелец
    exit /b 1
)

REM Присваивание параметров переменным
set "dir_path=%~1"
set "min_s=%~2"
set "max_s=%~3"
set "owneroffile=%~4"
set "output_file=result.txt"
set "countto_files=0"

REM Проверка существования директории
if not exist "%dir_path%" (
    echo Данной папки нет
    exit /b 1
)

REM Очистка файла результатов если он существует
echo. > "%output_file%"

REM Поиск файлов
for /r "%dir_path%" %%F in (*) do (
    REM Увеличение счетчика просмотренных файлов
    set /a "countto_files+=1"
    
    REM Получение размера файла
    for %%A in ("%%F") do (
        set "file_size=%%~zA"
        
        REM Получение владельца файла
        for /f "tokens=*" %%O in ('dir /q "%%F" ^| findstr /i /c:"%owneroffile%"') do (
            REM Проверка размера и владельца
            if !file_size! GEQ %min_s% if !file_size! LEQ %max_s% (
                echo %%~dpF,%%~nxF,!file_size! >> "%output_file%"
		
            )
        )
    )
)

REM Добавление общего количества просмотренных файлов
echo Всего просмотрено файлов: %countto_files% >> "%output_file%"

endlocal