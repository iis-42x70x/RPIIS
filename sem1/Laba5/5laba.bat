@echo off
rem Получаем сегодняшнюю дату
for /F "tokens=1,2 delims= " %%A in ('date /t'do set today=%%B%%A
rem Считаем количество активных процессов и сохраняем в переменную total.
rem Используем команду 'tasklist' для получения списка процессов.
rem 'find /c' считает количество строк.
for /F %%i in ('tasklist ^| find /v "Image Name" ^| find /v "===" ^| find /c /v ""') do set total=%%i
SET result=%today%_%total%
rem Создаем файл result.txt и записываем туда результат.
echo %result% > result.txt
echo Результат записан в файл result.txt: %result%
