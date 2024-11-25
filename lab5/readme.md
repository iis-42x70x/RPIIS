# Написание скриптов Win/Linux

В рамках ЛР №5 необходимо создать исполняемый файл в соответствии с заданным вариантом.

49 Создать файл sh и bat, который выполняет следующее: 
На вход пакетному файлу приходит два числа (как параметры пакетного файла). 
Создать файл, в который записать все имена процессов в алфавитном порядке, размер используемой памяти 
которых находится в заданном диапазоне.

## Batch file 

```
chcp 1252
@echo off
set /p Start=Start: 
set /p End=End:
echo Name ------------ RAM  > bat.txt
for /f "tokens=1,5" %%a in ('tasklist /FI "MEMUSAGE ge %Start%" /FI "MEMUSAGE le %End%" ^| findstr /V "Image" ^| findstr /V "=====" ^| sort') do (	
        echo %%a %%b >> bat.txt
    )
notepad bat.txt
exit
```
### Тестовый результат (bat.txt)

Значение в КБ
Start = 0
End = 10000

```
Name ------------ RAM  
cmd.exe 4 892 
cmd.exe 4 688 
CompPkgSrv.exe 8 720 
csrss.exe 5 144 
csrss.exe 6 220 
findstr.exe 4 088 
findstr.exe 4 092 
fontdrvhost.exe 7 712 
fontdrvhost.exe 2 532 
Microsoft.Media.Player.ex 1 468 
services.exe 9 200 
SgrmBroker.exe 7 460 
smss.exe 1 092 
sort.exe 3 336 
svchost.exe 8 224 
svchost.exe 7 036 
svchost.exe 9 772 
svchost.exe 5 200 
svchost.exe 6 068 
svchost.exe 9 872 
svchost.exe 8 044 
svchost.exe 8 136 
svchost.exe 7 612 
svchost.exe 6 320 
svchost.exe 7 856 
svchost.exe 9 908 
svchost.exe 8 248 
svchost.exe 5 932 
svchost.exe 7 684 
svchost.exe 8 072 
svchost.exe 9 188 
svchost.exe 7 508 
svchost.exe 8 444 
svchost.exe 5 664 
svchost.exe 6 392 
svchost.exe 9 552 
svchost.exe 6 404 
svchost.exe 8 036 
svchost.exe 7 676 
svchost.exe 7 844 
svchost.exe 7 876 
svchost.exe 7 196 
svchost.exe 7 040 
svchost.exe 9 140 
svchost.exe 5 404 
svchost.exe 5 716 
svchost.exe 9 800 
svchost.exe 7 056 
svchost.exe 9 372 
svchost.exe 7 716 
svchost.exe 8 764 
svchost.exe 8 428 
System 140 
System Services 
SystemSettings.exe 3 872 
tasklist.exe 9 324 
UserOOBEBroker.exe 9 544 
wininit.exe 6 636 
```

### Описание программы 
1. **Запрос диапазона памяти**
   - Программа предлагает ввести начальное (`Start`) и конечное (`End`) значения объёма памяти в килобайтах.
   
2. **Фильтрация**
   - Используется команда `tasklist`, чтобы получить список процессов Windows 10/11.
   - Применяются фильтры для отбора процессов, потребляющих память в указанном диапазоне.
   - Лишние строки с шаблонами `Name` и `=====` удаляются с помощью команд `findstr`.
   - Результаты сортируются по имени процесса.

3. **Сохранение результата**
   - Список процессов, подходящих под заданные условия, записывается в файл `bat.txt` в формате:
     ```
     Name ------------ RAM
     process_name      memory_usage
     ```

4. **Открытие файла**
   - Файл `bat.txt` автоматически открывается в Notepad.
   
 ## Shell file 
 
 ```
read -p "Start" Start
read -p "End" End
(ps aux | awk -v Start=$Start -v End=$End '{if ($4 >= Start && $4 <= End) print substr($11,2), $4}' | sed 's/]//g' | sort) > sh.txt
 ```

## Тестовый результат (sh.txt)

Значения в %
Start = 0
End = 0.5

