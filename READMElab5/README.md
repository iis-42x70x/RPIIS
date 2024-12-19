## Условие лабораторной работы 5:

### Вариант 48. Создать файлы sh и bat, которые выполняют следующее:

На вход пакетному файлу приходит некоторое число, относительный путь к файлу (как параметр пакетного файла), содержащему строки, в каждой из которых написано через пробел целое число и строка. Необходимо рядом с исходным файлом создать файл с названием, совпадающим с текущей датой, и скопировать в него все строки из исходного файла, содержащие число большее либо равное заданному числу в качестве параметра.

## Цель работы:

- Освоить командные оболочки shell (для OS семейства Unix) и cmd (для OS семейства MS Windows):
    + изучить основные встроенные команды,
    + научиться писать файлы сценариев,
    + научиться соотносить командные оболочки для разных OS.
- Освоить командное окружение для OS семейства Unix(утилиты из пакета GNU Core Utilities), и соответствующие им утилиты для OS семейства MS Windows.

## Ход работы:

Используя материалы в интернете, я написала скрипты под windows и linux.

Код для Windows:

```batch
  @echo off
set /p number="input any number: "
set /p path="Input a path: "

call :checkNumber
call :checkPath
goto :passed

rem "function that validates input 'number' variable"
:checkNumber
if "%number%"=="" (echo the "number" variable isn't defined & goto :exit)
for /f "tokens=* delims=0" %%a in ("%number%") do (set number=%%a)
if "%number%" == "" (set number=0 & exit /b)
set /a "isInteger=number*1"
if NOT %isInteger% == %number% (echo the input number doesn't have number type & goto :exit)
exit /b

rem "function that validates input 'path' variable"
:checkPath
if "%path%"=="" (echo the "path" variable isn't defined & goto :exit)
if not exist "%path%" (echo the entered path doesn't exist & goto :exit)
exit /b


:passed
set dateStr=%date%
type nul > %dateStr%.txt
for /f "tokens=1,2 delims= " %%i in (%path%) do (if %%i geq %number% (echo %%i %%j >> %dateStr%.txt))

:exit
pause
```

Код для Linux:

```bash
read -p "Input any number: " number
read -rp "Input a path: " path

number=$(echo $number | sed 's/^0*//')
isPassed=1
checkNumber() {
 if [ "$number" == "" ]; then
  isPassed=0
  echo "the 'number' variable isn't defined"
 elif ! [[ $number =~ ^-?[0-9]+$ ]]; then
  isPassed=0
  echo "the 'number' variable doesn't have number type"
 fi
}
checkPath() {
 if [ "$path" == "" ]; then
  isPassed=0
  echo "the 'path' variable isn't defined"
 elif ! [ -e $path ]; then
  isPassed=0
  echo "the entered path doesn't exist"
 fi
}
checkNumber
checkPath
if [ $isPassed -eq 1 ]; then
 fileName="$(printf "%(%d.%m.%Y)T").txt"
 if [ -e $fileName ]; then
     rm "$fileName"
 fi
 touch "$fileName"
 cat $path | while read line 
 do
    read -a data <<< "$line"
    if [[ ${data[0]} -ge $number ]]
    then
     echo "${data[0]} ${data[1]}" >> "$fileName"
    fi
 done
fi
```

#### Переменные:

Для Windows я использовала переменные:

- number - для параметра входного числа.
- file_path - для сохранения и последующего использования пути ко входному файлу.
- date - для получения текущей даты.
- i - для сохранения и последующего сравнения первой подстроки (числовой подстроки) из входного файла.
- j - для сохранения и последующего включения в выходной файл текстовой подстроки.

Для Linux я использовала переменные:

- number - для параметра входного числа.
- file_path - для сохранения и последующего использования пути ко входному файлу.
- date - для получения текущей даты.
- str_num - для сохранения и последующего сравнения числа в начале строки.
- line - для сохранения строки.

## Вывод

В ходе данной лабораторной работы я изучила основные встроенные команды, научилась писать файлы сценариев, соотносить командные оболочки для разных OS, также освоила командное окружение Unix и MS Windows.
