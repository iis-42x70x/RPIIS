@echo off
chcp 65001
setlocal
if "%~2"=="" (    
    echo Необходимы два аргумента: путь к первой и второй папке.
    exit /b 1
)
set "iz=%~1"
set "v=%~2"
    	
if not exist "%iz%" (
	echo Данной папки нет - %iz%
    	exit /b 1
)
if not exist "%v%" (
	echo Данной папки нет - %v%
    	exit /b 1
)
pushd "%iz%"
for %%F in (*) do (
	if /I "%%~xF"==".txt" (
        echo Перемещение файла %%F в %v%       
        move /Y "%%F" "%v%\"
) else (        
	echo Устанавливаем атрибут "только чтение" для файла %%F
        attrib +r "%%F"   
)
)
popd
echo Выполнение завершено.
endlocal
