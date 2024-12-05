@echo off
setlocal

:: Проверка, передан ли PID как аргумент
if "%~1"=="" (
    echo Использование: %0 ^<PID^>
    exit /b 1
)

set PID=%~1

:: Проверка, существует ли процесс с данным PID
tasklist /FI "PID eq %PID%" | findstr /I "%PID%" >nul
if errorlevel 1 (
    echo Процесс с PID %PID% не найден.
    exit /b 1
) else (
    echo Процесс с PID %PID% запущен.
)

:: Запрос на завершение процесса
:ask
set /p answer="Хотите завершить процесс? [Y/n] "
if /I "%answer%"=="Y" (
    taskkill /PID %PID% /F
    echo Процесс завершен.
    exit /b 0
) else if /I "%answer%"=="n" (
    echo Вы выбрали не завершать процесс.
    exit /b 0
) else (
    echo Пожалуйста, введите Y или n.
    goto ask
)
