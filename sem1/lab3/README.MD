# Лабораторная работа 1

### Цель:

Познакомиться с системой верстки текстов *TeX*, языком верстки *TeX*, издательской системой *LaTeX*. Выполнить вариант индивидуального задания.

### Основные команды

* `multicols`- разбиение страницы на части;
* `usepackag` - вставка плавающей картинки;
* `scn` - подключение одноименной библиотеки;
* `setcounter` - нумерация секций ;

### Перед началом работы необходимо подключить специальные пакеты
```
\documentclass[10pt, a4paper]{article}
\usepackage{hyperref}
    \usepackage[unicode, pdftex]{hyperref}
\usepackage[russian, english]{babel} % установка языков
\usepackage{graphicx} % вставка изображений
\usepackage{multicol} % деление на колонки
\usepackage{fancyhdr} % настройка колонтитулов
\usepackage{parskip} % настройка отступов абзаца
\usepackage{biblatex} % список литературы
\usepackage{mathtext} % Times New Roman
\usepackage{indentfirst} % отступ после заголовка секции
\usepackage{float} % плавающие картинки
\usepackage{titlesec} % настройка заголовков
\usepackage[margin=0.1cm]{caption} % настройка описаний
\captionsetup[figure]{font=scriptsize} % шрифт описания фигуры
\usepackage[left=2.5cm,right=2.5cm, top=2.1cm,bottom=2.5cm]{geometry} % макет страницы
\fancyhf{} % очистка колонтитулов
\cfoot{\textbf{\thepage}} % жирные номера страниц
\pagestyle{fancy}
\renewcommand{\headrulewidth}{0pt} % удаление линии header
\linespread{0.99} % межстрочный интервал
\setlength{\columnsep}{0.6cm} % расстояние между столбцами

\setlength{\parskip}{0pt} % вертикальный отступ абзаца
\setlength{\parindent}{0.5cm} % горизонтальный отступ абзаца
\setlength{\textfloatsep}{\theintvl\curtextsize} % отступ после картинок
\setcounter{page}{108} % нумерация страниц
\setcounter{figure}{7} % начальное значение нумерации фигур
\titleformat{\section}{\normalsize\centering}{\thesection. }{0cm}{}[] % стиль заголовков разделов
\titlespacing*{\section} % отступ возле секций
{0pt}{0.4cm}{0.3cm}
\renewcommand{\thesection}{\Roman{section}} % римские цифры
\setcounter{section}{6} % нумерация секций
```
### Создание списка
```
\begin{thebibliography}{13}
    \bibitem{book1} text1
    \bibitem{book2} text2
    \bibitem{book3} text3
\end{thebibliography}
```
как это будет выглядить
<p align="center">
 <img width="200px" src="skrin1.png" alt="qr"/>
</p>
 <p  align="center"><img src="images/skrin1.png" ></p>
![](skrin1.png)


### Добавление изображений с ссылкой
```
 \begin{figure}[H]
    \href{http://fkn.ktu10.com/?q=node/2906}{%
        \parbox{\textwidth}{
            \centering
            \includegraphics[width=16cm]{lw1_picture1.jpg}
            \caption{Methodology of machine learning model development for computer vision}
            \label{fig_8}
        }
    }
\end{figure}

```
как это будет выглядеть 
 <p  align="center"><img src="images/skrin2.png" ></p>

 
###  Так же могут прикодиться комманды
* `\par` - абзац
* `\newpage` - новая страница
* `\vspace{N}` - оступ на N


Более подробно с LaTex можно ознакомиться по [ссылке](https://www.overleaf.com/learn/latex/Learn_LaTeX_in_30_minutes)


# Лабораторная работа 3

### Цель:

Познакомиться с программами git, освоить их программные аргументы.
### Основные команды:

* `git init` - создание локального репозитория;
* `git add` - перенос изменений из рабочего каталога в раздел проиндексированных файлов;
* `git status` - прорверка статуса текущего репозитория;
* `git redase --skip ` - пропуск текущего конфликтного коммита и переход к следующему;

Более подробно с основными командами Git можно ознакомиться по [ссылке](https://habr.com/ru/articles/587558/).
    
 <p  align="center"><img src="images/pic.jpg" ></p>
