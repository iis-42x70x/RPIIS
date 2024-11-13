@echo off
set number=%1
set file_path=%2

cd . > %date%.txt

for /F "tokens=1,2" %%i in (%file_path%) do (
    if %%i GEQ %number% echo %%i %%j >> %date%.txt
)

echo Done. Output saved to %date%.txt.

pause