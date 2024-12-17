#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <fstream>
#include <string>
#include <Windows.h>
using namespace std;


//DFS для первого прохода
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

//DFS для второго прохода
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

// Чтение матрицы смежности из файла
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
        int value;
        size_t pos = 0;
        while ((pos = line.find(' ')) != string::npos) {
            value = stoi(line.substr(0, pos));
            row.push_back(value);
            line.erase(0, pos + 1);
        }
        row.push_back(stoi(line)); // Последний элемент в строке
        matrix.push_back(row);
    }

    file.close();
    return matrix;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Считываем матрицу смежности из файла
    string filename = "graph.txt";
    vector<vector<int>> graph = readAdjacencyMatrix(filename);
    int V = graph.size();

    //транспонированный граф
    vector<vector<int>> transpose(V, vector<int>(V, 0));
    for (int u = 0; u < V; u++) {
        for (int v = 0; v < V; v++) {
            if (graph[u][v]) {
                transpose[v][u] = 1;
            }
        }
    }

    //Первый DFS
    stack<int> finishStack;
    vector<bool> visited(V, false);
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            dfs1(i, graph, visited, finishStack);
        }
    }

    //Второй DFS
    vector<vector<int>> stronglyConnectedComponents;
    fill(visited.begin(), visited.end(), false);
    vector<int> componentMap(V, -1); // Для сопоставления вершины -> КСС
    int componentIndex = 0;         // Индекс текущей КСС

    while (!finishStack.empty()) {
        int node = finishStack.top();
        finishStack.pop();
        if (!visited[node]) {
            vector<int> component;
            dfs2(node, transpose, visited, component);
            for (int v : component) {
                componentMap[v] = componentIndex;
            }
            stronglyConnectedComponents.push_back(component);
            componentIndex++;
        }
    }

    //граф конденсации
    set<pair<int, int>> edges; // Хранит рёбра между КСС (без повторений)
    for (int u = 0; u < V; u++) {
        for (int v = 0; v < V; v++) {
            if (graph[u][v] && componentMap[u] != componentMap[v]) {
                edges.insert({ componentMap[u], componentMap[v] });
            }
        }
    }

    // Вывод КСС
    cout << "Компоненты сильной связности:" << endl;
    for (int i = 0; i < stronglyConnectedComponents.size(); i++) {
        cout << "КСС " << i << ": ";
        for (int v : stronglyConnectedComponents[i]) {
            cout << v << " ";
        }
        cout << endl;
    }

    // Вывод ГК
    cout << "\nГраф конденсации:" << endl;
    if (edges.empty()) {
        cout << "Рёбер между КСС нет." << endl;
    }
    else {
        for (auto edge : edges) {
            cout << edge.first << " -> " << edge.second << endl;
        }
    }

    return 0;
}
