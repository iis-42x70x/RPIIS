@echo off
chcp 1251
setlocal

rem Создание переменных для хранения суммарной памяти и количества процессов
set "total_memory=0"
set "process_count=0"

rem Использование команды tasklist для получения информации о процессах
for /f "skip=3 tokens=5" %%A in ('tasklist') do (
    set /a total_memory+=%%A
    set /a process_count+=1
)

rem Сохранение результатов в файл
set "output_file=system_memory_usage.txt"
echo Суммарный объем памяти (в KB): %total_memory% > "%output_file%"
echo Число активных процессов: %process_count% >> "%output_file%"

echo Результаты сохранены в файл %output_file%
pause

