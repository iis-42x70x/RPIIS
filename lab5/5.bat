chcp 1252
@echo off
set /p Start=Start: 
set /p End=End:
echo Name ------------ RAM  > bat.txt
for /f "tokens=1,5" %%a in ('tasklist /FI "MEMUSAGE ge %Start%" /FI "MEMUSAGE le %End%" ^| findstr /V "Image" ^| findstr /V "=====" ^| sort') do (	
        echo %%a %%b >> bat.txt
    )
notepad bat.txt
exit