<h1 align="center"> Работа с Latex</h1>
<p  align="center"><img src="Логотип.png" ></p>
Для регистрации можно перйти по ссылке

<a href="https://www.overleaf.com/">OverLeaf</a>

Для начала проекта нужно нажать на кнопку
<p  align="center"><img src="images/10.png" ></p>

### Для работы с Latex нужно подключитьспециальные пакеты
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
 а вот как выглядит это в **pdf**
 <p  align="center"><img src="images/3.png" ></p>

### Вставка картинок
```
\begin{center}
    \begin{figure}[H]
    \centering
    \includegraphics[width=4.35cm]{figs/Picture.png}
    \caption{Figure 5.The first variant of mutual placement of objects.}
    \label{fig:first}
\end{figure}
\end{center}
```
 а вот как выглядит это в **pdf**

  <p  align="center"><img src="images/zzzzzzzzzzzz.jpg" width=400px height=300px></p>

 ### Работа с секциями  и римскими цифрами
 ```
 \section*{\fontsize{10}{11}\selectfont\textnormal{
  \RomanNumeralCaps{5}. Conclusion }
}
```
<p align="center"> а вот как выглядит это в <b>pdf</b>
</p>
 <p  align="center"><img src="images/25.png" width=700px height=200px ></p>
 
 ## Вот так выглядит документ при его редактировании
  <p  align="center"><img src="images/21.png"  ></p>

## Цель: работа с Git и GitHub, а также научиться оформлять MarkDown  файлы

 <p  ><img src="images/555.png"  ></p>
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
