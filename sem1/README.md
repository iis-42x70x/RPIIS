# ЛАБА 1

### ЦЕЛЬ
- Познакомиться с системой верстки текстов TeX, языком верстки TeX, издательской системой LaTeX.Выполнить вариант индивидуального задания.

## Основные библиотеки 
### УСЛОВИЕ

- Сверстать три страницы научной статьи с использованием системы верстки текстов TeX.
- На странице [OSTIS Research Papers Collection (246-248)](https://proc.ostis.net/proc/Proceedings%20OSTIS-2024.pdf) необходимо взять доклад, соответствующий варианту индивидуального задания.

### [РЕЗУЛЬТАТ](lab1/LAB1.pdf)

# ЛАБА 3
### ЦЕЛЬ

- Познакомиться с программами git, освоить их программные аргументы.

### ВЫВОДЫ

- Научился на практике выполнять всевозможные действия с репозиторием и отвечать на теоретические вопросы из списка заданий.
- Получил практические навыки работы в консоли, использования консольных команд.

## ОТЧЁТ
1. git init <br>![1](images/1.png)
2. git status <br>![2](images/2.png)
3. ветка в Git-это линия разработки. Обычно основной веткой является main или master.
4. echo Kirito>SAO.txt {file} <br>![4](images/4.png)
5. git commit -m "comment" <br>![5](images/5.png)
6. git commit -a -m "comment" <br>![6](images/6.png)
7. git log <br>![7](images/7.png)
8. git config --list <br>![8](images/8.png)
9. убрать файл из контекста   /   git reset <br>![9](images/9.png)
10. посмотреть изменения в файле по сравнению с последним коммитом <br>![10](images/10.png)
11. убрать изменения относительно последнего коммита из файла <br>![11](images/11.png)![11.1](images/11.1.png)  ![11.2](images/11.2.png) 
12. git add . <br>![12](images/12.png)
13. git config --global <br>
14. переписать имя пользователя [user.name](http://user.name) {name} <br>![14](images/14.png)
15. посмотреть существующие ветки <br>![15](images/15.png)
16. создание новой ветки <br>![16](images/16.png)
17. переключиться на другую ветку <br>![17](images/17.png)
18. git checkout -b {name} <br>![18](images/18.png)
19. git branch -d {name} <br>![16](images/19.png)
20. примержить изменения из указанной ветки в текущую <br>![16](images/20.png)
21. конфликт в случае слияния веток с разными изменениями в одном файле <br>
22. посмотреть в каких файлах конфликты <br>![16](images/22.png)
23. устранить конфликт  <br>![16](images/22.png)
25. ребазирование текущей ветки <br>![16](images/25.png)
27. git rebase --abort <br>![16](images/27.png)
28. git rebase --skip <br>![16](images/28.png)
29. отправить изменения из локального репозитория для указанной ветки в удалённый репозиторий <br>![16](images/29.png)
30. git fetch <br>![16](images/30.png)
31. git fetch origin master {name} <br>![16](images/31.png)
32. git clone {name} {name}(создание копии репозитория) <br>![16](images/32.png)
33. git rm/mv {name} (удаление/переименование файла) <br>![16](33.png)
34. git rebase -i HEAD~n <br>
35. git revert HEAD <br>![16](images/35.png)
34. git rebase -i HEAD~n <br>
35. git revert HEAD <br>![16](35.png)
