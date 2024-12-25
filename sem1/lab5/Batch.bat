@echo off

If «%~4»==»» (
    Echo Использование: %~nx0 ^<каталог^> ^<min_size^> ^<max_size^> ^<владелец^>
    Exit /b 1
)

Set «dir=%~1»
Set «min_size=%~2»
Set «max_size=%~3»
Set «owner=%~4»

If not exist «%dir%» (
    Echo Данной папки нет
    Exit /b 1
)

For /r «%dir%» %%F in (*) do (
    For /f «delims=» %%S in ('wmic where «Path='%%F'» get Size /value') do set «size=%%S»
    For /f «delims=» %%U in ('wmic where «Path='%%F'» get Owner /value') do set «file_owner=%%U»

    Set /a «size_int=%size:~0,-2%»
    If %size_int% GEQ %min_size% if %size_int% LEQ %max_size% if «%file_owner:~0,-1%»==»%owner%» (
        Echo «%%F», «%%~nxF», «%size%»
    )
)

For /f «delims=» %%F in ('dir /b /a-d «%dir%»') do set /a «total_files+=1»
Echo Общее число просмотренных файлов: %total_files% >> results.txt

