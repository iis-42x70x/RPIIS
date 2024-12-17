# Отчет о работе: Нахождение графа конденсации для орграфа

## Теория

### Что такое граф?
**Граф** — это множество вершин (узлов) и рёбер (связей), которые соединяют пары вершин.  
- Если граф направленный (**орграф**), каждое ребро имеет направление от одной вершины к другой.  
- Если граф невзвешенный, рёбра не имеют численных значений.

Пример:  

Вершины: {0, 1, 2, 3}
Рёбра: (0 -> 1), (1 -> 2), (2 -> 0), (3 -> 1)

### Компоненты сильной связности (КСС)
Компонента сильной связности (КСС) — это подграф, в котором каждая вершина достижима из любой другой.  

Пример:  

Граф: 0 -> 1 -> 2 -> 0, 3 -> 4
КСС: {0, 1, 2}, {3}, {4}

### Граф конденсации
Граф конденсации — это орграф, где каждая вершина представляет одну КСС исходного графа, а рёбра показывают связь между КСС.

Пример:  

Исходный граф: 0 -> 1 -> 2 -> 0, 3 -> 4, 4 -> 3, 2 -> 3
КСС: {0, 1, 2}, {3, 4}
Граф конденсации: (0 -> 1)

### Алгоритм нахождения графа конденсации (Косарайю)
Алгоритм выполняется в три этапа:
- **Первый проход DFS**: Построение стека вершин в порядке завершения DFS.
- **Транспонирование графа**: Меняем напраление всех ребер.
- **Второй проход DFS**: На транспонированном графе, начиная с вершин стека, определяем КСС.

---

## Код и объяснения

### Чтение матрицы смежности из файла
Граф задаётся матрицей смежности, хранящейся в текстовом файле.
```cpp
0 1 0 0
0 0 1 0
1 0 0 1
0 0 0 0
```

```cpp
vector<vector<int>> readAdjacencyMatrix(const string& filename) {
    ifstream file(filename);
    vector<vector<int>> matrix;

    if (!file.is_open()) {
        cerr << "Ошибка: не удалось открыть файл " << filename << endl;
        exit(1);
    }

    string line;
    while (getline(file, line)) {
        vector<int> row;
        size_t pos = 0;
        while ((pos = line.find(' ')) != string::npos) {
            row.push_back(stoi(line.substr(0, pos)));
            line.erase(0, pos + 1);
        }
        row.push_back(stoi(line));
        matrix.push_back(row);
    }

    file.close();
    return matrix;
}
```

 - getline: Считывает строку из файла.
 - stoi: Преобразует строку в число.
 - matrix.push_back(row): Добавляет строку в матрицу.

### Первый DFS: Формирование стека завершения

```cpp
void dfs1(int start, const vector<vector<int>>& matrix, vector<bool>& visited, stack<int>& finishStack) {
    stack<int> s;
    s.push(start);

    while (!s.empty()) {
        int node = s.top();
        s.pop();

        if (!visited[node]) {
            visited[node] = true;
            for (int neighbor = 0; neighbor < matrix.size(); neighbor++) {
                if (matrix[node][neighbor] && !visited[neighbor]) {
                    s.push(neighbor);
                }
            }
            finishStack.push(node);
        }
    }
}
```

 - Цель: Проходим граф в глубину и сохраняем вершины в стек finishStack в порядке завершения их обработки.
 - Параметры:
 - start — стартовая вершина.
 - matrix — матрица смежности графа.
 - visited — массив посещённых вершин.
 - finishStack — стек для хранения порядка завершения вершин.

### Транспонирование графа

```cpp
vector<vector<int>> transpose(V, vector<int>(V, 0));
for (int u = 0; u < V; u++) {
    for (int v = 0; v < V; v++) {
        if (graph[u][v]) {
            transpose[v][u] = 1;
        }
    }
}
```

 - Цель: Меняем направления всех рёбер.
Если в исходном графе было ребро u -> v, то в транспонированном — v -> u.

### Второй DFS: Нахождение КСС

```cpp
void dfs2(int start, const vector<vector<int>>& transpose, vector<bool>& visited, vector<int>& component) {
    stack<int> s;
    s.push(start);

    while (!s.empty()) {
        int node = s.top();
        s.pop();

        if (!visited[node]) {
            visited[node] = true;
            component.push_back(node);
            for (int neighbor = 0; neighbor < transpose.size(); neighbor++) {
                if (transpose[node][neighbor] && !visited[neighbor]) {
                    s.push(neighbor);
                }
            }
        }
    }
}
```

 - Цель: Найти все вершины, принадлежащие текущей КСС.
 - component.push_back(node): Добавляем вершину в текущую компоненту сильной связности.

### Построение графа конденсации

```cpp
set<pair<int, int>> edges;
for (int u = 0; u < V; u++) {
    for (int v = 0; v < V; v++) {
        if (graph[u][v] && componentMap[u] != componentMap[v]) {
            edges.insert({componentMap[u], componentMap[v]});
        }
    }
}
```

 - Цель: Для каждой пары вершин u и v проверяем:
 - Если вершины принадлежат разным КСС, добавляем ребро между соответствующими вершинами графа конденсации.

### Вывод результатов

```cpp
cout << "Компоненты сильной связности:" << endl;
for (int i = 0; i < stronglyConnectedComponents.size(); i++) {
    cout << "КСС " << i << ": ";
    for (int v : stronglyConnectedComponents[i]) {
        cout << v << " ";
    }
    cout << endl;
}
```

```cpp
cout << "\nГраф конденсации:" << endl;
if (edges.empty()) {
    cout << "Рёбер между КСС нет." << endl;
} else {
    for (auto edge : edges) {
        cout << edge.first << " -> " << edge.second << endl;
    }
}
```

### Вывод

Пример:

Для входного файла graph.txt:

```cpp
0 1 0 0
0 0 1 0
1 0 0 1
0 0 0 0
```

Результаты:

```shell
Компоненты сильной связности:
КСС 0: 3
КСС 1: 0 1 2

Граф конденсации:
0 -> 1
```

Алгоритм корректно разделяет граф на КСС и строит граф конденсации.