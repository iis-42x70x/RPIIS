# Лабараторная работа №5
### Цель:
* Освоить командные оболочки shell (для OS семейства Unix) и cmd (для OS семейства MS Windows): изучить основные встроенные команды, научиться писать файлы сценариев, научиться соотносить командные оболочки для разных OS.
* Освоить командное окружение для OS семейства Unix(утилиты из пакета GNU Core Utilities), и соответствующие им утилиты для OS семейства MS Windows.
### Задание:
*Вариант 95:*

Создать файл sh и bat, который выполняет следующее:


На вход пакетному файлу приходит время (как параметр пакетного файла), когда код из данного пакетного файла должен быть выполнен. Создается папка на рабочем столе, в ней создается файл, куда записываются данные сети, ОС и запущенные процессы.


### Bat файл:
<p  align="center"><img src="bat.webp" ></p>

```
@echo off
chcp 1251 >nul

if "%~1"=="" (
    echo Укажите время в формате HH:MM в качестве параметра.
    exit /b
)
 
for /f "tokens=1-2 delims=:" %%A in ("%time%") do set /a "h=%%A, m=%%B"

for /f "tokens=1-2 delims=:" %%A in ("%~1") do set /a "th=%%A, tm=%%B"

set /a wait_mins=(th*60 + tm) - (h*60 + m)
if %wait_mins% lss 0 set /a wait_mins+=1440

echo Ожидание %wait_mins% минут...
timeout /t %wait_mins% /nobreak >nul

set "desk=%USERPROFILE%\Desktop"
set "folder=%desk%\ScheduledTask"
mkdir "%folder%"

set "log=%folder%\SystemInfo.txt"

echo Данные о сети: >> "%log%"
ipconfig >> "%log%"
echo. >> "%log%"

echo Данные об ОС: >> "%log%"
systeminfo >> "%log%"
echo. >> "%log%"

echo Запущенные процессы: >> "%log%"
tasklist >> "%log%"
echo. >> "%log%"

echo Задача выполнена. Данные записаны в "%log%".
```
### Sh файл:
<p  align="center"><img src="sh.webp" ></p>

```
#!/bin/bash
if [ -z "$1" ]; then
echo "Укажите время выполнения в формате HH:MM"
exit 1
fi
FOLDER=~/Desktop/NetworkInfo
mkdir -p "$FOLDER"
while true; do
CURRENT_TIME=$(date +%H:%M)
if [ "$CURRENT_TIME" == "$1" ]; then
break
fi
sleep 60
done
{
echo "Дата и время: $(date)"
echo "Информация о сети:"
ifconfig
echo "Информация об ОС:"
uname -a
echo "Запущенные процессы:"
ps aux
} > "$FOLDER/info.txt"
echo "Данные записаны в $FOLDER/info.txt"

```
### Полезные сайты:
Подойдёт для тех, кто начал работать с bat файлами: [ссылка](https://help.reg.ru/support/servery-vps/oblachnyye-servery/rabota-s-serverom/kak-sozdat-bat-fayl-i-rabotat-s-nim#0).

Также можно почитать это: [batch script](https://habr.com/ru/sandbox/168937/).

А здесь можно почитать про sh файлы: [ссылка](https://selectel.ru/blog/tutorials/linux-bash-scripting-guide/).

### Вывод:
Файлы с расширением .bat и .sh являются скриптовыми файлами, которые используются для автоматизации задач в операционных системах Windows и Unix/Linux соответственно. 
Оба типа файлов являются мощными инструментами для автоматизации и управления системами, но они предназначены для различных операционных систем и имеют свои уникальные особенности и возможности. Знание их различий и умений написания может существенно упростить выполнение рутинных задач и улучшить производительность работы.
