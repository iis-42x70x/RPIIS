@echo off

if "%~1"=="" (
    echo Folder path is not specified.
    exit /b
)

if not exist "%~1" (
    echo The folder does not exist.
    exit /b
)

pushd "%~1" >nul 2>&1 || (
    echo Error navigating to the folder.
    exit /b
)

setlocal enabledelayedexpansion
set "uniqueChars="

for /r %%F in (*.doc) do (
    set "filename=%%~nF"
    for /l %%I in (0,1,127) do (
        set "char=!filename:~%%I,1!"
        if defined char (
            echo !uniqueChars! | find "!char!" >nul || set "uniqueChars=!uniqueChars!!char!"
        )
    )
)

echo Number of unique characters: > W:\lab5\result.txt
echo !uniqueChars! >> D:\lab5\lab5_bat\result.txt

set /a uniqueCount=0
for /l %%I in (0,1,127) do (
    set "char=!uniqueChars:~%%I,1!"
    if defined char (
        set /a uniqueCount+=1
    )
)
echo Total unique characters count: !uniqueCount! > D:\lab5\lab5_bat\result.txt
echo Done. The result is saved in D:\lab5\lab5_bat\result.txt.

popd