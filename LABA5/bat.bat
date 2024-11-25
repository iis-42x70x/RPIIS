@echo off
setlocal enabledelayedexpansion
chcp 65001

if "%~1"=="" (
    exit /b
)

set "folder=%~1"

if not exist "!folder!" (
    exit /b
)

> log.txt echo.

for /r "%folder%" %%f in (*.txt) do (
    set "line="
    set /a count=0
    for /f "usebackq tokens=*" %%l in ("%%f") do (
        set /a count+=1
        if !count! equ 5 (
            set "line=%%l"
      echo !line!
    echo !line! >> log.txt
        )
    )
 )

sort log.txt /o log.txt

echo Готово
pause
