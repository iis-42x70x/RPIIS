# <a href="https://git.io/typing-svg"><img src="https://readme-typing-svg.herokuapp.com?font=Italic&weight=500&size=33&pause=1000&color=D740F7&random=false&width=435&lines=%D0%A0%D0%B0%D1%81%D1%87%D0%B5%D1%82%D0%BD%D0%B0%D1%8F+%D1%80%D0%B0%D0%B1%D0%BE%D1%82%D0%B0" alt="Typing SVG" /></a>
---
## <a href="https://git.io/typing-svg"><img src="https://readme-typing-svg.herokuapp.com?font=Italic&weight=500&size=29&pause=1000&color=D740F7&background=37143F16&random=false&width=435&lines=%D0%92%D0%B2%D0%B5%D0%B4%D0%B5%D0%BD%D0%B8%D0%B5" alt="Typing SVG" /></a>

### <a href="https://git.io/typing-svg"><img src="https://readme-typing-svg.herokuapp.com?font=Italic&weight=500&size=24&pause=1000&color=D740F7&random=false&width=435&lines=%D0%A6%D0%B5%D0%BB%D1%8C" alt="Typing SVG" /></a>
♥ Изучить основы теории графов, способы представления графов, базовые алгоритмы для работы с графам. ♥

---
### <a href="https://git.io/typing-svg"><img src="https://readme-typing-svg.herokuapp.com?font=Italic&weight=500&size=24&pause=1000&color=D740F7&random=false&width=435&lines=%D0%97%D0%B0%D0%B4%D0%B0%D0%BD%D0%B8%D0%B5" alt="Typing SVG" /></a>
>*☆ 1.8 определить вид графа ☆*

Реализовать на С++ код, определяющий двусвязный граф. Граф представлен в виде матрицы инцидентности.

---
### <a href="https://git.io/typing-svg"><img src="https://readme-typing-svg.herokuapp.com?font=Italic&weight=500&size=24&pause=1000&color=D740F7&random=false&width=435&lines=%D0%9A%D0%BB%D1%8E%D1%87%D0%B5%D0%B2%D1%8B%D0%B5+%D0%BF%D0%BE%D0%BD%D1%8F%D1%82%D0%B8%D1%8F" alt="Typing SVG" /></a>

* $\color{violet}{\textsf {Граф }}$  -  математическая абстракция реальной системы любой природы, объекты которой обладают парными связями.
(совокупность точек, соединенных линиями. Точки называются вершинами, или узлами, а линии – ребрами, или дугами.)

* $\color{violet}{\textsf{ Неориентированный граф }}$ — Граф, ни одному ребру которого не присвоено направление.

* $\color{violet}{\textsf{ Матрица инцедентности графа }}$ — это матрица, количество строк в которой соответствует числу вершин, а количество столбцов – числу рёбер. В ней указываются связи между инцидентными элементами графа (ребро(дуга) и вершина). (В неориентированном графе если вершина инцидентна ребру то соответствующий элемент равен 1, в противном случае элемент равен 0)

* $\color{violet}{\textsf{ Двусвязный граф }}$ - связный и неделимый граф в том смысле, что удаление любой вершины не приведёт к потере связности.

## <a href="https://git.io/typing-svg"><img src="https://readme-typing-svg.demolab.com?font=Italic&weight=500&size=24&pause=1000&color=D740F7&width=435&lines=%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC+%D1%80%D0%B5%D1%88%D0%B5%D0%BD%D0%B8%D1%8F" alt="Typing SVG" /></a>

На вход алгоритму подаётся матрица инцидентности. По ней необходимо проверить, инцидентна ли каждая вершина как минимум двум рёбрам. 

## <a href="https://git.io/typing-svg"><img src="https://readme-typing-svg.demolab.com?font=Italic&weight=500&size=24&pause=1000&color=D740F7&width=435&lines=%D0%A0%D0%B5%D0%B0%D0%BB%D0%B8%D0%B7%D0%B0%D1%86%D0%B8%D1%8F+%D0%BD%D0%B0+%D0%A1%2B%2B" alt="Typing SVG" /></a>
```C++
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	setlocale(LC_ALL, "RUSSIAN");
	string path = "matrix.txt";
	ifstream fin;
	fin.open(path);
	if (!fin.is_open())
	{
		cout << "Файл не найлен\n";
	}
	else
	{
        int count = 0;
        int temp;

        while (!fin.eof())
        {
            fin >> temp;
            count++;
        }
        
        fin.seekg(0, ios::beg);
        fin.clear();

        
        int count_space = 0;
        char symbol;
        while (!fin.eof())
        {           
            fin.get(symbol);
            if (symbol == ' ') 
                count_space++;
            if (symbol == '\n')
                break;
        }
        

        
        fin.seekg(0, ios::beg);
        fin.clear();

        

        int rows = count / (count_space + 1);
        int columns = count_space + 1;

        double** matrix;
        matrix = new double* [rows];
        for (int i = 0; i < rows; i++)
            matrix[i] = new double[columns];

        
        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++)
                fin >> matrix[i][j];

        
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
                cout << matrix[i][j] << "\t";
            cout << "\n";
        }


        bool check2sv = true;        
        for (int i = 0; i < rows; i++) 
        {
            int count1 = 0;
            for (int j = 0; j < columns; j++)
            {
                if (matrix[i][j] == 1)
                {
                    count1++;                   
                }
                
            }
            if (count1 < 2) {
                
                check2sv = false;
            }
        }

        if (check2sv != false)
        {
            cout << "Граф двусвязный\n";
        }
        else
        {
            cout << "Граф не двусвязный\n";
        }
        

        for (int i = 0; i < rows; i++)
            delete[] matrix[i];
        delete[] matrix;

        fin.close();
        
	}

}
```
## <a href="https://git.io/typing-svg"><img src="https://readme-typing-svg.demolab.com?font=Italic&weight=500&size=24&pause=1000&color=D740F7&width=435&lines=%D0%A0%D0%B0%D0%B7%D0%B1%D0%BE%D1%80+%D0%BA%D0%BE%D0%B4%D0%B0" alt="Typing SVG" /></a>

