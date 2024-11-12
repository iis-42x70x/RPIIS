## Лабораторная работа №1
### Цель работы:
Научиться работать с LaTeX. Сверстать несколько страниц. Выполнять ЛР1 можно на сайте [overleaf](https://www.overleaf.com/).

### Команды:
Вот пакеты, которые понадобятся для следующих команд: 
```\usepackage[english, russian]{babel}
\usepackage[T2A]{fontenc}
\usepackage[utf8]{inputenc}
\usepackage{lipsum}
\usepackage{enumitem}
\usepackage{graphicx}
\usepackage{setspace}
\usepackage{geometry}
\usepackage{multicol}
\usepackage{wrapfig}
\usepackage{float}
```


1. Чтобы вставить **картинку с подписью**, сначала загрузите ее на сайт, а после напишите следующий код:
```\ref{fig:picture1}:
\begin{figure}[H]
\includegraphics[width=0.455\textwidth]{1картинка.png}
\caption {\footnotesize Examples of correctly predicted images with their prediction heatmaps for "Overall percent of abnormal volume" parameter:\\a) patient ID 13676, actual value 14\%, predicted value 14\%; \\b) patient ID 2641, actual value 30\%, predicted value 28\%;\\c) patient ID 19415, actual value 34\%, predicted value 33\%.}
\label{fig:picture1}
\end{figure}
```
2. Для того, чтобы начать **параграф** достаточно этого:
```
\par
```
3. Для того, чтобы сделать **список** надо:
```
\begin{itemize}[itemsep=-1mm]
\item background noise (outside the lungs) that requires
mask cropping to remove it;
\item the presence of artifacts in the lungs that requires
more data to train the neural network to correctly
distinguish these artifacts;
\item some errors in CXR image annotations that should
be excluded from the dataset.
\end{itemize}
```
4. Код для **римской цифры**:
```
\RomanNumeralCaps{7}
```
5. Чтобы поместить **параграф в середину**, надо:
```
\begin{center}
\par \RomanNumeralCaps{7.} Discussion of the application of semantic technologies in the context of the tasks considered in
this paper
\end{center}
```
6. Для **списка литературы с пунктиками в виде специальных квадратных скобочках**, используем:
```
\begin{thebibliography}{9}
\scriptsize
\vspace{-1mm}
\bibitem{lamport94}
T.B Portals. Available at: https://tbportals.niaid.nih.gov
(accessed 2024, March)
\vspace{-3mm}
\bibitem
.CASE BROWSER. Available at:
https://data.tbportals.niaid.nih.gov (accessed 2024, March)
\end{thebibliography}
```
7. Чтобы сделать **текст жирным**, надо:
```
\textbf{\large ОБРАБОТКА РЕНТГЕНОВСКИХ
ИЗОБРАЖЕНИЙ ГРУДНОЙ КЛЕТКИ НА
ОСНОВЕ ТЕКСТОВЫХ АННОТАЦИЙ
РАДИОЛОГОВ}
```
8. Прикрепляем **текст к правой стороне**, мы следующим образом:
```
\begin{flushright}
Received 12.03.2024
\end{flushright}
```


#### Здесь можно увидеть код для 3 страниц:
```\documentclass[a4paper, 10pt,]{article}
\usepackage[english, russian]{babel}
\usepackage[T2A]{fontenc}
\usepackage[utf8]{inputenc}
\usepackage{lipsum}
\usepackage{enumitem}
\newcommand{\RomanNumeralCaps}[1]
    {\MakeUppercase{\romannumeral #1}}
\usepackage{graphicx}
\usepackage{setspace}
\usepackage{geometry}
\geometry{top=15mm}
\geometry{bottom=35mm}
\geometry{right=19mm}
\geometry{left=19mm}
\usepackage{multicol}
\usepackage{wrapfig}
\usepackage{float}
\setlength{\columnsep}{1cm}

\begin{document}
\setcounter{page}{300}

\begin{multicols*}{2}

\begin{spacing}{0.55}

\ref{fig:picture1}:
\begin{figure}[H]
\includegraphics[width=0.455\textwidth]{1картинка.png}
\caption {\footnotesize Examples of correctly predicted images with their prediction heatmaps for "Overall percent of abnormal volume" parameter:\\a) patient ID 13676, actual value 14\%, predicted value 14\%; \\b) patient ID 2641, actual value 30\%, predicted value 28\%;\\c) patient ID 19415, actual value 34\%, predicted value 33\%.}
\label{fig:picture1}
\end{figure}


\ref{fig:picture2}:
\begin{figure}[H]
\vspace{1.1cm}\includegraphics[width=0.45\textwidth]{2картинка.png}
\caption {\footnotesize Examples of incorrectly predicted "Overall percent of abnormal volume" with corresponding prediction heatmaps.}
\label{fig:picture2}
\end{figure}

\end{spacing}

but "Overall percent of abnormal volume" parameter is
set to zero.

\begin{spacing}{0.55}

\ref{fig:picture3}:
\begin{figure}[H]
\vspace{0.5cm}\includegraphics[width=0.45\textwidth]{3картинка.png}
\caption {\footnotesize Figure 12. The patient’s right lung has been damaged, but "Overall percent of abnormal volume" parameter is set to zero.}
\label{fig:picture3}
\end{figure}

\end{spacing}

\vspace{0.7cm}

\begin{spacing}{1}
\par A study of patient ID 426 in the CASE BROWSER [2]
found that the other parameter "Pleural Effusion. \%
of hemithorax involved" is equal to 50\%. Also, four
sextants were annotated and have some lesions: Upper,
Middle, Lower Right and Lower Left Sextants. The right
lung is particularly badly damaged

\par At least 44 such images with markup inconsistencies
were found. It is necessary to exclude them from the
training samples.

\par Simple \textsl{consistency checks} between different CXR annotation markup parameters should be developed for
future research. It is necessary to pay attention not only
to the images, but also to the various textual descriptions
provided.
\par As a result, it was concluded that the high MAE value
is due to the following reasons:
\begin{itemize}[itemsep=-1mm]
\item background noise (outside the lungs) that requires
mask cropping to remove it;
\item the presence of artifacts in the lungs that requires
more data to train the neural network to correctly
distinguish these artifacts;
\item some errors in CXR image annotations that should
be excluded from the dataset.
\end{itemize}

\begin{center}
\par \RomanNumeralCaps{7.} Discussion of the application of semantic technologies in the context of the tasks considered in
this paper
\end{center}

\par In 1982, Japanese scientists developed a program for
the fifth generation of electronic computing machines.
Despite the fact that more than 42 years have passed,
the fifth generation computers have not been fully realized. The main difficulty in creating fifth-generation
computers or future computers is to create a machine
with artificial intelligence (AI) that will be able to draw
logical conclusions from the facts presented.

\par To interact with a fifth-generation computer, a person
(user) will not need to develop software for the machine to solve the task at hand. In addition, fifth generation
computers will solve the problem of data formalization
in the interaction between computer and computer and
human and computer. Commands for the machine can be
formulated in ordinary spoken language without knowledge of formal programming languages as well as input
and output data formats.
\par Thus, fifth-generation computers are intelligent semantic systems with extremely high interoperability. Interoperability is the ability of a product or system, whose
interfaces are completely open, to interact and function
with other products or systems without any access or
implementation restrictions.
\par Although fifth generation computers have not yet been
realized, active work is being done to remove the barriers
between humans and computers, and between computers
and computers.
\par One of the directions for the development of interoperable intelligent computer systems is automatic
data transformation between different modalities: image
to text, text to image, speech to text, text to speech,
image to speech, speech to image, image to music, 3D
reconstruction of an object from a set of images, CT
scan to X-ray image, satellite image to geographical map,
geographical map to satellite image and other modality
transformations [19], [20].
\par This research project is developing an intelligent semantic system that converts a textual description into an
image, namely the textual markup of a radiologist into a
heatmap of lesion foci in the corresponding CXR medical
image.
\par A neural network trained to solve such a problem will
be a decision support system for population screening.
The trained neural network model will produce a textual
description of lung lesions based on the patient’s chest
radiograph, as well as a heatmap corresponding to these
lesions in the form of a graphical representation Fig. 13.



\begin{spacing}{0.6}

\vspace{0.5cm}\includegraphics[width=0.45\textwidth]{4картинка.png}
\caption { \footnotesize Figure 13. Operation schematic of the CXR-based decision support system under development.}

\end{spacing}

\vspace{0.7cm}

\par The problem of generating a heatmap from a textual
description and the subsequent problem of generating a
heatmap and corresponding textual description from an
input CXR image is one of the challenges of semantic
image segmentation.
\par Semantic image segmentation is the task of dividing
parts of an image into subgroups of pixels belonging to
corresponding objects, with subsequent classification of
these objects. Unlike classification and object detection tasks, the task of semantic segmentation is more complex
both in terms of solution methods and computational
resources [21].
\par Analyzing the literature to identify different semantic
methods for medical image processing revealed the following approaches:
\begin{itemize}[itemsep=-1mm]
\item probabilistic latent semantic analysis (PLSA),
which, in conjunction with neural network, is able
to mining the hidden semantics of an image [22];
\item implementation of Semantic Similarity Graph Embedding (SSGE) framework, which explicitly explores the semantic similarities among images [23];
\item investigation and development of the concept of
a personal intellectual assistant (secretary, referent) [24].
\end{itemize}
\par Unfortunately, this paper does not apply the found
semantic methods to medical image processing. However,
the application of such semantic techniques in the context
of the tasks considered in this paper is very relevant in
future investigations.
\par As correctly noted in [25], "Currently, decision support systems in radiation mammology focus on the
detection and classification of neoplasms, despite the
fact that \textsl{the real work of a radiologist does not imply
a diagnosing.} Computer vision systems use \textsl{a black box
model} and do not explain the results of work, which is
unacceptable in medicine".
\par This study also focuses on a deeper evaluation of
the behavior of such a "black box" (neural network
model) by studying the activation heatmaps on different
convolutional layers of the neural network, which are
obtained using the Gradient-weighted Class Activation
Mapping (Grad-CAM) method [18]. The investigation
of heatmaps on different convolutional layers provides
a better understanding of the decision-making logic of
the neural network based on the input data.
\par Fig. 5 shows the result of the semantic analysis of
lesion names. As shown in Fig. 5, there are four classes
of lesions: "Cavity", "Density", "Nodule" and "Collapse".
Meanwhile, the two classes "Density" and "Nodule" have
meaning overlap in the three lesion names. In the future,
semantic analysis methods will be applied to better
understand the disease asymmetry of different lung lobes
(see Tab. II).
\par After the decision support system for population
screening is completed, it is planned to be implemented into the already existing software "AI-based
software for computer-assisted diagnosis of lung diseases using chest X-Ray and CT images" (LungExpert,
https://lungs.org.by).

\begin{center}
\par \RomanNumeralCaps{8.} Conclusions
\end{center}

\par In this article, text annotations to CXR images were
analyzed. At this stage of the project, the main efforts of
the authors were focused on the formation of databases for further research. A catalogue tree with new datasets
is described and constantly developing.
\par Two main tasks based on radiologists’ textual annotations were planned and the corresponding pipeline for
the neural networks training was described: pulmonary
disease study using sextants and the pulmonary disease
study using overall characteristics.
\par The task of predicting the parameter "Overall percent
of abnormal volume" showed that it is necessary to
develop additional simple consistency checks between
different CXR textual annotations. Also using lung masks
is a good idea to improve the quality of neural networks.
\par Further research is planned to create neural network
attention heatmaps based on the textual descriptions of
radiologists.

\begin{center}
Acknowledgment
\end{center}

\par This work was carried out with the financial support of
the ISTC-PR150 "Belarus TB Database and TB Portal"
project



\begin{thebibliography}{9}
\scriptsize
\vspace{-1mm}
\bibitem{lamport94}
T.B Portals. Available at: https://tbportals.niaid.nih.gov
(accessed 2024, March)
\vspace{-3mm}
\bibitem
.CASE BROWSER. Available at:
https://data.tbportals.niaid.nih.gov (accessed 2024, March)
\vspace{-3mm}
\bibitem
.TB DEPOT. Available at: https://depot.tbportals.niaid.nih.gov//
cohort-creation?tab=4 (accessed 2024, March)
\vspace{-3mm}
\bibitem
.Tuberculosis (pulmonary manifestations). Available at:
https://radiopaedia.org/articles/tuberculosis-pulmonarymanifestations-1 (accessed 2024, March)
\vspace{-3mm}
\bibitem
.Statistical Atlas of Lung Lesions. Available at:
https://image.org.by/lesionAtlas (accessed 2024, March)
\vspace{-3mm}
\bibitem 
.V. Kovalev, V. Liauchuk, A. Gabrielian, A. Rosenthal, "Towards
Statistical Atlas of Lung Lesions," International Journal of
Computer Assisted Radiology and Surgery, 21-25 June, Munich, Germany, 2020, Vol. 15, Suppl. 1, pp. s31–s32. [Online].
Available: https://www.researchgate.net/publication/3442
17581 Towards\_Statistical\_Atlas\_of\_Lung\_Lesions
\vspace{-3mm}
\bibitem 
.Lung cavity. Available at: https://en.wikipedia.org/wiki/Lung\_
cavity (accessed 2024, March)
\vspace{-3mm}
\bibitem 
.D.M. Hansell, A.A. Bankier, H. MacMahon, T.C. McLoud,
N.L. Müller, J. Remy, et al., "Fleischner Society:
Glossary of terms for thoracic imaging," Radiology,
2008, Vol. 246, No. 3, pp. 697–722. [Online]. Available:
https://doi.org/10.1148/radiol.2462070712
\vspace{-3mm}
\bibitem 
.K. Loverdos, A. Fotiadis, C. Kontogianni, M. Iliopoulou,
M. Gaga, "Lung nodules: A comprehensive review on current
approach and management," Annals of Thoracic Medicine, 2019,
Vol. 14, Issue 4, pp. 226–238. [Online]. Available: https://www.
ncbi.nlm.nih.gov/pmc/articles/PMC6784443
\vspace{-3mm}
\bibitem 
.G. Metry, G. Wegenius, B. Wikström, V. Källskog, P. Hansell,
P.G. Lindgren, H. Hedenström, B.G. Danielson, "Lung density
for assessment of hydration status in hemodialysis patients using the computed tomographic densitometry technique," Kidney
international, 1997, Vol. 52, Issue 6, pp. 1635–1644. [Online].
Available: https://doi.org/10.1038/ki.1997.496
\vspace{-3mm}
\bibitem 
.Pulmonary infiltrate. Available at: https://en.wikipedia.org/wiki/ Pulmonary\_infiltrate (accessed 2024, March)
\vspace{-3mm}
\bibitem 
.Collapsed Lung (Pneumothorax). Available at: https://www.
pennmedicine.org/for-patients-and-visitors/patient-information/
conditions-treated-a-to-z/collapsed-lung-pneumothorax
(accessed 2024, March).
\vspace{-3mm}
\bibitem
.’Timika score’ on x-rays may help identify complex TB
cases. Available at: https://www.auntminnie.com/imaginginformatics/artificial-intelligence/article/15635618/timika-scoreon-xrays-may-help-identify-complex-tb-cases (accessed 2024,
March)
\vspace{-3mm}
\bibitem
.A. Chakraborthy, A.J. Shivananjaiah, S. Ramaswamy,
N. Chikkavenkatappa, "Chest X ray score (Timika score):
an useful adjunct to predict treatment outcome in tuberculosis,"
Advances in Respiratory Medicine, 2018, Vol. 86, No. 5, pp. 205–
210. [Online]. Available: https://doi.org/10.5603/ARM.2018.0032
\vspace{-3mm}
\bibitem
.LungExpert. Available at: https://lungs.org.by (accessed 2024,
March).
\vspace{-3mm}
\bibitem
.TB DEPOT Data Dictionary. Available at: https://depot.tbportals.
niaid.nih.gov//data-dictionary (accessed 2024, March)
\vspace{-3mm}
\bibitem
.ImageNet. Available at: https://www.image-net.org (accessed
2024, March)
\vspace{-3mm}
\bibitem
.R.R. Selvaraju, M. Cogswell, A. Das, R. Vedantam., D. Parikh,
D. Batra, "Grad-CAM: Visual Explanations from Deep Networks
via Gradient-Based Localization," International Journal of Computer Vision, 2020, Vol. 128, No. 2, pp. 336–359. [Online].
Available: https://doi.org/10.1007/s11263-019-01228-7
\vspace{-3mm}
\bibitem
.Top 7 text-to-image generative AI models. Available at:
https://byby.dev/ai-text-to-image-models (accessed 2024, Apr)
\vspace{-3mm}
\bibitem
 .Rohit Kundu. Image Processing: Techniques, Types, Applications [2023]. Available at: https://www.v7labs.com/blog/imageprocessing-guide (accessed 2024, Apr).
\vspace{-3mm}
\bibitem
 .M. Arsalan, M. Owais, T. Mahmood, J. Choi, K.R. Park, "Artificial Intelligence-Based Diagnosis of Cardiac and Related Diseases," Journal of Clinical Medicine, 2020, 9(3):871, pp 1–27. [Online]. Available: https://doi.org/10.3390/jcm9030871
\vspace{-3mm}
\bibitem
.M.R. Zare, M. Mehtarizadeh, "An Ensemble of Deep Semantic
Representation for Medical X-ray Image Classification," 2021
55th Annual Conference on Information Sciences and Systems
(CISS), Baltimore, MD, USA, 2021, pp. 1–6. [Online]. Available:
https://www.doi.org/10.1109/CISS50987.2021.9400268
\vspace{-3mm}
\bibitem 
.B. Chen, Z. Zhang, Y. Li, G. Lu, D. Zhang, "Multi-Label Chest
X-Ray Image Classification via Semantic Similarity Graph Embedding," in IEEE Transactions on Circuits and Systems for Video
Technology, April 2022, vol. 32, no. 4, pp. 2455–2468. [Online].
Available: https://www.doi.org/10.1109/TCSVT.2021.3079900
\vspace{-3mm}
\bibitem 
 .V. Rostovtsev, "Intelligent health monitoring systems,"
Otkrytye semanticheskie tekhnologii proektirovaniya
intellektual’nykh system [Open semantic technologies for
intelligent systems], 2023, pp. 237–240. [Online]. Available:
https://libeldoc.bsuir.by/handle/123456789/51289
\vspace{-3mm}
\bibitem 
.A. Kayeshko, A. Efimova, "Decision support system for breast
cancer screening," Otkrytye semanticheskie tekhnologii proektirovaniya intellektual’nykh system [Open semantic technologies
for intelligent systems], 2021, pp. 229–232. [Online]. Available:
https://libeldoc.bsuir.by/handle/123456789/45424
\end{thebibliography}

\vspace{-1mm}
\begin{center}
\textbf{\large ОБРАБОТКА РЕНТГЕНОВСКИХ
ИЗОБРАЖЕНИЙ ГРУДНОЙ КЛЕТКИ НА
ОСНОВЕ ТЕКСТОВЫХ АННОТАЦИЙ
РАДИОЛОГОВ}
\end{center}

\begin{center}
\normalize Косарева А. А., Павленко Д. А.,Снежко Э. В.
\end{center}

\par Проанализировано более 11 000 рентгеновских снимков
грудной клетки и соответствующих им текстовых аннотаций, а также проведены первые пилотные исследования
по обработке изображений с учетом текстовых аннотаций
специалистов-рентгенологов. Разработан конвейер обработки изображений для базы данных и нейронной сети. Проведено прогнозирование параметра «Общий процент аномального объема», для которого средняя абсолютная ошибка
составила 11,073 при использовании нейросетевой модели
InceptionResNet50V2.

\begin{flushright}
 \large Received 12.03.2024
\end{flushright}

\end{spacing}
\end{multicols*}

\end{document}
```

#### А здесь картинка с готовыми страницами:
<p  align="center"><img src="Скрины/Стр300.jpg" ></p>
<p  align="center"><img src="Скрины/Стр301.jpg" ></p>
<p  align="center"><img src="Скрины/Стр302.jpg" ></p>

#### Выводы: 
Git позволяет отслеживать каждое изменение в проекте, сохраняя историю изменений. Каждое изменение фиксируется в виде коммита с уникальным идентификатором (хэш). Git позволяет нескольким разработчикам одновременно работать над проектом, что делает его идеальным для командной работы. Изменения можно легко объединять и синхронизировать. За выполнение лабораторной работы были изучены принципы работы с Git и GitHub, в том числе напис

## Лабораторная работа №3
---
### Цель работы: 
Научиться работать с гитхабом. Дать консоли определенный команды и посмотреть как они работают.  

### Команды:
1. создать локальный репозиторий в текущей папке <p  align="center"><img src="Скрины2/1.jpg" ></p>
2. посмотреть статус текущего репозитория <p  align="center"><img src="Скрины2/2.jpg" ></p>
3. что такое ветка и какая ветка является обычно основной 
Это коммиты, которые расположены в хронологическом порядке. Основная ветка: main или master 
4. добавить файл в контекст, который будет коммититься <p  align="center"><img src="Скрины2/4.jpg" ></p>
5. создать коммит на основе текущего контекста и указать для него комментарий <p  align="center"><img src="Скрины2/5.jpg" ></p>
6. создать коммит, включающий изменения всех наблюдаемых файлов и указать для него комментарий <p  align="center"><img src="Скрины2/6.jpg" ></p>
7. посмотреть протокол(лог) коммитов <p  align="center"><img src="Скрины2/7.jpg" ></p>
8. посмотреть информацию о текущих настройках  <p  align="center"><img src="Скрины2/8.jpg" ></p>
9. убрать файл из контекста <p  align="center"><img src="Скрины2/9.jpg" ></p>
10. посмотреть изменения в файле по сравнению с последним коммитом <p  align="center"><img src="Скрины2/10.jpg" ></p>
11. убрать изменения относительно последнего коммита из файла <p  align="center"><img src="Скрины2/11.jpg" ></p>
12. добавить в контекст коммита все измененные и созданный файлы <p  align="center"><img src="Скрины2/12.jpg" ></p>
13. изменить глобальные/локальные настройки <p  align="center"><img src="Скрины2/13.jpg" ></p>
14. переписать имя пользователя <p  align="center"><img src="Скрины2/14.jpg" ></p>
15. просмотреть существующие ветки <p  align="center"><img src="Скрины2/15.jpg" ></p>
16. создать новую ветку <p  align="center"><img src="Скрины2/16.jpg" ></p>
17. переключиться на другую ветку <p  align="center"><img src="Скрины2/17.jpg" ></p>
18. создать новую ветку и сразу же переключиться на неё <p  align="center"><img src="Скрины2/18.jpg" ></p>
19. удалить ветку/удалить ветку, даже если она не примержена <p  align="center"><img src="Скрины2/19.jpg" ></p>
20. примержить изменения из указанной ветки в текущую <p  align="center"><img src="Скрины2/20.jpg" ></p>
21. в каком случае могут появиться конфликты? сделать конфликт
Конфликты могут возникнуть в случаях, когда несколько членов команды работают над одним и тем же репозиторием Git, и каждый из них вносит изменения в одни и те же файлы. Конфликты могут возникнуть при слиянии (merge) или ребейзе (rebase) веток, а также при попытке отправить изменения в удаленный репозиторий (push), когда другой пользователь уже сделал изменения в том же файле.align="center"><img src="Скрины2/21.jpg" ></p>
22. как посмотреть в каких файлах конфликты align="center"><img src="Скрины2/22.jpg" ></p>
23. как устранить конфликты align="center"><img src="Скрины2/23.jpg" ></p>
24. как переключиться на указанный коммит align="center"><img src="Скрины2/24.jpg" ></p>
25. сделать ребазирование(rebase) текущей ветки align="center"><img src="Скрины2/25.jpg" ></p>
26. устранение конфликтов во время ребазирования align="center"><img src="Скрины2/26.jpg" ></p>
27. отменить ребазирование во время конфликтов align="center"><img src="Скрины2/27.jpg" ></p>
28. пропустить текущий конфликтный коммит и перейти к следующему align="center"><img src="Скрины2/28.jpg" ></p>
29. отправить изменения из локального репозитория для указанной ветки в удалённый(дистанционный) репозиторий align="center"><img src="Скрины2/29.jpg" ></p>
30. забрать изменения из репозитория, для которого были созданы удалённые ветки по умолчанию align="center"><img src="Скрины2/30.jpg" ></p>
31. забрать изменения удалённой ветки из репозитория по умолчанию, основной ветки align="center"><img src="Скрины2/31.jpg" ></p>
32. создание копии репозитория align="center"><img src="Скрины2/32.jpg" ></p>
33. переименовать последний коммит align="center"><img src="Скрины2/33.jpg" ></p>
34. переименовать не последний коммит align="center"><img src="Скрины2/34.jpg" ></p>
35. скрыть изменения по сравнению с последним коммитом align="center"><img src="Скрины2/35.jpg" ></p>

### Вывод:
В этой лаболаторная я познакомилась с [github.com](https://github.com/INDEX), научилась работать с файлами в ним и ветками через консоль, выучила нужные команды.
