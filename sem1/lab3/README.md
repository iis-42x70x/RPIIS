# Лабораторная 1 

### Цель:
Изучить систему верстки текстов *TeX*, язык верстки *TeX* и издательскую систему *LaTeX*. Выполнить индивидуальное задание по выбранному варианту.

### Перед началом работы необходимо подключить специальные пакеты
```
\documentclass[10pt, a4paper]{article}%создание базы , шрифт 10

\usepackage{graphicx} %подключение пакета для картинок
\usepackage{multicol} %подключение библиотеки для разделения текста на колонки
\usepackage{amsmath}

\usepackage[colorlinks=true, allcolors=blue]{hyperref}
\graphicspath{ {images/} }
\usepackage{lipsum}
\usepackage{setspace}%подключение бибилотеки для отступов между строками
\usepackage{fancyhdr}
\usepackage{float}
\usepackage[left=2.1cm,right=2.1cm, top=2.1cm,bottom=2.2cm]{geometry} % создание шаблона с определенными отступами
\setlength{\columnsep}{0.45cm} %расстояние между двумя колонками с текстами
\usepackage{fancyhdr}
\cfoot{\textbf{\thepage}} % номер страницы становится жирным
\pagestyle{fancy}
\setcounter {page}{117}% установление номера страницы
\renewcommand{\headrulewidth}{0pt} % убрать разделительную линиб в верхнем колонтитуле
\newcommand{\RomanNumeralCaps}[1]
    {\MakeUppercase{\romannumeral #1}}

```
### Создание списка
```
\begin{enumerate}[label={[\arabic*]}]

    \bibitem{book1} Book №1

    \bibitem{book2} Book № 2

    \bibitem{book3} Book № 3
    
\end{enumerate}
```


### Основыне комманды
* `\par` - абзац
* `\begin{tabular} ... \end{tabular}` -  создает таблицу
* `\bibitem{book1} ` - автомотическое создание нумирации списка
* `\newpage` - новая страница
* `\setcounter{page}...` - автомотическое  начало нумирации страниц с заданного номера
