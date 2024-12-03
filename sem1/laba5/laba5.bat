@echo off
setlocal enabledelayedexpansion

set /p directory="Enter the path to the directory: "
set /p min_pid="Min PID: "
set /p max_pid="Max PID: "

if not exist "%directory%" (
    mkdir "%directory%"
)

echo Wait...

for /f "tokens=1,2 delims=," %%A in ('tasklist /nh /fo csv') do (
    set "process_name=%%A"
    set "pid=%%B"
    set "process_name=!process_name:"=!"
    set "pid=!pid:"=!"

    if defined pid (
        if !pid! geq %min_pid% if !pid! leq %max_pid% (
            for /f "usebackq tokens=*" %%U in (`powershell -NoProfile -Command "try { (Get-WmiObject Win32_Process -Filter 'ProcessId=!pid!').GetOwner().User } catch { 'Неизвестно' }"`) do (
                set "user=%%U"
            )
            if "!user!"=="" (
                set "user=System"
            )
            set "file_path=%directory%\!pid!.txt"
            echo Имя процесса: !process_name! > "!file_path!"
            echo Пользователь: !user! >> "!file_path!"
        )
    )
)

if  %ERRORLEVEL%==1 (
	echo something happened...
)
if %ERRORLEVEL%==0 (
	echo Complite.
)
pause
