\documentclass[twocolumn,10pt]{extarticle}
\setlength{\parindent}{2em}
\setlength{\parskip}{0pt}
\usepackage{amsmath, amssymb, amsthm}
\usepackage{enumitem}
\newcommand{\RomanNumeralCaps}[1] %преамбула для римских цифр
    {\MakeUppercase{\romannumeral #1}}
\usepackage [la4paper, top=2cm, bottom=2cm, left=2.2cm, right=2.2cm]
{geometry}
\begin{document}
\setcounter{page}{199}
mode when the user asks a question and the system answers [43], [44]. A clear advantage of question-and- answer systems is the possibility of linguistic processing of user questions [40], [45]. At the same time, semantic classification of question-answer texts contributes to the isolation of specific types of relations, question types and answer classes [45]–[48]. The conceptual basis for for- malizing questions in QAS is the question language and erotetic logic, which allows us to specify question-answer relations [39]. Currently known question-answer systems, which are capable of parsing a question and matching the answer with the help of a natural language analyzer, are Mulder [49], AllQuest (http://www.allquests.com) and AskNet Global Search (http://www.asknet.ru).

However, such systems are focused only on analyzing and detecting semantic relations between subject domain objects in indexed texts. This fact imposes the following limitations [50]:
\begin{itemize}[noitemsep]
\item there is no possibility to strictly formally establish semantic relations between objects in the text;
\item it is impossible to generate a response to the user when such a response does not exist in the indexed texts or in the current information state of the system;
\item  does not support questions to identify correspon- dences and analogies between objects and concepts.
\end{itemize}
The elimination of these limitations requires the cre- ation of the next generation of question-and-answer systems — intelligent reference systems (IRS), or in- telligent question-and-answer systems (IQAS). In such systems, the emphasis shifts from textual representation of information to the formation and use of knowledge spaces. The combination of work on the representation of knowledge in the IQAS knowledge base, the processing of this knowledge by special operations of the knowledge processing machine, and the interaction of the end user with the IQAS requires the coordination of all three stages of work. Thus, for the mass development of IQASs in various subject areas, a design technology for intelligent question-answering systems is needed in which, first, all design stages are coordinated, second, the languages of knowledge representation are compatible with the languages of knowledge processing and the languages of user communication with the IQAS

Despite the successes in the development of geoin- formation services and their standardization, creation of ontologies of subject areas, knowledge about terrain objects and phenomena as integrating elements of subject areas, due attention has not been paid and not investigated semantic compatibility of GIS components and applied GIS, procedures for integration of spatial knowledge with knowledge of subject areas have not been established. In this regard, the actual task is:
\begin{itemize}[noitemsep]
\item designing spatial ontologies and based on them solving the problem of integration of knowledge of
subject areas and spatial relations, as well as solving the problem of metadata management and improv- ing search, access and exchange in the conditions of growing volumes of spatial information and services provided by multiple sources of geoinformation;
\item realizing knowledge inference using spatial and thematic information and meeting the information needs of users using question language;
\item development of cartographic interface as a natural way for human to present information about terrain objects and phenomena, based on the formal de- scription of the syntax of the map language, and providing both understanding of the semantics of terrain objects and phenomena immersed in knowl- edge bases, and providing changes in the state of knowledge bases.
\end{itemize}

Thus, the constant evolution of models and tools for ontological description of subject areas using spatial and temporal components, the heterogeneity of spatial components and the ambiguity of temporal components, poses new challenges in terms of interaction, integration and compatibility of different types of knowledge used in GIS by integrating subject area ontologies (vertical level), extending GIS subsystems at the horizontal level and utilizing new territories and time intervals

Analysis of human activities and works in the field of geoinformatics shows that further development in this area lies in the field of intellectualization of geographic information systems [51]–[58].

\textbf {intelligence of systems with integrated spatially referenced data}

$\Rightarrow subdividing*:$
\textit{
\begin{itemize}[noitemsep, leftmargin=2.5cm]
\item use of digital cartographic material and Earth remote sensing data in
problem-oriented areas, creation of systems for pattern and image recognition from Earth remote sensing data [4], [59], [60]
\item planning of actions in a dynamically changing situation under incomplete or fuzzy data using expert
knowledge [61]–[63]
\item Analysis of emergency situations and preparation of materials for decision-making on prevention or elimination of their consequences, creation of expert systems for forecasting the occurrence and development on the ground of man-made and natural situations: floods, earthquakes, extreme weather conditions (precipitation, temperature), epidemics, spread of radionuclides, chemical emissions, meteorological forecast, etc. [64]
199
\item creation of decision support systems for applied geoinformation systems of territorial planning and
management [65]–[68]
\item development of diagnostic expert systems for geological exploration and underground hydrodynamics [69]–[71]
\item control systems of transportation and transportation processes [72]–[74]
\item logistic planning, creation of expert systems and software tools for enterprise and building management [75]–[77]
\item creation of monitoring, control and navigation systems [78]
\item creation of expert systems and software tools for geodata analysis [79]
\item resolution of land disputes [80]
\item medico-geographical assessment of
environmental impact on human
health [81]
\item retrospective analysis of events and
inventory of cultural heritage [82]–[86]
\item creation of digital cartographic
information banks with remote access to them, spatial information management based on spatial data portals, creation of information retrieval systems on Earth sciences and geoinformatics [87]–[90]
\item development of support systems for pedagogical, educational and training activities, as well as training systems using spatial information [91]–[97]
\end{itemize}
}
The intellectualisation of geographic information sys- tems implies [51], [98]:
\begin{itemize}[noitemsep]
\item  the possibility of end-user communication with the system in the language of questions [99];
\item  the use of various interoperable problem solvers with the possibility of explaining the obtained so- lutions;
\item  use of cartographic interface for visualisation of initial data and results.
Realising the capabilities of intelligent reference geo- graphic information systems can be done by:
\item  knowledge base management systems, • intelligent search,
\item  interoperable problem solvers,
\item  intelligent map interfaces,
\item  expert systems in various fields of human activity, 
\item  decision support systems,
\item intelligent assistance systems
\end{itemize}
Full solution of the above tasks requires the use of open systems standards, the use of ontologies of terrain objects as integrating elements of different subject areas,
communication of users with the system in the mode of question-and-answer system using the language of questions.

The technology that satisfies these requirements is the open complex technology for developing intelligent systems based on semantic networks [100] (OSTIS tech- nology — Open Semantic Technology for Intelligent Systems), the main provisions and principles of which are described in the work [101], the principles of creation and unified design models in the works [102], [103].

OSTIS technology is based on the following principles [104]:
\begin{itemize}[noitemsep]
\item orientation on semantic unambiguous representation of knowledge in the form of semantic networks hav- ing basic theoretical-multiple interpretation, which provides problems of diversity of forms of repre- sentation of the same meaning, and problems of ambiguity of semantic interpretation of information constructions;
\item the use of associative graph-dynamic model of memory;
\item application of agent-based model of knowledge pro- cessing;
\item realisation of OSTIS technology in the form of intellectual Metasystem IMS [5], which itself is built on OSTIS technology and provides design support for computer systems developed on OSTIS technology;
\item ensuring in the designed systems a high level of flexibility, stratification, reflexivity, hybridity, inter- operability and, as a consequence, learnability.
\end{itemize}

Systems built on this technology are called ostis- systems, and the universal abstract language of seman- tic networks (SC-code) or semantic code is used as a language tool for knowledge representation. In this case, knowledge bases of ostis-systems have a semantic representation, and the knowledge and skills interpreter is a collection of agents that process the knowledge base and manage situations and events in this knowledge base [104].
At the same time, the systems developed using this technology do not have the disadvantages of sys- tems based on generative models (systems like Chat- GPT [105]), because it is not the generation of new data, which are similar to the training data, but the relationship between the actual data and knowledge of the subject area is established, which ensures the reliability of conclusions based on knowledge.

In order to realise these possibilities, reduce the labour intensity of building and modifying intelligent systems with integrated spatially related data, it is proposed to build a semantic model of ISRD based on spatial ontolo- gies, to ensure communication between users of ISRD in a formal language of questions and to develop means of automation and information support of the design 200 process of this class of systems, including the formation of components of the core of intelligent systems with integrated spatially related data.

An important point that reduces the development time of intelligent systems with integrated spatially referenced data on the one hand, and increases their functionality on the other hand, is the availability of tools for designing such systems. At the same time, the technology of designing intelligent systems with integrated spatially referenced data should be oriented to multiple use of functional components of the system in order to reduce the design and development time of application systems. Thus, this study is about the creation of automation and information support for the design of intelligent systems with integrated spatially referenced data.

The structure of the study is presented in Figure 1. The first (upper) level corresponds to the data and knowledge level, where the integration of subject matter knowledge with spatial data and knowledge takes place; the second (middle) level is the system level, which corresponds to the principles underlying the proposed approach; the third (lower) level is the application level and corresponds to the application systems developed on the basis of the models and tools proposed in the paper.

The models, software tools and means of automation and information support of design proposed in this paper are proposed to be developed as a part of the open complex technology for the development of intelligent systems based on semantic networks OSTIS.
Using the notation adopted in the design of systems using OSTIS technology, let us clarify the concept of an intelligent system with integrated spatially referenced data (synonymous with intelligent geographic informa- tion system).\\

\textbf{intelligent system with integrated spatially referenced data}

\begin{tabular}{c p{10cm}}
:= & [intelligent geographic information system]\\
:= & [an information system designed to provide \\
   & answers to a user’s question, the main \\
   & object of study of which is knowledge and \\
   & data on terrain objects, acting as an \\
   & integration basis for solving applied \\
   &tasks in various subject areas]\\
\end{tabular}

\begin{tabular}{c p{12cm}}
$\supset$  & intelligent ostis-system with integrated \\
           & spatially referenced data\\
\end{tabular}

\hspace{40pt}$\subset ostis-system $

\hspace{40pt}
\begin{tabular}{c p{5cm}}
:= & [an intelligent system with inte-\\
   &grated spatially referenced data,\\
   &developed according to the prin-\\
   &ciples of OSTIS technology]\\
\end{tabular}

\hspace{60pt}$\Rightarrow subdividing*:$  
\textit{
\begin{flushright}
\begin{minipage}{0.3\textwidth}
\begin{itemize}[noitemsep]
\item knowledge base of
intelligent ostis-system with integrated spatially-referenced data
\item problem solver for intelligent ostis-system
with integrated spatially
referenced data 
\item map interface of
intelligent ostis-system with integrated spatially referenced data
201
\end{itemize}
\end{minipage}
\end{flushright}
}
\begin{center}
\RomanNumeralCaps{3}.Semantic model of an intelligent system with 
integrated spatially reference data
\end{center}
This work is based on the method of knowledge representation in the form of a homogeneous semantic network with basic theoretical-multiple interpretation, which allows not only to describe declarative knowledge of subject areas, but also procedures of their process- ing, i. e. we are talking about procedural knowledge, the interpretation of which is carried out in a special component — semantic problem solver.

Therefore, in this paper, the concept of an intercon- nected system of coordinated semantic models of intelli- gent systems proposed in the works [102], [103], [106]– [109] is further developed in a more complete realisation of a special class of intelligent systems - intelligent systems with integrated spatially referenced data. For this purpose it is necessary to form the core ISRD, which is based on the semantic model of this class of systems. Thus, it is necessary to describe the semantic model of the knowledge base of an intelligent system with inegrated spatial data, which includes the construction of geontology and necessitates the development of a model of integration of subject areas with spatial components of geoinformation systems, the semantic model of the ISRD problem solver and the semantic model of the ISRD user interface [98], [110]. In this case, the user interface is not a viewer of cartographic (spatial) data, but a component interfaced with the knowledge base, i. e. knowledge about space understood by the system with simultaneous updating of knowledge both in the knowledge base of the system and in the knowledge base of the user interface.

In order to ensure semantic compatibility, an ontology of spatial objects has been developed, the task of which is to clearly and unambiguously define the semantics of terrain objects and phenomena.

The ontology of spatial objects consists of two sections. The first section includes directly the ontology of terrain objects and phenomena. The second section contains se- mantic characteristics of such objects — special elements specifying spatial and semantic characteristics of terrain objects and phenomena.

In the ontology of terrain objects and phenomena the objects of classification are terrain objects and phenom- ena to which map objects correspond, as well as features (characteristics) of these objects.


\end{document}
