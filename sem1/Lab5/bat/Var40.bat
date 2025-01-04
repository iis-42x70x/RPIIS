@echo off

REM Prompt user for folder path and output file if not provided
if "%~1"=="" (
    set /p FOLDER_PATH="Enter folder path: "
) else (
    set "FOLDER_PATH=%~1"
)

if "%~2"=="" (
    set /p OUTPUT_FILE="Enter output file name: "
) else (
    set "OUTPUT_FILE=%~2"
)

REM Check if the folder exists
if not exist "%FOLDER_PATH%" (
    echo The folder does not exist
    pause
    exit  1
)

REM Initialize counters
set "total_size=0"
set "total_files=0"

REM Traverse through the directory and calculate size
for /r "%FOLDER_PATH%" %%f in (*) do (
    set /a total_files+=1
    for %%s in (%%~zf) do set /a total_size+=%%s
)

REM Write the result to the output file
echo %FOLDER_PATH%, %total_size% bytes, %total_files% files > "%OUTPUT_FILE%"

REM Notify the user
echo Results saved to %OUTPUT_FILE%
pause
