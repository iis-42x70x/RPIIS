@echo off
set size=%1
if "%size%"=="" (
  echo Ne zadan parametr razmer of file!
  exit /b
)
fsutil file createnew generated_file.txt %size%
for /f "tokens=1-5 delims=.: " %%j in ('
 dir/a-d/tc ".\generated_file.txt"^| findstr/rc:"^[^ ]"
') do (
  set /a hours=%%m
  set /a minutes=%%n
)
if "%hours%" lss "%minutes%" (
  set /a mod_val=%minutes% - %hours%
) else (
set /a mod_val=%hours%-%minutes%
)
set /a num_dir=%mod_val%*%size%
echo %num_dir%
for /L %%i in (1,1,%num_dir%) do (
  md %%i
  cd %%i
  echo. > "%hours%"_"%minutes%"
)
