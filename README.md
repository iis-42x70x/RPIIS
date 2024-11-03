<h1 align="center"> Работа с Latex</h1>
Для регистрации можно перйти по ссылке

<a href="https://www.overleaf.com/">OverLeaf</a>

Для начала проекта нужно нажать на кнопку
<p  align="center"><img src="Images/Начало проекта.jpg" ></p>

### Пакеты для работы с Latex
```
\documentclass[10pt, a4paper]{article}%создание базы , шрифт 10
\usepackage{graphicx} %подключение пакета для картинок
\usepackage{multicol} %подключение библиотеки для разделения текста на колонки
\usepackage{amsmath}
\usepackage[colorlinks=true, allcolors=blue]{hyperref}
\graphicspath{ {images/} }
\usepackage{setspace}%подключение бибилотеки для отступов между строками
\usepackage[left=2.1cm,right=2.1cm, top=2.1cm,bottom=2.2cm]{geometry} % создание шаблона с определенными отступами
\setlength{\columnsep}{0.45cm} %расстояние между двумя колонками с текстами
\usepackage{fancyhdr}
\cfoot{\textbf{\thepage}} % номер страницы становится жирным
\pagestyle{fancy}
\setcounter {page}{1}% установление номера страницы
\newcommand{\RomanNumeralCaps}[1]
{\MakeUppercase{\romannumeral #1}}

```
### Работа со списками
```
\begin{itemize}
\item Filtering irrelevant parts of an sc-text stored in the knowledge base;
\item Linearization of a non-linear text that is a certain graph structure within the knowledge base; 
\item Translation of a linearized sc-text into a natural language.
\end{itemize}
```
Вот так это выглядит в **pdf**
 <p  align="center"><img src="Images/Cписок.jpg" ></p>

### Вставка картинок
```
\centering
\includegraphics[width=\linewidth]{zzzzzzzzzzzz.jpg}
\caption{\small Figure 1. An example of a structure prior to filtering.}
```
Вот так это выглядит в **pdf**

  <p  align="center"><img src="Images/Фото 1.jpg" width=400px height=300px></p>

 ### Работа римскими цифрами
 ```
\centerline{\MakeUppercase{\romannumeral 3}. Introduction}
```
Вот так это выглядит в **pdf**
</p>
 <p  align="center"><img src="Images/Римские цифры.jpg" width=600px height=200px ></p>
 
 ## Вот так выглядит документ при его редактировании
  <p  align="center"><img src="Images/Обзор.jpg"></p>

## Цель: работа с Git и GitHub, а также научиться оформлять MarkDown  файлы

 <p  ><img src="Images/555.png"  ></p>
 <p><b>Git</b> (произносится «гит») — распределённая система управления версиями.</p>

 [Git](https://git-scm.com/)

 <a href="https://github.com/">GitHub</a>
 
 ### Основные команды:

<p>1. Проверка стасуса</p>

 ```
 git status
 ```
<p>2. Добавление файлов</p>

```
git add .
```
<p>3. Создание коммита</p>

```
git commit -m "message"
```
<p>4. Загрузка на определенную ветку в GitHub</p>

```
git push origin <название ветки>
```
### вот рессурсы для обучения командам Git
<a href="https://habr.com/ru/articles/541258/">Работа с git</a>
