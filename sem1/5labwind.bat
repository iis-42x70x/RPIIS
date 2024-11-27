@echo off
setlocal enabledelayedexpansion


set /a "DIVISOR=%~1" >nul 2>nul
if errorlevel 1 (
    echo Параметр должен быть числом.
    exit /b 1
)

set "FOUND=0"
for /f "skip=3 tokens=1,2" %%A in ('tasklist /NH /FO TABLE') do (
    set "NAME=%%A"
    set "PID=%%B"
    
    set /a "MOD=PID %% DIVISOR" >nul 2>nul
    if not errorlevel 1 if "!MOD!"=="0" (
        echo !NAME! !PID!
        set "FOUND=1"
    )
)

if "%FOUND%"=="0" (
    echo процесс не найден
    timeout /t 3 >nul
)
