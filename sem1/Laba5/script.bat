@echo off
if not exist "%~1" (
  echo Данной папки нет
  exit /b 1
)

setlocal EnableDelayedExpansion

set count=0
for /r "%~1" %%a in (*.%~2) do (
  if attrib "%%a" 2>&nul find "H" (
    set /a count+=1
  )
)

echo Найдено скрытых файлов с расширением %~2: !count!
endlocal
