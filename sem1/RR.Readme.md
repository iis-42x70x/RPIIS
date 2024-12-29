# Расчётная работа.
---
## Введение

### Цель
 Изучить основы теории графов, способы представления графов, базовые алгоритмы для работы с графам. 

---
### Задание
 1.8 (мс)  определить вид графа 

Реализовать на С++ код, определяющий двусвязный граф. Граф представлен в виде матрицы смежности.

---
### Ключевые понятия 

* $\color{red}{\textsf {Граф }}$  -  математическая абстракция реальной системы любой природы, объекты которой обладают парными связями.
(совокупность точек, соединенных линиями. Точки называются вершинами, или узлами, а линии – ребрами, или дугами.)

* $\color{red}{\textsf{ Неориентированный граф }}$ — Граф, ни одному ребру которого не присвоено направление.

* $\color{red}{\textsf{ Матрица смежности}}$ — вид представления графа в виде матрицы, когда пересечение столбцов и строк задаёт дуги. Используя матрицу смежности, можно задать вес дуг и ориентацию.

* $\color{red}{\textsf{ Двусвязный граф }}$ - связный и неделимый граф в том смысле, что удаление любой вершины не приведёт к потере связности.

## Решение

На вход алгоритму подаётся матрица смежности. По ней необходимо проверить, инцидентна ли каждая вершина как минимум двум рёбрам. 

```C++
vector<vector<int>> adjMatrix(n, vector<int>(n, 0));
cout << "Enter the adjacency matrix (" << n << " x " << n << "):" << endl;
for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
        cin >> adjMatrix[i][j];
    }
}
```


```C++
  void dfsBiconnected(int u, int parent, const vector<vector<int>>& adjMatrix, vector<int>& discoveryTime,
                    vector<int>& lowTime, stack<pair<int, int>>& edgeStack, int& time, bool& isBiconnected) {
    discoveryTime[u] = lowTime[u] = ++time;
    int children = 0;

    for (int v = 0; v < adjMatrix.size(); ++v) {
        if (adjMatrix[u][v]) {
       }
    }
}
```

```C++
cout << "Введенная матрица:\n";
for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
        cout << matrix[i][j] << "\t";
    }
    cout << "\n";
}
```

```C++
bool isGraphBiconnected(const vector<vector<int>>& adjMatrix) {
    // Initialization
    dfsBiconnected(0, -1, adjMatrix, discoveryTime, lowTime, edgeStack, time, isBiconnected);
    return isBiconnected;
}
```

## Выводы
В результате выполнения расчётной работы приобрёл следующие навыки:

* $\color{red}{\textsf { ✔️ Изучил основы теории графов }}$

* $\color{red}{\textsf { ✔️ Изучил способы представления графов }}$

* $\color{red}{\textsf { ✔️ Изучил базовые алгоритмы для работы с графами }}$

* $\color{red}{\textsf { ✔️ Изучил базовые алгоритмы работы с файлами в C++ }}$
  ### Ссылки на источники :
  https://www.youtube.com/watch?v=TLV2akXrAXE
  https://www.youtube.com/watch?v=y1Yz3WJyGfA
  https://www.youtube.com/watch?v=aK5bw-WTB1A
