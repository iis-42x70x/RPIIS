# Лабораторная работа 5

---

**Цель:** Освоить командные оболочки shell для OS семейства Unix и cmd для OS семейства MS Windows:
* изучить основные встроенные команды,
* научиться писать файлы сценариев,
* научиться соотносить командные оболочки для разных OS.
Освоить командное окружение для OS семейства Unix(утилиты из пакета GNU Core Utilities), и соответствующие им утилиты для OS семейства MS Windows.

## Задание:
Создать файл sh и bat, который выполняет следующее: 
На вход пакетному файлу приходит относительный путь к папке
(как параметр пакетного файла). Если такой папки нет, то писать “Данной папки нет” и завершить выполнение программы.
Папка должна содержать другие папки (несколько уровней вложенности) и файлы. Отсортировать имена папок,
содержащихся в указанной в порядке возрастания количества находящихся в них файлов,
результат вывести в файл result.txt 

### Основные команды:
#### Для sh файла:
 * echo "..."
 *  exit
 * sort

#### Для bat файла:
 * set  
 * exist
 * echo

### Мой вариант выполненной работы.
**bat файл**
```
@echo off
setlocal enabledelayedexpansion

REM Proverka nalichiya parametra
if "%~1"=="" (
    echo Vvedite imya papki kak parametr.
    goto end
)

if not exist "%~1" (
    echo Dannoy papki net.
    exit /b 1
)

REM Initializiruem peremennye
set "folder=%~1"
set "resultfile=result.txt"

REM Obnulyaem fail rezultatov
if exist %resultfile% del %resultfile%

REM PowerShell dlya sortirovki podpapok
powershell -Command ^
    "Get-ChildItem -Directory -Path '%folder%' | Select-Object -ExpandProperty Name | Sort-Object Length | Out-File '%resultfile%'"



:end
pause


popd
endlocal


```
Переменные: folder - название папки

**sh файл**

```
#!/bin/bash

if [ -z "$1" ]; then
    echo "Vvedite imya papki kak parametr."
    exit 1
fi

folder="$1"
if [ ! -d "$folder" ]; then
    echo "Dannoy papki net."
    exit 1
fi

> result.txt
for subfolder in "$folder"/*/; do
    subfolder_name=$(basename "$subfolder")
    length=${#subfolder_name}
    echo "$length $subfolder_name" >> result.txt
done

sort -n result.txt | awk '{print $2}' > temp.txt && mv temp.txt result.txt


```
Переменные: folder - название папки, subfolder_name  -  текст содержащийся в названии 

Чтобы создать bat file необходимо создать файл в блокноте или любом другом текстовом редакторе, затем при сохранении указать расширение bat и в поле тип файла указать **все файлы**.
Чтобы создать sh file необходимо создать файл в блокноте или любом другом текстовом редакторе, затем при сохранении указать расширение sh.
Далее в командной строке необходимо сделать пакетный файл исполняемым (используем команду chmod +x file.sh)
