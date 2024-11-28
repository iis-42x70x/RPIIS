@echo off
if "%~1"=="" (
    echo The path to storage is missed. Try "%~0 path"
    exit /b 1
)
set "folder=%~1"
if not exist "%~1" (
    echo Directory is missed.
    exit /b 1
)

setlocal enabledelayedexpansion
set "count=0"

for /r "%folder%" %%f in (*) do (
    set /a count+=1
)

echo amount of files in "%folder%" = !count!
for /f "tokens=1-3 delims=." %%a in ("%date%") do (
    set day=%%a
    set month=%%b
    set year=%%c
)
set max_digit=0
for %%d in (%day% %month% %year%) do (
    for /l %%i in (0,1,9) do (
        echo %%d | find "%%i" >nul
        if not errorlevel 1 (
            if %%i gtr !max_digit! (
                set max_digit=%%i
            )
        )
    )
)
echo max date of today : "%max_digit%"
set /a result=%count% * %max_digit%
echo result = "%result%"
set "output_file=%folder%\%count%.txt"
echo %result% > "%output_file%"
echo result is saved at "%output_file%"
endlocal
exit /b 0
