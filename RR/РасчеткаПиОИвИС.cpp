#include <iostream>
#include <cstring> // Для memset

using namespace std;

const int MAX_VERTICES = 100; // Максимальное количество вершин
const int MAX_EDGES = 100; // Максимальное количество ребер

// Функция обхода в глубину (DFS)
void dfs(int graph[MAX_VERTICES][MAX_EDGES], bool visited[], int vertex, int numVertices, int numEdges) {
    visited[vertex] = true; // Помечаем вершину как посещенную
    cout << vertex << " "; // Выводим вершину

    // Обходим все ребра
    for (int j = 0; j < numEdges; j++) {
        // Проверяем, инцидентно ли ребро вершине
        if (graph[vertex][j] == 1) {
            // Находим другую вершину, инцидентную этому ребру
            for (int i = 0; i < numVertices; i++) {
                if (i != vertex && graph[i][j] == 1 && !visited[i]) {
                    dfs(graph, visited, i, numVertices, numEdges); // Рекурсивный вызов для соседней вершины
                }
            }
        }
    }
}

// Функция поиска компонент связности
void findConnectedComponents(int graph[MAX_VERTICES][MAX_EDGES], int numVertices, int numEdges) {
    bool visited[MAX_VERTICES];
    memset(visited, false, sizeof(visited)); // Инициализируем массив посещенных вершин

    for (int i = 0; i < numVertices; i++) {
        if (!visited[i]) { // Если вершина еще не посещена
            cout << "Компонента связности: ";
            dfs(graph, visited, i, numVertices, numEdges); // Запускаем DFS
            cout << endl; // Переход на новую строку после компоненты
        }
    }
}

int main() {
    setlocale(LC_ALL, ""); // Установка локализации
    int numVertices; // Количество вершин
    int numEdges; // Количество ребер
    int graph[MAX_VERTICES][MAX_EDGES]; // Матрица инцидентности

    cout << "Введите количество вершин: ";
    cin >> numVertices;

    cout << "Введите количество ребер: ";
    cin >> numEdges;

    cout << "Введите матрицу инцидентности (0 или 1):" << endl;
    for (int i = 0; i < numVertices; i++) {
        for (int j = 0; j < numEdges; j++) {
            cin >> graph[i][j]; // Заполнение матрицы
        }
    }

    cout << "Компоненты связности графа:" << endl;
    findConnectedComponents(graph, numVertices, numEdges);

    return 0;
}