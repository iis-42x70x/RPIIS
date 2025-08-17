#include <iostream>
#include <vector>

using namespace std;

// Функция для вычисления матрицы смежности из матрицы инцидентности
vector<vector<int>> calculateAdjacencyMatrix(const vector<vector<int>>& incidenceMatrix) {
    int vertices = incidenceMatrix.size(); // Число вершин
    int edges = incidenceMatrix[0].size(); // Число рёбер

    // Матрица смежности
    vector<vector<int>> adjacencyMatrix(vertices, vector<int>(vertices, 0));

    // Перебираем рёбра и отмечаем связи между вершинами
    for (int e = 0; e < edges; ++e) {
        int v1 = -1, v2 = -1;

        // Ищем вершины, которые соединяет это ребро
        for (int v = 0; v < vertices; ++v) {
            if (incidenceMatrix[v][e] == 1) {
                if (v1 == -1) {
                    v1 = v; // Первая вершина
                }
                else {
                    v2 = v; // Вторая вершина
                    break;
                }
            }
        }

        // Если нашли две вершины для ребра, обновляем матрицу смежности
        if (v1 != -1 && v2 != -1) {
            adjacencyMatrix[v1][v2] = 1;
            adjacencyMatrix[v2][v1] = 1; // Так как граф неориентированный
        }
    }

    return adjacencyMatrix;
}

// Функция для вывода матрицы
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

int main() {
	setlocale(LC_ALL, "Russian");
    int vertices, edges;

    // Ввод числа вершин и рёбер
    cout << "Введите количество вершин: ";
    cin >> vertices;

    cout << "Введите количество рёбер: ";
    cin >> edges;

    // Матрица инцидентности
    vector<vector<int>> incidenceMatrix(vertices, vector<int>(edges, 0));

    cout << "Введите матрицу инцидентности построчно:" << endl;
    for (int i = 0; i < vertices; ++i) {
        cout << "Вершина " << i + 1 << ": ";
        for (int j = 0; j < edges; ++j) {
            cin >> incidenceMatrix[i][j];
        }
    }

    // Вывод введённой матрицы инцидентности
    cout << "\nМатрица инцидентности:" << endl;
    printMatrix(incidenceMatrix);

    // Вычисляем матрицу смежности
    vector<vector<int>> adjacencyMatrix = calculateAdjacencyMatrix(incidenceMatrix);

    // Вывод матрицы смежности
    cout << "\nМатрица смежности:" << endl;
    printMatrix(adjacencyMatrix);

    return 0;
}
