@echo off
setlocal enabledelayedexpansion

if "%~1"=="" (
    echo Please enter a number as a parameter
    exit /b
)
set number=%~1

for /f "tokens=2 delims==" %%i in ('wmic os get localdatetime /value ^| find "="') do set date=%%i
set month=!date:~4,2!
set day=!date:~6,2!
set year=!date:~0,4!

if %number% lss 0 (
    echo !month!-!day!-!year!
) else (
    set /a mod=number %% 2
    if !mod! equ 0 (
        echo !month!/!day!/!year!
    ) else (
        echo !month!
    )
)

endlocal
