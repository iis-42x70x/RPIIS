@echo off
chcp 65001
setlocal

if "%~1"=="" (
    echo Укажите путь к папке-источнику.
    exit /b 1
)

if "%~2"=="" (
    echo Укажите путь к папке-назначению.
    exit /b 1
)

set "source=%~1"
set "destination=%~2"

rem Копируем файлы из источника в назначение
for %%F in ("%destination%\*") do (
    if not exist "%source%\%%~nxF" (
        echo Копируем %%~nxF из %destination% в %source%
        copy "%%F" "%source%\"
    )
)

echo Синхронизация завершена.
endlocal