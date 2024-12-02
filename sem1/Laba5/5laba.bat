@echo off
REM Получаем сегодняшнюю дату
FOR /F "tokens=1,2 delims= " %%A IN ('date /t') DO SET today=%%B%%A
REM Считаем количество активных процессов и сохраняем в переменную total.
REM Используем команду 'tasklist' для получения списка процессов.
REM 'find /c' считает количество строк.
FOR /F %%i IN ('tasklist ^| find /v "Image Name" ^| find /v "===" ^| find /c /v ""') DO SET total=%%i
SET result=%today% %total%
REM Создаем файл result.txt и записываем туда результат.
echo %result% > result.txt
echo Результат записан в файл result.txt: %result%
