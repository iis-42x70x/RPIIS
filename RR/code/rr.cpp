#include <iostream>
#include <vector>
#include <windows.h>

using namespace std;

// Функция для вычисления пересечения двух матриц смежности
vector<vector<int>> intersection(const vector<vector<int>>& graph1, const vector<vector<int>>& graph2) {
    int n = graph1.size();
    vector<vector<int>> result(n, vector<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            result[i][j] = graph1[i][j] & graph2[i][j]; // Логическое И
        }
    }
    return result;
}

// Функция для вывода матрицы
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int elem : row) {
            cout << elem << " ";
        }
        cout << endl;
    }
}

// Функция для построения матрицы смежности из списка зависимостей
vector<vector<int>> buildMatrix(int n, const vector<pair<int, int>>& edges) {
    vector<vector<int>> matrix(n, vector<int>(n, 0));
    for (const auto& edge : edges) {
        int u = edge.first;
        int v = edge.second;
        matrix[u-1][v-1] = 1;
        matrix[v-1][u-1] = 1; // Для неориентированного графа
    }
    return matrix;
}

int main() {
    setlocale(LC_ALL, "Russian");
    int n, m;

    // Ввод количества вершин и зависимостей для первого графа
    cout << "Введите количество вершин графа: ";
    cin >> n;
    cout << "Введите количество ребер для первого графа: ";
    cin >> m;

    vector<pair<int, int>> edges1(m);
    cout << "Введите ребра первого графа (пары вершин):" << endl;
    for (int i = 0; i < m; ++i) {
        cin >> edges1[i].first >> edges1[i].second;
    }

    // Ввод количества ребер для второго графа
    cout << "Введите количество ребер для второго графа: ";
    cin >> m;

    vector<pair<int, int>> edges2(m);
    cout << "Введите ребра второго графа (пары вершин):" << endl;
    for (int i = 0; i < m; ++i) {
        cin >> edges2[i].first >> edges2[i].second;
    }

    // Построение матриц смежности
    vector<vector<int>> graph1 = buildMatrix(n, edges1);
    vector<vector<int>> graph2 = buildMatrix(n, edges2);

    // Вычисляем пересечение графов
    vector<vector<int>> result = intersection(graph1, graph2);

    // Вывод результата
    cout << "Пересечение графов (матрица смежности):" << endl;
    printMatrix(result);

    return 0;
}