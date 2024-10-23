# Работа с LaTeX 

Для выполнения Лабораторной работы № 1
Был использован Overleaf

Для регистрации можно перейти по ссылке:
[OverLeaf](https://www.overleaf.com)

*OverLeaf — онлайн редактор Latex* 

## Использованные пакеты Latex

Для корректной работы в LaTeX нужно подключить специальные пакеты, в данной работе были использованы следующие:

...
\usepackage{graphicx} % Required for inserting images
\usepackage{inputenc}
\usepackage{biblatex}
\usepackage{import}
\usepackage{scn} 
\usepackage{setspace}
\usepackage[russian]{babel} 
...

## Вставка фото и подпись под ней

...
\begin{figure}[h]
    \centering
    \includegraphics[width=\linewidth]{images/first.png} 
    \caption{Start page} 
    \label{Figure 1}
\end{figure}
...

## Ссылка на фото

...
\ref{Figure 1}
... 

## Римские цифры
Команда была изменена для нумерации заголовков с помощью римских цифр

...
\MakeUppercase{\romannumeral 5}
...
## Выделение текста

...
\textbf{text}
...

## Подчеркивание текста

...
\underline{text}
...

## Вертикальный отступ между строками 

...
\vspace{2 mm}
...

## Переход на новую страницу
...
\newpage
...

# Работа с Git'ом

Для выполнения Лабораторной №3
Были использованы Github & Git

*Github — веб-сервис хостинга проектов и их совместной разработки на базе Git*

[Github](https://github.com/)

*Git — система управления версиями*

[Git](https://git-scm.com/)
