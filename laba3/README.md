<h1 style="text-align: center;"> ЛР1. Работа с LaTex </h1>
<img src="C:\Users\Asus\Desktop\laba3\imagesforlatex\laTex.png">
<h3>Цель ЛР1 - сверстать страницы сборника средствами LaTeX.</h3>
<p>Для выполнения поставленной задачи очень удобно использовать сайт <a href="https://www.overleaf.com/"> OverLeaf</a>.
<h3>Для работы с latex необходимо подключить следующие пакеты:</h3> 
<p><code>\documentclass[7pt]{article} \twocolumn <br>
\usepackage[T2A]{fontenc} % для русского языка <br>
\usepackage[utf8]{inputenc} <br>
\usepackage[russian, english]{babel} <br>
\usepackage{amsmath} <br>
\usepackage{multicol} <br>
\usepackage{geometry} % для настройки отступов <br> 
\geometry{left=1.8cm, right=2cm, top=0.9cm} <br>
\usepackage{graphicx} % для вставки картинок <br>
\DeclareUnicodeCharacter{2212}{-} <br>
\usepackage{fancyhdr}
</code></p>
<h3>Вставка изображений в latex:</h3>
<p>Предварительно необходимо загрузить изображение на сам сайт overleaf:</p>
<img src="C:\Users\Asus\Desktop\laba3\imagesforlatex\addimages.png"></img>
<p>После чего можно добавить свое изображение:</p>
<p><code>\begin{figure}<br> 
\centering<br> 
\includegraphics[width=0.829\linewidth]{snimok5.png}<br>  \caption{\textbf{EasyEPLANner} objects}<br>
\label{fig:easy}</code></p>
<h4>Пример выполнения в PDF:</h4>
<img src="C:\Users\Asus\Desktop\laba3\imagesforlatex\pdfphoto.png"></img>
<h3>Вставка математических формул в latex:</h3>
<p>Необходимо заключать математическую формулу в <code>$..$</code>: <br>
<code>$y_j=F(\displaystyle \sum_{i}\omega_{ij}-T_j)$</code></p>
<h4>Пример выполнения в PDF:</h4>
<img src="C:\Users\Asus\Desktop\laba3\imagesforlatex\formula.png"></img>
<h3>Работа со списками в latex:</h3>
<p><code>\begin{itemize}<br>
\item Improving system performance and especially accelerating system response time to user requests. It is connect with productivity and overall user satisfaction.<br> \item Continuous updating and refactoring ontological models (further formalization of missing concepts, fix typos and etc.);<br>
\item Enhancing PFC-visualization - not only displaying, but also editing diagrams. Adding rich navigating between PFC-diagram and according text representation;<br>
\item Further formulation of questions (typical) to the system from the user and their formalization at the level of the existing knowledge base;<br>
\item Adding more description of parts of real control projects based on the existing knowledge base.<br>
\end{itemize}</code></p>
<h4>Пример выполнения в PDF:</h4>
<img src="C:\Users\Asus\Desktop\laba3\imagesforlatex\listing.png"></img>
<h3>Благодарности в latex:</h3>
<p><code>\begin{thebibliography}{20}<br>
\fontsize{6}{5}\selectfont<br>
\setlength{\parindent}{0cm}<br>
\setlength{\parskip}{0.1cm}<br>
\bibitem[1]{e1}  N. Lutska, O. Pupena, A. Shyshak, V. Taberko, D. Ivaniuk, M. O.
Nikita Zotov, and L. Vlasenko, “Ontological model of digital twin
in manufacturing,” in \underline{Open semantic technologies for intelligent
systems}, ser. 5, V. Golenkov, Ed. BSUIR, Minsk, 2022, p.
310–335.<br>
\bibitem[2]{e1} V. V. Taberko, D. S. Ivaniuk, D. V. Shunkevich, and O. N. Pupena,
“Principles for enhancing the development and use of standards
within Industry 4.0,” in \underline{Open semantic technologies for intelligent
systems}, ser. 4, V. Golenkov, Ed. BSUIR, Minsk, 2020, pp. 167–
174.<br>
\bibitem[3]{e1} V. A. Golovko, A. A. Kroshchanka, V. V. Golenkov, V. P.
Ivashenko, M. V. Kovalev, V. V. Taberko, and D. S. Ivaniuk,
“Integration of artificial neural networks and knowledge bases,”
2018.<br>
\bibitem[4]{e1} S. Gil, G. D. Zapata-Madrigal, and G. L. Giraldo-Gómez, “An ontological model to integrate and assist virtualization of automation
systems for industry 4.0,” \underline{Smart and Sustainable Manufacturing
Systems}, vol. 5, p. 10, 09 2021.<br>
\bibitem[5]{e1} V. R. Sampath Kumar, A. Khamis, S. Fiorini, J. L. Carbonera, A. Olivares Alarcos, M. Habib, P. Goncalves, H. Li, and
J. I. Olszewska, “Ontologies for industry 4.0,” \underline{The Knowledge
Engineering Review}, vol. 34, p. e17, 2019.</code></p>
<h4>Пример выполнения в PDF:</h4>
<img src="C:\Users\Asus\Desktop\laba3\imagesforlatex\references.png"></img>
<h3>Выполнение римских цифр средствами latex:</h3>
<code>\newcommand{\RomanNumeralCaps}[1]<br>
{\MakeUppercase{\romannumeral #1}} %римские цифры будут выглядеть как надо<br>
\begin{center}<br>
\section*{\footnotesize \RomanNumeralCaps{9}. Conclusion}<br>
\end{center}</code>
<h4>Теперь как это выглядит в PDF:</h4>
<img src="C:\Users\Asus\Desktop\laba3\imagesforlatex\romannumeral.png"></img>
<h1 style="text-align: center;">ЛР3.Знакомство с Git и Github.</h1>
<h3>Цель: работа с Git и GitHub, а также научиться оформлять MarkDown файлы</h3>
<h4>Что такое git?</h4>
<p>Git - это консольная утилита, для отслеживания и ведения истории изменения файлов, в вашем проекте. Чаще всего его используют для кода, но можно и для других файлов. Например, для картинок - полезно для дизайнеров.
<br>С помощью Git-a вы можете откатить свой проект до более старой версии, сравнивать, анализировать или сливать свои изменения в репозиторий.</p>
<hr style="color: red;">
<img src="C:\Users\Asus\Desktop\laba3\imagesforlatex\git.png"></img>
<hr style="color: red;">
<h1 style = "text-align: center;">Основные команды Git:</h1>
<p><code>git init</code> - создание пустого репозитория<br>
<code>git add <имя файла></code> - добавление файла в репозиторий<br>
<code>git add .</code> - добавление всех файлов в репозиторий<br>
<code>git branch</code> - создание ветки<br>
<code>git status</code> - проверка статуса<br>
<code>git commit -m "message"</code> - создание коммита<br>
<code>git push origin <название ветки></code> - загрузка на определенную ветку в Github<br>
<code>git checkout <branch></code> - переход к ветке
<h3>Вывод:</h3>
<hr>
<p>В ходе данной лабораторной работы я познакомился с системой контроля версий Git, изучил основы ее применения, а также научился работать с репозиториями GiHub.</p>
<hr>