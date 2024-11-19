@echo off
set dir1=%~1
set dir2=%~2
for  %%I in (%dir1%\*) do ( 
	if not exist %dir2%\%%~nxI (
		del %dir1%\%%~nxI 
		echo ydalenie %%~nxI iz %dir1%
	)
)   
for  %%I in (%dir2%\*) do (
	if not exist %dir1%\%%~nxI (
		copy %dir2%\%%~nxI %dir1%\%%~nxI
		echo Kopirovanie %%~nxI v %dir1%
	)
)
pause
