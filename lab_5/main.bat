@echo off
setlocal enabledelayedexpansion

set num=%1
set max=0
for /L %%i in (0,1,9) do (
    echo %num% | findstr /C:"%%i" >nul && if %%i gtr !max! set max=%%i
)

set /a fileCount=0
for /L %%i in (1,1,!max!) do (
    set /a mod=%%i %% 2
    if !mod! equ 0 (
        echo %date% > "file%%i.doc"
    ) else (
        echo %date% > "file%%i.txt"
    )
    set /a fileCount+=1
)

echo Created !fileCount! files.
endlocal
