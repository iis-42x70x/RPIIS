# Лабораторная работа №5
### Цель:
* Освоить командные оболочки shell (для OS семейства Unix) и cmd (для OS семейства MS Windows): изучить основные встроенные команды, научиться писать файлы сценариев, научиться соотносить командные оболочки для разных OS.
* Освоить командное окружение для OS семейства Unix(утилиты из пакета GNU Core Utilities), и соответствующие им утилиты для OS семейства MS Windows.
### Задание:
*Вариант 73:*

Создать файл sh и bаt, который выполняет следующее: На вход пакетному файлу приходит абсолютный путь к файлу формата *.срр с кодом какой-либо программы. Проверить для указанного файла соответствие количества открывающихся И закрывающихся скобок. При соответствии скобок вывести в консоль сообщение “Баланс скобок соблюден, найдено Х пар скобок", при несоответствии - вывести сообщение “Баланс скобок не соблюден. Найдено Х открывающихся скобок иУ закрывающихся".


## Bat файл:
<p  align="center"></p>

```

@echo off
setlocal enabledelayedexpansion

if "%~1"=="" (
    echo Укажите путь к файлу .cpp
    exit /b 1
)

set "file=%~1"
set "open_brackets=0"
set "close_brackets=0"

for /f "delims=" %%i in ('type "%file%"') do (
    set "line=%%i"
    for /l %%j in (0,1,127) do (
        set "char=!line:~%%j,1!"
        if "!char!"=="(" set /a open_brackets+=1
        if "!char!"==")" set /a close_brackets+=1
    )
)

if %open_brackets%==%close_brackets% (
    echo Баланс скобок соблюден, найдено %open_brackets% пар скобок
) else (
    echo Баланс скобок не соблюден. Найдено %open_brackets% открывающихся скобок и %close_brackets% закрывающихся
)

```


## Sh файл:
<p  align="center"><</p>

```

#!/bin/bash

if [ -z "$1" ]; then
    echo "Укажите путь к файлу .cpp"
    exit 1
fi

file="$1"
open_brackets=0
close_brackets=0

while IFS= read -r line; do
    open_brackets=$((open_brackets + $(grep -o "{" <<< "$line" | wc -l)))
    close_brackets=$((close_brackets + $(grep -o "}" <<< "$line" | wc -l)))
done < "$file"

if [ "$open_brackets" -eq "$close_brackets" ]; then
    echo "Баланс скобок соблюден, найдено $open_brackets пар скобок"
else
    echo "Баланс скобок не соблюден. Найдено $open_brackets открывающихся скобок и $close_brackets закрывающихся"
fi

```



### Полезные сайты:
Подойдёт для тех, кто начал работать с bat файлами: [ссылка](https://help.reg.ru/support/servery-vps/oblachnyye-servery/rabota-s-serverom/kak-sozdat-bat-fayl-i-rabotat-s-nim#0).

Также можно почитать это: [batch script](https://habr.com/ru/sandbox/168937/).

А здесь можно почитать про sh файлы: [ссылка](https://selectel.ru/blog/tutorials/linux-bash-scripting-guide/).

### Вывод:
Файлы с расширением .bat и .sh являются скриптовыми файлами, которые используются для автоматизации задач в операционных системах Windows и Unix/Linux соответственно. 
Оба типа файлов являются мощными инструментами для автоматизации и управления системами, но они предназначены для различных операционных систем и имеют свои уникальные особенности и возможности. Знание их различий и умений написания может существенно упростить выполнение рутинных задач и улучшить производительность работы.
