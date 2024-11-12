@echo off
chcp 65001

REM вводим путь к папке и формат файла
set folder_path=%1
set file_format=%2
if "%folder_path%"=="" (
    echo Ошибка: пустой путь!
)
if "%file_format%"=="" (
    echo Ошибка: пустой формат!
)

REM Подсчет количества файлов с заданным расширением в папке
set count=0
for /f %%a in ('dir "%folder_path%\"*.%file_format%"" /b /a-d ^| find /c /v ""') do set count=%%a
echo Количество файлов формата %file_format% - %count%

set /a remainder=%count% %% 2 
if %remainder%==0 (
    rem Получаем список процессов и считаем количество строк, исключая заголовок
    for /f "tokens=*" %%A in ('tasklist ^| find /C /V ""') do set Processes=%%A 
    echo Число активных процессов - %Processes%  
) else (
    rem Цикл отсчета времени
    for /l %%i in (7,-1,1) do (
        echo До завершения программы %%i секунд
        timeout /t 1 >nul
    )
    echo Программа завершена.
)