@echo off

setlocal EnableDelayedExpansion

set fileName=%1

cd . > temp.txt

sort %fileName% /o temp.txt

cd . > oddStrings.txt
cd . > evenStrings.txt

set counter=1
set currentCounterValueMod2=0
for /f %%i in (temp.txt) do (
	set /a currentCounterValueMod2=!counter!%%2

	if !currentCounterValueMod2! equ 1 (
		echo %%i >> oddStrings.txt
	) else (
		echo %%i >> evenStrings.txt
	)

	set /a counter=counter+1
)

del temp.txt

endlocal