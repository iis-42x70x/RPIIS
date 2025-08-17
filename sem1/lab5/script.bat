@echo off
setlocal enabledelayedexpansion

set path=%1

IF EXIST %path% (
	FOR /F "delims=" %%a in (%path%) DO (
		for %%b in (%%a) do (
			set /a counw += 1
		)
	)
	set counc=0
	FOR %%i in (%1) DO (
		set counc=%%~zi
	)
	
	set /a res=!counw! * !counc! * %date:~,2%
	
	echo !res! >> result.txt	

) ELSE (
	echo no files
)  
endlocal