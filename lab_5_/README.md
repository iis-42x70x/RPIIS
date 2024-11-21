# Лабораторная работа №5
## Цели:
- Познакомиться с теоретической информацией о скриптах
- Познакомиться с синтаксисом скриптов bat и sh
- Выполнить выданный вариант лабораторной работы по выполнению скрипта
## Вариант лабораторной работы
Для выполнения лабораторной работы мне был выдан вариант 36 из [Google Disk](https://docs.google.com/document/d/1tXtgo5lmXXqKtmLP_zxZdqtialix6AT0hfbyLE4rFS8/edit?tab=t.0)\
Вариант 36:\
Создать файл sh и bat, который выполняет следующее:\
На вход пакетному файлу приходит число (как параметр пакетного файла). Требуется создать текстовый файл размера, заданного параметром (в байтах). Затем создать количество папок, вложенных друг в друга иерархически, равное числу символов в созданном файле, умноженное на сумму, получившуюся в результате сложения чисел, взятых из времени создания файла |MM-HH| (значение по модулю). В каждой папке создать по одному файлу с именем времени создания файла в формате HH_MM.
## Выполнение лаборатной работы
Скрипт, или сценарий - последовательность команд, инструкций на сценарном языке, обычно использующаяся для автоматизации рутинных задач.
## Сферы применения
- Веб-разработка\
	Создание динамических элементов на веб-страницах, валидация форм, анимации и многое другое
- Анализ данных\
    Обработка и анализ больших объемов информации, создание графиков и отчетов на основе данных
- Автоматизация задач\
	Написание скриптов для автоматизации повседневных задач, упрощение рутинных действий на компьютере
- Игровая индустрия\
    Создание интерактивных игр, управление поведением игровых объектов, разработка игровой логики
- Научные исследования\
	Моделирование процессов, обработка экспериментальных данных, создание специализированных инструментов для исследований
## Пример скрипта sh
```
# Команда ниже называется shebang он должен обязательно быть для того чтобы файл считался скриптом
#!/bin/bash
if [ $# -ne 1 ]; then
    echo "Неверное количество аргументов! Укажите размер файла в байтах."
    exit 1
fi
file_size=$1
dd if=text_template.txt of=generated_file.txt bs=1 count=$file_size
minutes=$(stat -f "%SB" generated_file.txt|cut -d ":" -f 2)
hours=$(stat -f "%SB" generated_file.txt|cut -d " " -f 3|cut -d ":" -f 1)
if [ "$hours" -lt "$minutes" ]; then
    mod_value_h_m=$((minutes - hours))
else
    mod_value_h_m=$((hours - minutes))
fi
number_of_directories=$((mod_value_h_m*file_size))
for ((i=1;i<=number_of_directories;i++))
do
	path_dir="./$i"
	mkdir -p "$path_dir"
	cd "./$i"
	touch "$hours"_"$minutes.txt"
done
echo "Гатово"
```
## Пример скрипта bat
```
@echo off
set size=%1
if "%size%"=="" (
  echo Ne zadan parametr razmer of file!
  exit /b
)
fsutil file createnew file.txt %size%
for /f "tokens=1-5 delims=.: " %%j in ('
 dir/a-d/tc "C:\Users\user\Desktop\file.txt"^| findstr/rc:"^[^ ]"
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
  echo. > "%hours%"-"%minutes%"
)
```
## Выводы
Я познакомился с теоретическими сведениями о скриптах, а также реализовал свой вариант скрипта sh и bat
## Ресурсы для обучения скриптам
[Список команд для bat/cmd](https://www.celitel.info/klad/bathelp/list_comm.htm)\
[Bash-скрипты: начало](https://habr.com/en/companies/ruvds/articles/325522/)\
[Шпаргалка по написанию bash-скриптов1](https://gist.github.com/Titiaiev/dcb7298389d1276b823bbc96e29f940d)\
[Шпаргалка по написанию bash-скриптов2](https://devhints.io/bash)\
[Выучите Х за Y минут,где Х=Bash](https://learnxinyminutes.com/docs/bash/)
