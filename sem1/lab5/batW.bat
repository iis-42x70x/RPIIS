@echo off
setlocal enabledelayedexpansion

set "BASEPATH=W:\pioivis_lab5"

set /p DIRNAME=Enter folder name: 

if not exist "%BASEPATH%\%DIRNAME%" (
    echo Folder "%DIRNAME%" not found %BASEPATH%.
    pause
    goto :EOF
)

echo Folder found!

if exist "%BASEPATH%\result.txt" del "%BASEPATH%\result.txt"

for %%f in ("%BASEPATH%\%DIRNAME%\*.txt") do (
    for /f "usebackq delims=" %%L in ("%%f") do (
        for %%W in (%%L) do (
            set "word=%%W"
            set "firstChar=!word:~0,1!"
            if /i "!firstChar!"=="v" (
                echo %%W>>"%BASEPATH%\result.txt"
            )
        )
    )
)

echo Words successfully written to result.txt file!
pause
