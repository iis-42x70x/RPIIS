# Лабораторная работа 5
 
### Цель: 
 
Освоить командные оболочки shell (для OS Unix) и cmd (для OS MS Windows):
+ изучить основные встроенные команды,
+ научиться писать файлы сценариев,
+ научиться соотносить командные оболочки для разных OS.
+ Освоить командное окружение для OS семейства Unix(утилиты из пакета GNU Core Utilities), и соответствующие им утилиты для OS семейства MS Windows.

### Условия задания:
Создать файл sh и bat, который выполняет следующее:
На вход пакетному файлу приходит значение PID (число) процесса (как параметр пакетного файла). Если процесс запущен, то вывести информацию о нем. Далее вывести сообщение, “Хотите завершить процесс? [Y/n]”, если после этого пользователь ввел Y, то процесс должен быть завершен с сообщением в консоль “Процесс завершен”, если пользователь выбрал n, то программа заканчивается, если пользователь ввел что-то другое, то повторно задать вопрос.

## Batch файл

@echo off
setlocal

if "%~1"=="" (
    echo Please specify the PID of the process.
    exit /b 1
)

set PID=%~1

rem Checking whether the process is running
tasklist /FI "PID eq %PID%" | findstr /I "%PID%" >nul
if errorlevel 1 (
    echo Process with PID %PID% not found.
    exit /b 1
)

rem Output of information about the process
echo Information about the process with PID %PID%:
tasklist /FI "PID eq %PID%"

:ask
set /p choice="Do you want to complete the process? [Y/n]: "
if /I "%choice%"=="Y" (
    taskkill /PID %PID% /F
    echo The process is completed.
    exit /b 0
) else if /I "%choice%"=="n" (
    exit /b 0
) else (
    echo Incorrect input. Please enter Y or n.
    goto ask
)


### Пример работы кода
Information about the process with PID 7536:

Имя образа                     PID Имя сессии          № сеанса       Память
========================= ======== ================ =========== ============
mediaget.exe                  7536 Console                    1    64 200 КБ
Do you want to complete the process? [Y/n]: Y
Успешно: Процесс, с идентификатором 7536, успешно завершен.
The process is completed.


@echo off: Отключает вывод команд в консоль. Символ @ перед этой командой предотвращает вывод самой команды echo off.


if "%~1"=="" (
    echo Please specify the PID of the process.
    exit /b 1
) :Проверяет, был ли передан аргумент (PID). Если аргумент не указан, выводит сообщение об ошибке и завершает выполнение с кодом 1

set PID=%~1: Сохраняет переданный аргумент (PID) в переменной PID для дальнейшего использования.


rem Checking whether the process is running
tasklist /FI "PID eq %PID%" | findstr /I "%PID%" >nul
if errorlevel 1 (
    echo Process with PID %PID% not found.
    exit /b 1
) : Использует команду tasklist для получения списка запущенных процессов и фильтрует его по указанному PID.
Если процесс не найден (код ошибки равен 1), выводится сообщение об этом, и скрипт завершается.


echo Information about the process with PID %PID%:
tasklist /FI "PID eq %PID%" :Выводит информацию о процессе с указанным PID, используя команду tasklist.


:ask
set /p choice="Do you want to complete the process? [Y/n]: "
if /I "%choice%"=="Y" (
    taskkill /PID %PID% /F
    echo The process is completed.
    exit /b 0
)
else if /I "%choice%"=="n" (
    exit /b 0
)
else (
    echo Incorrect input. Please enter Y or n.
    goto ask
) :Здесь программа запрашивает у пользователя, хочет ли он завершить процесс.
Если пользователь вводит Y, выполняется команда taskkill, которая завершает процесс с указанным PID, и выводится сообщение о завершении.
Если пользователь вводит n, программа просто завершает выполнение.
Если ввод некорректный, программа сообщает об этом и снова запрашивает ввод.

###Bash файл
#!/bin/bash

if [ -z "$1" ]; then
    echo "Please specify the PID of the process."
    exit 1
fi

PID=$1

# Checking whether the process is running
if ps -p $PID > /dev/null; then
    echo "Information about the process with PID $PID:"
    ps -p $PID -o pid,comm,user
else
    echo "Process with PID $PID not found."
    exit 1
fi

while true; do
    read -p "Do you want to kill the process? [Y/n]: " choice
    case "$choice" in
        [Yy]* )
            if kill -9 $PID; then
                echo "The process has been terminated."
            else
                echo "Failed to terminate the process."
            fi
            exit 0
            ;;
        [Nn]* )
            exit 0
            ;;
        * )
            echo "Incorrect input. Please enter Y or n."
            ;;
    esac
done

###разборка кода
#!/bin/bash
Эта строка указывает, что скрипт должен выполняться с помощью интерпретатора Bash.


if [ -z "\$1" ]; then
    echo "Please specify the PID of the process."
    exit 1
fi
Проверяет, был ли передан аргумент (PID) при запуске скрипта.
-z "\$1": Проверяет, пуст ли первый аргумент.
Если аргумент не указан, выводится сообщение об ошибке, и скрипт завершает выполнение с кодом 1.


PID=\$1
Сохраняет переданный аргумент (PID) в переменной PID для дальнейшего использования.


if ps -p $PID > /dev/null; then
    echo "Information about the process with PID $PID:"
    ps -p $PID -o pid,comm,user
else
    echo "Process with PID $PID not found."
    exit 1
fi
Использует команду ps для проверки, запущен ли процесс с указанным PID.
ps -p $PID > /dev/null: Проверяет наличие процесса, перенаправляя вывод в /dev/null (скрывает его).
Если процесс найден, выводится информация о процессе (PID, команда и пользователь), используя ps -p $PID -o pid,comm,user.
Если процесс не найден, выводится сообщение об этом, и скрипт завершает выполнение с кодом 1.


while true; do
    read -p "Do you want to kill the process? [Y/n]: " choice
    case "$choice" in
        [Yy]* )
            if kill -9 $PID; then
                echo "The process has been terminated."
            else
                echo "Failed to terminate the process."
            fi
            exit 0
            ;;
        [Nn]* )
            exit 0
            ;;
        * )
            echo "Incorrect input. Please enter Y or n."
            ;;
    esac
done
Бесконечный цикл while true для запроса у пользователя, хочет ли он завершить процесс.
read -p "Do you want to kill the process? [Y/n]: " choice: Запрашивает ввод от пользователя и сохраняет его в переменной choice.
case "$choice": Использует оператор case для обработки пользовательского ввода:
Если пользователь вводит Y или y, выполняется команда kill -9 $PID, которая принудительно завершает процесс.
Если процесс успешно завершен, выводится сообщение об этом.
Если завершение не удалось, выводится сообщение о неудаче.
Если пользователь вводит N или n, скрипт завершает выполнение.
Если ввод некорректный, выводится сообщение об ошибке, и цикл продолжается.

### Выводы: 
 В ходе выполнения лабораторной работы по освоению командных оболочек cmd (для операционных систем MS Windows) и shell (для операционных систем Unix) были получены практические навыки работы с консольными программами и командами в различных операционных системах. 