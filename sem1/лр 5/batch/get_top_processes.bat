@echo off

chcp 65001

if "%1"=="" (
    echo Параметр N не передан. Пожалуйста, введите количество процессов для отображения:
    set /p N=Введите число N: 
) else (
    set N=%1
)

:: Проверяем, является ли N числом (цифры от 0 до 9)
for /f "delims=0123456789" %%A in ("%N%") do (
    echo Ошибка: %N% - не является числом.
    exit /b 1
)

:: Получаем текущую дату в формате ГГГГ-ММ-ДД
for /f "tokens=2 delims==" %%I in ('"wmic os get LocalDateTime /value"') do set datetime=%%I
set current_date=%datetime:~0,4%-%datetime:~4,2%-%datetime:~6,2%

:: Создаем папку logs, если она отсутствует
if not exist "logs" mkdir "logs"

:: Указываем имя выходного файла
set output_file=logs\top_processes_%current_date%.txt

:: Запуск команды tasklist и сохранение в файл
echo Сортировка процессов по использованию памяти...
tasklist > process_list.txt

:: Проверяем, существует ли файл process_list.txt
if not exist process_list.txt (
    echo Ошибка: файл process_list.txt не был создан.
    exit /b 1
)

:: Обработка файла process_list.txt для извлечения топ N процессов
(for /f "skip=3 tokens=1,5 delims=," %%A in ('findstr /v "Имя" process_list.txt') do @echo %%A %%B) > temp_sorted.txt

:: Сортировка данных по памяти
(sort /r /+15 temp_sorted.txt) > sorted_processes.txt

:: Извлечение топ N строк
setlocal enabledelayedexpansion
set count=0
> %output_file% (
    for /f "tokens=*" %%A in (sorted_processes.txt) do (
        set /a count+=1
        if !count! LEQ %N% echo %%A
    )
)
endlocal

:: Удаляем временные файлы
if exist temp_sorted.txt del temp_sorted.txt
if exist sorted_processes.txt del sorted_processes.txt
if exist process_list.txt del process_list.txt

:: Уведомление об окончании
if exist "%output_file%" (
    echo Топ %N% процессов успешно сохранен в файл "%output_file%".
) else (
    echo Ошибка: Не удалось создать файл с результатами.
)
