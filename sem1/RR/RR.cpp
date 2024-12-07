#include <iostream>
#include <vector>
using namespace std;

// Функция для проверки, является ли граф связным
bool isConnected(vector<vector<int>>& incidenceMatrix, int vertices) {
    vector<bool> visited(vertices, false);
    vector<int> stack;
    int startVertex = -1;

    // Найти первую вершину с ребрами
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < incidenceMatrix[i].size(); j++) {
            if (incidenceMatrix[i][j] == 1) {
                startVertex = i;
                break;
            }
        }
        if (startVertex != -1) break;
    }

    if (startVertex == -1) return false; // Нет ребер в графе

    stack.push_back(startVertex);
    visited[startVertex] = true;
    //Обход графа в глубину
    while (!stack.empty()) {
        int v = stack.back();
        stack.pop_back();

        for (int i = 0; i < incidenceMatrix[v].size(); i++) {
            if (incidenceMatrix[v][i] == 1) {
                for (int u = 0; u < vertices; u++) {
                    if (incidenceMatrix[u][i] == 1 && u != v && !visited[u]) {
                        visited[u] = true;
                        stack.push_back(u);
                    }
                }
            }
        }
    }

    // Проверка, все ли вершины с ребрами посещены
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < incidenceMatrix[i].size(); j++) {
            if (incidenceMatrix[i][j] == 1 && !visited[i]) {
                return false;
            }
        }
    }

    return true;
}

// Функция для поиска Эйлерова цикла
void findEulerianCycle(vector<vector<int>>& incidenceMatrix, int vertices) {
    if (!isConnected(incidenceMatrix, vertices)) {
        cout << "Граф не является связным, Эйлеров цикл невозможен." << endl;
        return;
    }
    //Проходим по каждой строке матрицы для подсчета степени вершин
    vector<int> degree(vertices, 0);
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < incidenceMatrix[i].size(); j++) {
            if (incidenceMatrix[i][j] == 1) {
                degree[i]++;
            }
        }
    }
    //Проверка на наличие вершин с нечетной степенью
    for (int i = 0; i < vertices; i++) {
        if (degree[i] % 2 != 0) {
            cout << "Граф имеет вершину с нечетной степенью, Эйлеров цикл невозможен." << endl;
            return;
        }
    }
    
    vector<int> currentPath;
    vector<int> circuit;
    currentPath.push_back(0);
    int currentVertex = 0;
    //Построение Эйлерова цикла
    while (!currentPath.empty()) {
        if (degree[currentVertex] != 0) {
            currentPath.push_back(currentVertex);
            int nextVertex = -1;
            for (int i = 0; i < incidenceMatrix[currentVertex].size(); i++) {
                if (incidenceMatrix[currentVertex][i] == 1) {
                    for (int j = 0; j < vertices; j++) {
                        if (incidenceMatrix[j][i] == 1 && j != currentVertex) {
                            nextVertex = j;
                            break;
                        }
                    }
                    incidenceMatrix[currentVertex][i] = 0;
                    incidenceMatrix[nextVertex][i] = 0;
                    degree[currentVertex]--;
                    degree[nextVertex]--;
                    currentVertex = nextVertex;
                    break;
                }
            }
            if (nextVertex == -1) {
                cout << "Не удалось найти следующую вершину." << endl;
                return;
            }
        }
        else {
            circuit.push_back(currentVertex);
            currentVertex = currentPath.back();
            currentPath.pop_back();
        }
    }
    //Вывод Эйлерова цикла
    cout << "Эйлеров цикл: ";
    for (int i = circuit.size() - 1; i >= 0; i--) {
        cout << circuit[i] + 1 << " ";
    }
    cout << endl;
}

int main() {
    int vertices, edges;
    setlocale(LC_ALL, "Russian");
    cout << "Введите количество вершин: ";
    cin >> vertices;
    cout << "Введите количество ребер: ";
    cin >> edges;

    vector<vector<int>> incidenceMatrix(vertices, vector<int>(edges, 0));

    cout << "Введите элементы матрицы инцидентности:" << endl;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < edges; j++) {
            cin >> incidenceMatrix[i][j];
        }
    }
    cout << "Введенная матрица инцидентности: " << endl;
    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < edges; j++)
        {
            cout << incidenceMatrix[i][j] << " ";
        }
        cout << endl;
    }
    findEulerianCycle(incidenceMatrix, vertices);
    return 0;
}