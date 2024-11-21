@echo off

if "%~1"=="" (
    echo Параметр не был передан.
    exit /b 1
)

if exist "%~1" (
    tasklist -fi "CPUTIME ge 00:10:00" -v -fo csv > processlist.csv
    set "input_file=processlist.csv"
    set "output_file=unfiltered.txt"

    echo. > "%output_file%"

    for /f "tokens=2,8 delims=," %%a in (%input_file%) do (
        if not %%b == "CPU Time" (
            echo %%~b        %%~a >> "%output_file%"
        )
    )
    sort /r %output_file% > result.txt
    echo Данные сохранены в result.txt.
) else (
    echo Данной папки нет.
    exit /b 1
)

exit /b 0
