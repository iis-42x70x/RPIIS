@echo off
setlocal enabledelayedexpansion

:: Путь к базовой директории
set "BASEPATH=C:\Users\Николай\source\repos\student\pioivis\lab5"

:: Запрос имени искомой папки
set /p DIRNAME=Enter folder name: 

:: Проверяем, существует ли директория
if not exist "%BASEPATH%\%DIRNAME%" (
    echo Folder "%DIRNAME%" doesnt found %BASEPATH%.
    pause
    goto :EOF
)

:: Удаляем предыдущий result.txt, если он существует
if exist "%BASEPATH%\result.txt" del "%BASEPATH%\result.txt"

:: Перебираем все txt файлы в указанной папке
for %%f in ("%BASEPATH%\%DIRNAME%\*.txt") do (
    :: Читаем каждый файл построчно
    for /f "usebackq delims=" %%L in ("%%f") do (
        :: Разбиваем строку на отдельные слова
        for %%W in (%%L) do (
            set "word=%%W"
            set "firstChar=!word:~0,1!"
            :: Проверяем первый символ слова без учёта регистра
            if /i "!firstChar!"=="v" (
                echo %%W>>"%BASEPATH%\result.txt"
            )
        )
    )
)

echo complete.
pause
