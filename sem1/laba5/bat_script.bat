@echo off
chcp 65001
set "folder=%~1"

if not exist "%folder%" (
  echo Данной папки нет
  exit /b 1
)
setlocal EnableDelayedExpansion

for /r "%folder%" %%f in (*.txt) do (
  for %%a in ("%%f") do set "size=%%~za"
  if !size! lss 500000 (
    set "files=!files!%%f "
  )
)

set "smallest_file="
set "smallest_size=500000"

for %%f in (%files%) do (
  for %%a in ("%%f") do set "file_size=%%~za"
  if !file_size! lss !smallest_size! (
    set "smallest_file=%%f"
    set "smallest_size=!file_size!"
    set "smallest_file_name=%%~nxf"	
  )
)

if defined smallest_file (
  echo Удаляем файл: !smallest_file_name!
  del "!smallest_file!"
) else (
  echo Не удалось найти подходящий файл для удаления.
)
endlocal
pause
