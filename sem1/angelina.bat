@echo off
chcp 65001 > nul

REM Запрос пути к папке
set /p path="Путь: "
set path2=%path:\=.%

REM Проверяем, существует ли папка
if exist "%path%" (
    REM Если папка существует, создаем файл с текущей датой
    echo %path2%> "%path%\%date%.txt"
    echo Файл создан: "%path%\%date%.txt"
    pause
    exit /b
)

REM Если папки нет, предлагаем создать
echo Заданной папки нет, создать ее [Y/n]?
set /p answer="Ваш выбор: "

REM Обрабатываем ввод пользователя
if /i "%answer%"=="Y" (
    mkdir "%path%"
    echo Папка создана: "%path%"
    REM Создаем файл после создания папки
    echo %path2%> "%path%\%date%.txt"
    echo Файл создан: "%path%\%date%.txt"
    pause
    exit /b
) else if /i "%answer%"=="n" (
    echo Операция отменена пользователем.
    pause
    exit /b
) else (
    echo Неверный ввод.
    pause
    exit /b
)
