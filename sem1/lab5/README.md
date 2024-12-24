<h1 align="center">Лабараторная работа №5</h1>

## Цели:

* **Ознакомиться с теоритичесими сведениями о скриптах** 
* **Выполнить выданный вариант лабораторной работы**

## Вариант:
Мне дали вариант прочесть все поддериктории директории указанной пользователем и найти все .txt файлы, далее слова в них, начинающие на буквы v/V, далее настроить запись этих слов в результирующий файл result.txt.
## Выполнение лабораторной работы


**Скрипт, или сценарий** — это небольшая программа, которая выполняет конкретную задачу. Обычно у скриптов нет своего визуального интерфейса: это код, который запускается по команде, отрабатывает, совершает нужные действия и завершается. Обычно такие программы нужны, чтобы автоматизировать повторяющиеся действия.

### Для написания скриптов я использовал два языка:
###  Вот вариант кода Sh


```
#!/bin/bash

read -p "Введите название папки для поиска: " folder_name

SEARCH_PATH="/mnt/windows"

if [ -z "$folder_name" ]; then
    echo "Имя папки не указано. Попробуйте снова."
    exit 1
fi

folder_path=$(find "$SEARCH_PATH" -type d -iname "$folder_name" 2>/dev/null | head -n 1)

if [ -n "$folder_path" ]; then
    echo "Папка с названием '$folder_name' найдена."
    echo "Поиск .txt файлов..."

    > result.txt

    find "$folder_path" -type f -name "*.txt" 2>/dev/null | while read -r file; do
        if [ -f "$file" ]; then
            found_words=$(grep -E -o '\b[Vv][a-zA-Z]*\b' "$file" | sort | uniq)

            if [ -n "$found_words" ]; then
                echo "Файл: $file" >> result.txt
                echo "$found_words" >> result.txt
            else
                echo "Нет слов, начинающихся на 'v' или 'V' в файле $file." >> result.txt
            fi
        else
            echo "Файл $file не найден или нет доступа к нему." >> result.txt
        fi
    done

    echo "Результаты записаны в файл result.txt."
else
    echo "Папка с названием '$folder_name' не найдена."
fi
```

### А вот  этот же скрипт только для **Bat**

```
@echo off
setlocal enabledelayedexpansion

:: Путь к базовой директории
set "BASEPATH=C:\Users\Николай\source\repos\student\pioivis\lab5"

:: Запрос имени искомой папки
set /p DIRNAME=Enter folder name: 

:: Проверяем, существует ли директория
if not exist "%BASEPATH%\%DIRNAME%" (
    echo Folder "%DIRNAME%" doesnt found %BASEPATH%.
    pause
    goto :EOF
)

:: Удаляем предыдущий result.txt, если он существует
if exist "%BASEPATH%\result.txt" del "%BASEPATH%\result.txt"

:: Перебираем все txt файлы в указанной папке
for %%f in ("%BASEPATH%\%DIRNAME%\*.txt") do (
    :: Читаем каждый файл построчно
    for /f "usebackq delims=" %%L in ("%%f") do (
        :: Разбиваем строку на отдельные слова
        for %%W in (%%L) do (
            set "word=%%W"
            set "firstChar=!word:~0,1!"
            :: Проверяем первый символ слова без учёта регистра
            if /i "!firstChar!"=="v" (
                echo %%W>>"%BASEPATH%\result.txt"
            )
        )
    )
)

echo complete.
pause

```
### Область применения

* **Сейчас скрипты используются почти в любой области разработки. В первую очередь это веб: одни скрипты отвечают за выполнение действий на «внешней» стороне сайта, другие — занимаются отправкой и обработкой данных с сервера и обратно.**

* **Скрипты можно использовать для автоматизации повседневных действий в любой отрасли. Если речь о разработке — написанный под конкретные задачи сценарий может обрабатывать данные, рисовать график на основе входной информации, связываться с сервером, анимировать дизайн сайта или делать что-то еще. Но и в офисной работе с документами, и в рекламе есть место скриптам. Их пишут программисты или сами работники офиса.**



## Вывод:
 В результате данной лабораторной работы мне  удалось выполнить свой вариант на **bat** и **sh**, а также 
 узнать основную информацию о скриптах.

 ## Используемые исочники:

 * <a href="https://habr.com/ru/articles/540076/">Habr</a>

 * <a href="https://ru.wikipedia.org/wiki/Bash">Википедия</a>

 * <a href="https://help.reg.ru/support/servery-vps/oblachnyye-servery/rabota-s-serverom/kak-sozdat-bat-fayl-i-rabotat-s-nim">Per.py</a>
