@echo off
setlocal enabledelayedexpansion

rem Проверяем количество параметров
if "%~3"=="" (
    echo Параметр не был передан
    exit /b 1
)

set "keywords_file=%1"
set "directory=%2"
set "numb=%3"

rem Создаем имя для новой подпапки
set "new_directory=%directory%_search"
mkdir "%new_directory%"

rem Читаем ключевые слова из файла
set "keywords="
for /f "delims=" %%k in (%keywords_file%) do (
    set "keywords=!keywords! %%k"
)
echo Ключевые слова: !keywords!

rem Проходим по всем текстовым файлам в исходной папке
for %%f in ("%directory%\*.txt") do (
    set "totalcount=0"

    rem Считаем количество вхождений ключевых слов в файле
    for %%k in (!keywords!) do (
        set "count=0"
        for /f %%i in ('findstr /c:"%%k" "%%f" ^| find /c /v ""') do (
            set /a count+=%%i)
    )
 echo Ключевое слово найдено !count! раз
set /a totalcount+=count
echo Общее количество вхождений ключевых слов: !totalcount!

    rem Если количество вхождений больше или равно заданному числу, копируем файл
    if !totalcount! geq %numb% (
        xcopy "%%f" "%new_directory%"
    )
)

echo Готово. Файлы скопированы в "%new_directory%" если количество вхождений ключевых слов больше или равно %numb%.
endlocal
