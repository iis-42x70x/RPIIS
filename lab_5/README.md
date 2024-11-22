# Лабораторная работа 5

---

**Цель:** Освоить командные оболочки shell для OS семейства Unix и cmd для OS семейства MS Windows:
* изучить основные встроенные команды,
* научиться писать файлы сценариев,
* научиться соотносить командные оболочки для разных OS.
Освоить командное окружение для OS семейства Unix(утилиты из пакета GNU Core Utilities), и соответствующие им утилиты для OS семейства MS Windows.

## Задание:
Создать файл sh и bat, который выполняет следующее:
На вход пакетному файлу подается путь к папке и имя файла, который будет создан (как
параметры пакетного файла). В заданной папке найти все txt-файлы и записать их названия в
алфавитном порядке в файл с названием, переданным в качестве параметра пакетного файла.
После создания файла в консоль должно писать “New file has been created”

### Основные команды:
#### Для sh файла:
 * echo -e "\n Введите..."
 * read peremennaya
 * cd papka

#### Для bat файла:
 * set 
 * cd. >
 * echo Введите...

### Мой вариант выполненной работы.
**bat файл**
```
@echo off
D:
set /p path="Vvedite pyt k papke - "
echo %path%
set /p nfile="Vvedite nazvanie fila - "
echo %nfile%
cd. > %nfile%
For /R %path% %%i In (*.txt) Do (
   If Exist %%i (
        Echo %%i >> %nfile%
   )
)
echo New file has been created!
pause
```
Переменные: path - путь к папке, nfile - имя файла

**sh файл**

```
#!/bin/bash
echo -e "\n введите путь к папке: "
read path_to
echo -e "\n введите имя файла: "
read filiks
touch $filiks
find $path_to -iname "*.txt" | sort --output=$filiks
echo "New file has been created!"
```
Переменные: path_to - путь к папке, filiks - имя файла

Чтобы создать bat file необходимо создать файл в блокноте, затем при сохранении указать расширение bat и в поле тип файла указать **все файлы**.
Пример создания sh файла:

```
touch file.sh
nano file.sh
chmod +x file.sh
sh file.sh
```

