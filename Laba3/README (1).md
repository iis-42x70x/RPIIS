# ЛАБА 1

### ЦЕЛЬ

- Познакомиться с системой верстки текстов TeX, языком верстки TeX, издательской системой LaTeX.Выполнить вариант индивидуального задания.

### УСЛОВИЕ

- Сверстать три страницы научной статьи с использованием системы верстки текстов TeX.
- На странице [OSTIS Research Papers Collection (171-173)](https://proc.ostis.net/proc/Proceedings%20OSTIS-2024.pdf) необходимо взять доклад, соответствующий варианту индивидуального задания.

### [РЕЗУЛЬТАТ](lab1/LAB1.pdf)

# ЛАБА 3
### ЦЕЛЬ

- Познакомиться с программами git, освоить их программные аргументы.

### ВЫВОДЫ

- Научился на практике выполнять всевозможные действия с репозиторием и отвечать на теоретические вопросы из списка заданий.
- Получил практические навыки работы в консоли, использования консольных команд.

## ОТЧЁТ
1. git init <br>![1](Screenshots/1.png)
2. git status <br>![2](Screenshots/2.png)
3. последовательность коммитов, master   /   main <br>
4. git add {file} <br>![4](Screenshots/3.png)
5. git commit -m "comment" <br>![5](Screenshots/4.png)
6. git log <br>![7](Screenshots/5.png)
7. git config --list <br>![8](Screenshots/6.png)
8. git restore --staged {file}   /   git reset <br>![9](Screenshots/7.png)
9. git diff {file} <br>![10](Screenshots/8.png)
10. git checkout {file} <br>![11](Screenshots/9.png)
11. git add --all   /   git add . <br>![12](Screenshots/10.png)
12. git config --global <br>
13. git config --global [user.name](http://user.name) {name} <br>![14](Screenshots/11.png)
14. git branch <br>![15](Screenshots/12.png)
15. git branch {name} <br>![16](Screenshots/13.png)
16. git checkout {name} / git switch {name} <br>![17](Screenshots/14.png)
17. git checkout -b {name} <br>![18](Screenshots/15.png)
18. git branch -d {name} <br>![16](Screenshots/16.png)
19. git merge {name} <br>![16](Screenshots/17.png)
20. конфликт в случае слияния веток с разными изменениями в одном файле <br>
21. git merge → git status <br>![16](Screenshots/18.png)
22. устранить конфликт вручную изменив файл до удовлетворительного состояния <br>![16](Screenshots/18.png)
23. git checout {hash} <br>![16](Screenshots/19.png)
24. git rebase {name} <br>![16](Screenshots/20.png)
25. git rebase --abort <br>![16](Screenshots/21.png)
26. git rebase --skip <br>![16](Screenshots/22.png)
27. git push <br>![16](Screenshots/23.png)
28. git fetch → git merge  /  git pull <br>![16](Screenshots/24.png)
29. git pull origin {name} <br>![16](Screenshots/25.png)
30. git clone {name} {name} <br>![16](Screenshots/26.png)
31. git commit --amend -m “comment” <br>![16](Screenshots/27.png)
32. git rebase -i HEAD~n <br>
