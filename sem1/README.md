# ЛАБА 1

### ЦЕЛЬ

- Познакомиться с системой верстки текстов TeX, языком верстки TeX, издательской системой LaTeX.Выполнить вариант индивидуального задания.

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
1. git init <br>![1](img/1.png)
2. git status <br>![2](img/2.png)  ![2](img/2_2.png)  ![2](img/2_3.png)
3. последовательность коммитов, master   /   main <br>
4. git add {file} <br>![4](img/3.png)
5. git commit -m "comment" <br>![5](img/4.png)
6. git commit -am "comment" <br>![6](img/5.png)
7. git log <br>![7](img/6.png)
8. git config --list <br>![8](img/7.png)
9. git restore --staged {file}   /   git reset <br>![9](img/8.png)
10. git diff {file} <br>![10](img/9.png)
11. git checkout {file} <br>![11](img/10.png)
12. git add --all   /   git add . <br>![12](img/11.png)
13. git config --global <br>
14. git config --global [user.name](http://user.name) {name} <br>![14](img/12.png)
15. git branch <br>![15](img/13.png)
16. git branch {name} <br>![16](img/16-1.png)
17. git checkout {name} / git switch {name} <br>![17](img/15.png)  ![17](img/image.png)
18. git checkout -b {name} <br>![18](img/18-1.png)
19. git branch -d {name} <br>![16](img/17.png)
20. git merge {name} <br>![16](img/20-1.png)
21. конфликт в случае слияния веток с разными изменениями в одном файле <br>
22. git merge → git status <br>![16](img/22-1.png)
23. устранить конфликт вручную изменив файл до удовлетворительного состояния <br>![16](img/22-1.png)
24. git checout {hash} <br>![16](img/24.png)
25. git rebase {name} <br>![16](img/25.png)
26. устранить конфликт → git add {file} → git rebase --continue <br>![16](img/26_1.png)  ![16](img/26_2.png)  ![16](img/26_3.png)
27. git rebase --abort <br>![16](img/27.png)
28. git rebase --skip <br>![16](imag/28.png)
29. git push <br>![16](img/29-1.png)
30. git fetch → git merge  /  git pull <br>![16](img/30.png)
31. git pull origin {name} <br>![16](img/31.png)
32. git clone {name} {name} <br>![16](img/32.png)
33. git commit --amend -m “comment” <br>![16](img/33.png)
34. git rebase -i HEAD~n <br>
35. git revert HEAD <br>![16](img/35-1.png)