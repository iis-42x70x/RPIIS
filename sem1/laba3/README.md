<h1 align="center"> Лабораторная работа №1 </h1>

### Цель работы: 
Познакомиться с системой верстки текстов TeX, языком верстки TeX, издательской системой LaTeX.Выполнить вариант индивидуального задания.

## Задание:
Сверстать три страницы научной статьи с использованием системы верстки текстов TeX.
[На странице](https://proc.ostis.net/proc/Proceedings%20OSTIS-2024.pdf) необходимо взять доклад, соответствующий варианту индивидуального задания.
Доклад представлен в форме статьи в формате *.pdf.

### Результат выполненной работы:
В результате этой работы должен получиться один pdf файл и один tex файл с исходниками статьи.

### Для работы с Latex нужно подключить специальные пакеты:
```
\documentclass[10pt, a4paper]{article}

\usepackage{CJKutf8}
\usepackage[russian, english]{babel}
\newcommand{\RomanNumeralCaps}[1]
    {\MakeUppercase{\romannumeral #1}}
\usepackage[utf8]{inputenc}
\usepackage{multicol} % Колонки
\usepackage{setspace} % Межстрочный интервал
\usepackage{ragged2e} % Выравнивания текста по ширине в документе.
\usepackage{fancyhdr} % Настройки верхнего и нижнего колонтитулов в документе.
\usepackage{titlesec} % Стилей заголовков разделов в документе.
\usepackage{enumitem} % Настройки списков в документе.
\usepackage{graphicx}
\usepackage{float} % "Плавающие" картинки
\usepackage{wrapfig} % Обтекание фигур (таблиц, картинок и прочего)
\usepackage[left=1.9cm,right=1.9cm, top=2.2cm,bottom=2.5cm]{geometry}
```

### Работа со списком:
```
\begin{itemize}
    \item according to the WHO, in 2020, GI diseases are the cause of death for more than 4 million people worldwide;
    \item according to studies conducted in different countries, GI diseases account for up to 25\% of all reasons for visits to general practitioners;
    \item some of the most common GI diseases include peptic ulcer disease, gastric and duodenal ulcers, gastritis, colitis, irritable bowel syndrome (IBS), gallstones, pancreatitis, and GI cancer;
\end{itemize}
```

### Вставка картинок: 
```
\begin{figure}[h]
    \center{\includegraphics[width=0.88\linewidth]{fourth.jpg}}
    \caption{Fragment of medical record ontology}
    \label{ris:fourth}
\end{figure}
```

### Pабота с римскими цифрами:
```
\begin{center}
    \RomanNumeralCaps{6}. Conclusion 
\end{center}
```

<h1 align="center"> Лабораторная работа №3 </h1>

### Цель работы: 
Познакомиться с программами git, освоить их программные аргументы.

### Задание: 
Получить практические навыки работы в консоли, использования консольных команд.
Для сдачи работы необходимо выполнить все задания и составить отчёт с тем, как эти задания выполнялись.
[Задания по гиту](https://docs.google.com/document/d/1pkqZWOlte5j6PuPpz7w03tPkw64ctuUwELoI-qctYVQ/edit?tab=t.0)

## Основные команды:
* init - для создания локального репозитория в текущей папке;
* add - добавить файл к отслеживанию;
* commit - создать коммит;
* remote add - для добавления удалённого репозитория;
* push - для отправления данных в удалённый репозиторий.
Более подробно с основными командами Git можно ознакомиться по [ссылке](https://habr.com/en/articles/587558/)
