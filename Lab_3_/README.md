# Работа в LaTeX 
Для редактирования кода LaTeX можно использовать сайт [Overleaf](https://www.overleaf.com "Главная страница Overleaf")
После регистрации откроется страница с проектами. Для создания нового документа с помощью LaTeX нужно нажать соответствующую кнопку
![Главная страница Overleaf](https://github.com/iis-42x70x/RPIIS/blob/Бурбас_Д/Lab_3_/images_latex/beginning_latex.png)
Когда вы создали новый проект вот так выглядит интерфейс
![Интерфейс редактирования документа](https://github.com/iis-42x70x/RPIIS/blob/Бурбас_Д/Lab_3_/images_latex/editing_latex.png)
В Overleaf также присутствует очень удобная функция: вы можете кликнуть по тексту в окне предпросмотра и Overleaf покажет как этот текст реализован в коде LaTeX в Окне редактирования кода.
## Подключение пакетов
Для комфортной работы с LaTeX рекомендуется подключить специальные пакеты
(Часть кода в которой пишется подключение пакетов и команды, задающие свойства всему документу, называется ***преамбулой***)
```
\documentclass{article} % Определяет тип документа (article)
\usepackage{graphicx} % Подключает пакет для вставки изображений
\usepackage{multicol} % Позволяет создавать многостолбцовые макеты
\usepackage[utf8]{inputenc} % Устанавливает кодировку UTF-8 для ввода текста
\usepackage[T2A]{fontenc} % Определяет кодировку шрифтов для кириллицы
\usepackage[russian,english]{babel} % Позволяет использовать русский и английский языки, включая соответствующие правила переносов
\usepackage{import} % Позволяет импортировать файлы из других директорий
\usepackage{amsmath} % Предоставляет расширенные возможности для работы с математическими формулами
\usepackage{scn} 
\usepackage{float} % Позволяет управлять позиционированием плавающих объектов (например, фигур)

\usepackage{subfig} % Позволяет размещать подфигуры в одной фигуре
\usepackage{fancyhdr} % Подключает пакет для кастомизации колонтитулов
\usepackage{setspace} % Позволяет изменять межстрочное расстояние
\usepackage[numbers]{natbib} % Подключает пакет для библиографий, использующий числовые ссылки
\usepackage[top=20mm,columnsep=15pt]{geometry} % Устанавливает параметры полей страницы: верхнее поле и расстояние между колонками
\usepackage{titlesec} % Позволяет изменять форматирование заголовков секций
\usepackage{titling} % Позволяет настраивать заголовок документа
```
## Вставка картинок
```
\begin{figure}[H]
    \centering
    \includegraphics[width=0.7\linewidth]{images/Figure7.jpeg}
    \caption{\small Definition areas of Not3 and Yes3 classes.}
    \label{fig:enter-label}
\end{figure}
```
Вот как выглядит это в pdf
![Пример картинки LaTeX](https://github.com/iis-42x70x/RPIIS/blob/Бурбас_Д/Lab_3_/images_latex/figure_example.png)
## Создание нумерации заголовков секций римскими цифрами
Для этого необходимо написать в преамбуле следующую команду
```
\renewcommand\thesection{\Roman{section}}
```
Теперь при объявлении секции будет использоваться нумерации римскими числами
```
\section{Introduction}
```
Вот как выглядит это в pdf
![Пример секции Introduction](https://github.com/iis-42x70x/RPIIS/blob/Бурбас_Д/Lab_3_/images_latex/roman_section_example1.png)
```
\section{The cognitive abilities level and the interoperable behaviour. State of art}
Вот как выглядит это в pdf
```
![Пример секции The cognitive abilities](https://github.com/iis-42x70x/RPIIS/blob/Бурбас_Д/Lab_3_/images_latex/roman_section_example2.png)
## Работа с библиографиями
```
\begin{thebibliography}{26}
\vspace{2.5mm}
\setlength{\itemsep}{0pt}
\bibitem{item1} D. Gurvits, A. N’yudzhent, F. Khalper Prosto o bol’shikh dannykh
[Big Data For Dummies], Moskow, Eksmo. 2015. 400 p.
\bibitem{item2} A. Vaigend, Big Data. Vsya tekhnologiya v odnoi knige [Big Data.
All the technology in one book], Moskow, Eksmo. 2018. 384 p.
\bibitem{item3} N. Marts, Dzh. Uorren Bol’shie dannye: printsipy i praktika postroeniya masshtabiruemykh sistem obrabotki dannykh v
real’nom vremeni [Big Data: Principles and best practices of
scalable realtime data systems], Moskow, OOO “I.D. Vil’yams”,
2016. 368 p.
\bibitem{item4} D. Silen, A. Meisman, M. Ali Osnovy Data Science i Big
Data. Python i nauka o dannykh [Introducing Data Science: Big
Data, Machine Learning, and more, using Python tools], Saint
Petersburg, Piter. 2017. 336 p.
\bibitem{item5} A.A. Barsegyan, M.S. Kupriyanov, I.I. Kholod Analiz dannykh i
protsessov [Data and Process Analysis], Saint Petersburg, BKhVPeterburg. 2009. 512 p.
\bibitem{item6} A.G. D’yakonov Analiz dannykh, obuchenie po pretsedentam,
logicheskie igry, sistemy WEKA, RapidMiner i MatLab [Data
analysis, learning by precedents, logic games, WEKA, RapidMiner and MatLab systems], Moskow, Izdatel’skii otdel fakul’teta
VMK MGU imeni M.V. Lomonosova. 2010. 278 p.
\bibitem{item7} Dzh. Gras Data Science. Nauka o dannykh s nulya [Data Science
from Scratch], Saint Petersburg, BKhV-Peterburg. 2017. 416 p.
\bibitem{item8} K. Fukunaga Vvedenie v statisticheskuyu teoriyu raspoznavaniya
obrazov [Introduction to Statistical Pattern Recognition], Moskow,
Nauka, 1979. 368 p.
\bibitem{item9} K.M. Bishop Raspoznavanie obrazov i mashinnoe obuchenie [Pattern Recognition and Machine Learning], Moskow, Dialektika,
2020. 960 p.
\bibitem{item10} V.V. Myasnikov Raspoznavanie obrazov i mashinnoe obuchenie.
Osnovnye podkhody [Pattern recognition and machine learning.
Basic approaches], Samara, Izdatel’stvo Samarskogo universiteta,
2023. 196 p.
...
\end{thebibliography}
```
Вот как выглядит это в pdf
![Пример библиографии](https://github.com/iis-42x70x/RPIIS/blob/Бурбас_Д/Lab_3_/images_latex/biblio_example.png)
## Создание заголовка главы
Для создания заголовка главы необходимо для начала написать в преамбуле команды по форматированию текста заголовка:
```
\title{\centering \vspace{-15mm} \huge \textbf{Interoperability as a Critical Component of the
Educational Process in Secondary Schools}}
\author{Alena Kazlova and Alexander Halavaty\\ \small
\textit{Belarusian State University}\\ \small
Minsk, Belarus\\ \small
Email: kozlova@bsu.by}
\date{}
\titleformat{\section}[block]{\normalsize \centering}{\thesection.}{0.4em}{}
```
А потом написать команду уже в основной части кода, а не в преамбуле:
```
\maketitle
```
Вот как выглядит это в pdf
![Пример Заголовка](https://github.com/iis-42x70x/RPIIS/blob/Бурбас_Д/Lab_3_/images_latex/headline_example.png)
## Переключение языка
Для переключения языка(к примеру на русский) можно использовать команду
```
\selectlanguage{russian}
```
![Пример смены языка](https://github.com/iis-42x70x/RPIIS/blob/Бурбас_Д/Lab_3_/images_latex/select_lang_example.png)
## Ресурс для более глубокого изучения LaTeX
[Learn LaTeX in 30 minutes](https://www.overleaf.com/learn/latex/Learn_LaTeX_in_30_minutes "Туториалы от Overleaf")