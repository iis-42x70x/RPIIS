# Лабораторная работа 5

---

**Цель:** Освоить командные оболочки shell для OS семейства Unix и cmd для OS семейства MS Windows:
* изучить основные встроенные команды,
* научиться писать файлы сценариев,
* научиться соотносить командные оболочки для разных OS.
Освоить командное окружение для OS семейства Unix(утилиты из пакета GNU Core Utilities), и соответствующие им утилиты для OS семейства MS Windows.

## Задание:
На вход пакетному файлу приходит относительный путь к папке (как параметр пакетного файла). Если такой папки нет, то писать “Данной папки нет” и завершить выполнение программы. Папка должна содержать текстовые файлы с различным содержимым. Если число файлов четное, то создать файл, в котором будет содержаться список имен файлов указанной папки, отсортированный по времени создания по убыванию. Если число файлов нечетное - создать файл, в котором будет содержаться список имен файлов указанной папки, отсортированный по увеличению размера



### Основные команды:
#### Для sh файла:
 * 
 *
 * 

#### Для bat файла:
 * 
 * 
 * 

### Мой вариант выполненной работы.
**bat файл**
```
@echo off
setlocal enabledelayedexpansion
set /p path= "Enter the folder path: "
echo %path%
if not exist "%path%" (
echo Folder does not exist.
exit /b
)
cd /d "%path%"
set count=0
for %%f in ("%path%\*.txt") do (
    set /a count+=1
)
if %count% lss 1 (
    echo There are no text files in the folder
    exit /b
) else (
    echo In folder "%path%" found %count% files
)
set /a chet=count %% 2
if %chet%==0 (
dir /T:C /O:-D "*.txt" > files_sorted_by_date.txt
echo List of files saved in files_sorted_by_date.txt
)
else (
dir /O:S "*.txt" > files_sorted_by_size.txt
echo List of files saved in files_sorted_by_size.txt
)
endlocal
pause
```

**sh файл**

```
#!/bin/bash
read -p "Enter the folder path: " path
echo "Path: $path"
if [ ! -d "$path" ]; then
    echo "Folder does not exist"
    exit 1
fi
cd "$path" || exit 1   
count=0
for f in *.txt; do
    if [ -e "$f" ]; then  
        count=$((count + 1))
    fi
done
if [ "$count" -lt 1 ]; then
    echo "There are no text files in the folder"
    exit 1
else
    echo "In folder \"$path\" found $count files"
fi
chet=$((count % 2))
if [ "$chet" -eq 0 ]; then
    ls -lt --time=creation *.txt > sorted_files.txt  
    echo "File list saved to sorted_files.txt"
else
    ls -S *.txt > files_sorted_by_size.txt  
    echo "File list saved to files_sorted_by_size.txt"
fi
```
**Для создания bat file** необходимо создать файл в блокноте, затем, когда сохраненяю указать расширение bat и в поле тип файла указать все файлы.

**Для создания sh файла:**

```
nano file.sh
```

Для запуска его (перед запуском стоит сохранить(CTRL + O); затем Enter; затем выходим из sh файла (CTRL + X) ):
```
bash file.sh
```
