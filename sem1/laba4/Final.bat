@echo off
Setlocal EnableDelayedExpansion
set "filename=%~1"

if exist "%~dp0!filename!" (
cd /d %~dp0!filename!
) else ( 
echo "You don't have this dir" 
exit /b
)

for /R %%i in (*) do (
set /a n=0
for /f "usebackq delims=" %%y in (%%i) do (
 for %%j in (%%y) do (
  set /a n+=1
 )
 
)
rename "%%i" "!n!_%%~ni%%~xi"
)
exit /b
