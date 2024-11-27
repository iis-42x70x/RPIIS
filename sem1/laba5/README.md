# Лабораторная работа №3
---
### Условие лабораторной работы №1

**Цель:** Освоить командные оболочки shell для OS семейства Unix и cmd для OS семейства MS Windows:
* изучить основные встроенные команды,
* научиться писать файлы сценариев,
* научиться соотносить командные оболочки для разных OS.
Освоить командное окружение для OS семейства Unix (утилиты из пакета GNU Core Utilities), и соответствующие им утилиты для OS семейства MS Windows.

## Задание:

Создать файл sh и bat, который выполняет следующее: 

На вход пакетному файлу приходит относительный путь к папке (как параметр пакетного файла). Если такой папки нет, то писать “Данной папки нет” и завершить выполнение программы. Создать файл, в который записать три числа, сгенерированных случайным образом. Если сумма чисел - четное число, то создать файл, в который записать значения всех переменных среды, затем посчитать количество встречающихся в файле символов “/” и записать его в конец файла. Если сумма чисел нечетное число - создать файл, в который записать сумму цифр текущей даты.

### Основные команды:
#### Для sh файла:
* echo "какой-то текст"
* cd директория
* printenv > текстовый файл
* переменная=$((RANDOM))

  #### Для bat файла:
* exit /b 1
* set /a переемнная=%RANDOM%
* for /f "tokens=*" %%A in (!ссылка на текстовый файл!) do (команды в цикле)
* for /l %%i in (первый элемент, шаг цикла, последний элемент) do (команды в цикле)

  ### Мой вариант выполненной работы.
  
**sh файл**
```
#!/bin/bash
if [ -z "$1" ]; then
  echo "Путь к папке не указан"
  exit 1
fi
D="$1"
if [ ! -d "$D" ]; then
  echo "Данной папки нет"
  exit 1
fi
cd "$D"
num1=$((RANDOM))
num2=$((RANDOM))
num3=$((RANDOM))
echo "$num1 $num2 $num3" > random_n_sh.txt
sum=$((num1 + num2 + num3))
if ((sum % 2 == 0)); then
  printenv > peremnnyesredy_sh.txt
  count=$(grep -o "/" peremnnyesredy_sh.txt | wc -l)
  echo "Количество символов '/': $count" >> peremnnyesredy_sh.txt
else
  date_sum=$(date +%Y%m%d | sed 's/./+&/g;s/^+//')
  date_result=$(($date_sum))
  echo "Сумма цифр текущей даты: $date_result" > date_sum_sh.txt
fi
```
Переменные: 
* D - полученная директория
* num1,num2,num3 - рандомные значения
* sum - сумма рандомных переменных
* count - переменная для подсчета количества слешей
* date_sum - строчка вида "2+0+2+4+2+7+1+1"
* date_result - сумма цифр даты

**bat файл**
```
@echo off
> peremennye.txt echo.
setlocal enabledelayedexpansion
if "%~1"=="" (
  echo Путь к папке не указан
  exit /b 1
)
set "DIR=%~1"
if not exist "%DIR%" (
  echo Данной папки нет
  exit /b 1
)
cd "%DIR%"
set /a num1=%RANDOM%
set /a num2=%RANDOM%
set /a num3=%RANDOM%
echo %num1% %num2% %num3% > random_num_bat.txt
set /a sum=%num1% + %num2% + %num3%
set /a ostatok=%sum% %% 2
if %ostatok%==0 (
  set "peremennye=peremennye_bat.txt"
   set count=0
    for /f "tokens=*" %%i in ('set') do (
        echo %%i >> !peremennye!
    )
for /f "tokens=*" %%A in (!peremennye!) do (
    set line=%%A
    for /l %%i in (0,1,1024) do (
        if "!line:~%%i,1!"=="\" set /a count+=1
    )
)
    echo kolichestvo simvolov "\": !count! >> !peremennye!
) else (
    set "date_sum_file=date_sum_bat.txt"
    for /f "tokens=2 delims==" %%d in ('wmic os get localdatetime /value') do set "current_date=%%d"
    
    set /a sum=0
    for /l %%i in (0,1,7) do (
        set /a sum+=!current_date:~%%i,1!
    )
    
    echo Сумма цифр в дате: !sum! > !date_sum_file!
)
```
Переменные:
* DIR - директория
* num1,num2,num3 - рандомные значения
* sum - сумма рандомных переменных
* ostatok - остаток от деления суммы на 2
* count - переменная для подсчета количества слешей
* line - строчка, в которой мы ищем слеш
* current_date - полные текущие дата и время
* sum_date - сумма цифр даты
* date_sum_file, peremennye - ссылки на файлы для токо чтобы можно было с файлами работать в цикле
