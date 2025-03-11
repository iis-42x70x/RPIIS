@echo off
Title Add amount of words in file to file's name
setlocal enabledelayedexpansion

set /p "folder=Write the path to the folder: "

if not exist "%folder%" (
    echo "This folder does't exist".
    pause
    exit 
)

for /r "%folder%" %%F in (*) do (
    set "file=%%~nxF"
    set "file_path=%%F"

    set "word_count=0"
 for /f "delims=" %%A in ('type "%%F"') do (
    for %%B in (%%A) do (
        set /a word_count+=1
    )
)

    set "new_name=!word_count!_!file!"
    ren "!file_path!" "!new_name!"
)

echo "Renaming over".