- `Подключаем библиотеку для работы с файлами и пространство имён std`
```C++
#include <iostream>
#include <fstream>
using namespace std;
```

- `Устанавливаем русскую локализацию, создаём переменную для пути к файлу и для самого файла`
```C++
setlocale(LC_ALL, "RUSSIAN");
string path = "matrix.txt";
ifstream fin;
fin.open(path);
```

- `Если файл не удалось найти, выводим в консоль сообщение об ошибке`
```C++
if (!fin.is_open())
{
	cout << "Файл не найлен\n";
}
```

Последующий код оборачиваем в условие else.

Создаём переменную для счёта количества символов и временную переменную. Пока файл не проверен до конца, записываем символ во временную переменную и увеличиваем счётчик символов
```C++
int count = 0;
int temp;

while (!fin.eof())
{
    fin >> temp;
    count++;
}
```

Переходим обратно в начало файла
```C++
fin.seekg(0, ios::beg);
fin.clear();
```

Создаём переменную для счёта количества пробелов и для символов. Пока файл не проверен до конца, получаем символ. Если этот символ - пробел, то увеличиваем счётчик пробелов. Если доходим до конца строки, то выходим из цикла.
```C++
int count_space = 0;
char symbol;
while (!fin.eof())
{           
    fin.get(symbol);
    if (symbol == ' ') 
        count_space++;
    if (symbol == '\n')
        break;
}
```

Снова возвращаемся в начало файла
```C++
fin.seekg(0, ios::beg);
fin.clear();
```

Создаём переменные и вычисляем количество строк и столбцов
```C++
int rows = count / (count_space + 1);
int columns = count_space + 1;
```

Создаём двумерный динамческий массив 
```C++
double** matrix;
matrix = new double* [rows];
for (int i = 0; i < rows; i++)
    matrix[i] = new double[columns];
```

Записываем в этот массив данные из матрицы
```C++
for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++)
        fin >> matrix[i][j];
```

Выводим матрицу на экран
```C++
for (int i = 0; i < rows; i++)
{
    for (int j = 0; j < columns; j++)
        cout << matrix[i][j] << "\t";
    cout << "\n";
}
```

Создаём переменную, где будет записан ответ, является ли граф двусвязным
```C++
bool check2sv = true;
```

Выполняем проверку на двусвязность. Если встречаем в строке матрицы единицу, то увеличиваем переменную count1. Если в строке меньше двух единиц, то записываем в check2sv значение false.
```C++
for (int i = 0; i < rows; i++) 
{
    int count1 = 0;
    for (int j = 0; j < columns; j++)
    {
        if (matrix[i][j] == 1)
        {
            count1++;                   
        }
        
    }
    if (count1 < 2) {
        
        check2sv = false;
    }
}
```

Выводим на экран результат. Если check2sv не было изменено на false, то граф двусвязный. В ином случае граф не двусвязный.
```C++
if (check2sv != false)
{
    cout << "Граф двусвязный\n";
}
else
{
    cout << "Граф не двусвязный\n";
}
```

Очищаем память, удаляя двумерный массив и закрывая файл. 
```C++
for (int i = 0; i < rows; i++)
    delete[] matrix[i];
delete[] matrix;

fin.close();
```

## Тесты:
Граф 1:

![Граф1](https://github.com/iis-32170x/RPIIS/blob/Давыдов_Р/RR/Tests/graph1.PNG)

Матрица 1:
```
1 0 1 0
1 1 0 0
0 1 0 1
0 0 1 1
```

Результат 1:

![result1](https://github.com/iis-32170x/RPIIS/blob/Давыдов_Р/RR/Tests/output1.PNG)

Граф 2:

![Граф2](https://github.com/iis-32170x/RPIIS/blob/Давыдов_Р/RR/Tests/graph2.PNG)

Матрица 2:
```
1 0 1 0 0 0 0 1 0
1 1 0 0 1 0 0 0 1
0 1 0 1 0 1 0 0 0
0 0 1 1 0 0 1 0 0
0 0 0 0 0 0 0 1 1
0 0 0 0 1 1 1 0 0
```

Результат 2:

![result2](https://github.com/iis-32170x/RPIIS/blob/Давыдов_Р/RR/Tests/output2.PNG)

Граф 3:

![Граф3](https://github.com/iis-32170x/RPIIS/blob/Давыдов_Р/RR/Tests/graph3.PNG)

Матрица 3:
```
1 1 0 1
1 0 1 0
0 1 1 0
0 0 0 1
```

Результат 3:

![result3](https://github.com/iis-32170x/RPIIS/blob/Давыдов_Р/RR/Tests/output3.PNG)

## Выводы
В результате выполнения расчётной работы приобрёл следующие навыки:

* Изучил основы теории графов

* Изучил способы представления графов

* Изучил базовые алгоритмы для работы с графами

* Изучил базовые алгоритмы работы с файлами в C++
