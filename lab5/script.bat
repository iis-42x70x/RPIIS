@echo off 
chcp 65001  
set /p "N=Введите числовое значение для N (интервал в секундах): " 
set /p "M=Введите числовое значение для M (максимальное время работы в секундах): " 
set /a "total_time=0" 
set /a "counter=1" 
set "current_path=%~dp0folder_%counter%" 
mkdir "%current_path%" 
timeout /t %N% >nul
set /a "total_time+=N" 
:loop 
    if %total_time% gtr %M% goto :end 
    set "file_path=%current_path%\%counter%.txt" 
   
    echo Общее время работы скрипта: %total_time% секунд > "%file_path%" 
    echo Новый файл %counter% был создан 
    set /a "counter+=1" 
    set "current_path=%current_path%\folder_%counter%" 
    mkdir "%current_path%" 
 set /a "total_time+=N" 
    timeout /t %N% >nul 
goto :loop 
:end 
set /a "total_folders=counter-1" 
echo Скрипт завершил работу. Общее количество созданных папок: %total_folders% 
pause