```
dm-session-worker 0.1
lib/systemd/systemd 0.1
lib/systemd/systemd-hostnamed 0.1
lib/systemd/systemd-journald 0.3
lib/systemd/systemd-localed 0.1
lib/systemd/systemd-logind 0.1
lib/systemd/systemd-timesyncd 0.1
lib/systemd/systemd-udevd 0.1
sbin/init 0.2
usr/bin/dbus-daemon 0.1
usr/bin/dbus-daemon 0.1
usr/bin/gjs 0.4
usr/bin/gjs 0.4
usr/bin/gnome-keyring-daemon 0.1
usr/bin/ibus-daemon 0.2
usr/bin/pipewire 0.2
usr/bin/pipewire-pulse 0.1
usr/bin/wireplumber 0.3
usr/libexec/accounts-daemon 0.1
usr/libexec/at-spi2-registryd 0.1
usr/libexec/at-spi-bus-launcher 0.1
usr/libexec/colord 0.2
usr/libexec/dconf-service 0.1
usr/libexec/evolution-addressbook-factory 0.5
usr/libexec/evolution-calendar-factory 0.4
usr/libexec/gdm-wayland-session 0.1
usr/libexec/geoclue 0.2
usr/libexec/gnome-session-binary 0.3
usr/libexec/gnome-session-binary 0.3
usr/libexec/gnome-session-ctl 0.1
usr/libexec/gnome-shell-calendar-server 0.3
usr/libexec/goa-identity-service 0.1
usr/libexec/gsd-a11y-settings 0.1
usr/libexec/gsd-color 0.4
usr/libexec/gsd-datetime 0.2
usr/libexec/gsd-disk-utility-notify 0.1
usr/libexec/gsd-housekeeping 0.1
usr/libexec/gsd-keyboard 0.4
usr/libexec/gsd-media-keys 0.5
usr/libexec/gsd-power 0.4
usr/libexec/gsd-printer 0.2
usr/libexec/gsd-print-notifications 0.2
usr/libexec/gsd-rfkill 0.1
usr/libexec/gsd-screensaver-proxy 0.1
usr/libexec/gsd-sharing 0.2
usr/libexec/gsd-smartcard 0.2
usr/libexec/gsd-sound 0.1
usr/libexec/gsd-usb-protection 0.1
usr/libexec/gsd-wacom 0.4
usr/libexec/gvfs-afc-volume-monitor 0.1
usr/libexec/gvfsd 0.1
usr/libexec/gvfsd-fuse 0.1
usr/libexec/gvfsd-metadata 0.1
usr/libexec/gvfsd-recent 0.1
usr/libexec/gvfsd-trash 0.1
usr/libexec/gvfs-goa-volume-monitor 0.1
usr/libexec/gvfs-gphoto2-volume-monitor 0.1
usr/libexec/gvfs-mtp-volume-monitor 0.1
usr/libexec/gvfs-udisks2-volume-monitor 0.2
usr/libexec/ibus-engine-simple 0.1
usr/libexec/ibus-extension-gtk3 0.5
usr/libexec/ibus-memconf 0.1
usr/libexec/ibus-portal 0.1
usr/libexec/ibus-x11 0.3
usr/libexec/power-profiles-daemon 0.1
usr/libexec/realmd 0.1
usr/libexec/switcheroo-control 0.1
usr/libexec/udisks2/udisksd 0.2
usr/libexec/upowerd 0.1
usr/libexec/xdg-desktop-portal 0.2
usr/libexec/xdg-desktop-portal-gnome 0.4
usr/libexec/xdg-desktop-portal-gtk 0.4
usr/libexec/xdg-document-portal 0.1
usr/libexec/xdg-permission-store 0.1
usr/lib/polkit-1/polkitd 0.1
usr/sbin/cups-browsed 0.2
usr/sbin/cupsd 0.1
usr/sbin/gdm3 0.1
usr/sbin/ModemManager 0.2
usr/sbin/NetworkManager 0.3
```

## Описание программы 

1. **Запрос диапазона памяти у пользователя**
   - Программа предлагает ввести начальное (`Start`) и конечное (`End`) значения использования памяти (в процентах).

2. **Фильтрация процессов**
   - Используется команда `ps aux`, чтобы получить список всех запущенных процессов с их использованием памяти.
   - Применяется `awk` для фильтрации процессов по значению памяти:
     - Сравниваются значения `Start` и `End` с колонкой `%MEM` (четвёртая колонка).
   - Из строки извлекается имя процесса (без квадратных скобок) и значение памяти.

3. **Сортировка и запись**
   - Результат сортируется с помощью команды `sort`.
   - Отфильтрованные данные сохраняются в файл `sh.txt`.








