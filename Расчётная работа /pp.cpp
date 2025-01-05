
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Функция для проверки на ацикличность с использованием матрицы инцидентности
bool isAcyclicIncidence(vector<vector<int>>& inc) {
    int n = inc.size(); // количество вершин
    int m = inc[0].size(); // количество ребер

    vector<int> color(n, 0); // 0 - белый, 1 - серый, 2 - черный
    vector<vector<int>> adj(n, vector<int>(n, 0)); // временная матрица смежности

    // Построение матрицы смежности из матрицы инцидентности
    for (int j = 0; j < m; j++) {
        int first = -1, second = -1;
        for (int i = 0; i < n; i++) {
            if (inc[i][j] == 1) {
                if (first == -1) {
                    first = i;
                }
                else {
                    second = i;
                    break;
                }
            }
        }
        if (first != -1 && second != -1) {
            adj[first][second] = 1;
            adj[second][first] = 1;
        }
    }

    // Поиск в ширину для проверки на ацикличность
    for (int start = 0; start < n; start++) {
        if (color[start] != 0) continue;

        queue<int> q;
        vector<int> parent(n, -1);

        q.push(start);
        color[start] = 1;

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            for (int u = 0; u < n; u++) {
                if (adj[v][u] == 0) continue;

                if (color[u] == 0) {
                    color[u] = 1;
                    parent[u] = v;
                    q.push(u);
                }
                else if (color[u] == 1 && u != parent[v]) {
                    return false; // найден цикл
                }
            }
            color[v] = 2;
        }
    }
    return true; // циклов нет
}

int main() {
    setlocale(LC_ALL, "ru");
    int n, m;
    cout << "Введите количество вершин и ребер: ";
    cin >> n >> m;

    // Ввод матрицы инцидентности
    vector<vector<int>> inc(n, vector<int>(m));
    cout << "Введите матрицу инцидентности:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> inc[i][j];
        }
    }

    // Проверка на ацикличность
    if (isAcyclicIncidence(inc)) {
        cout << "Граф является ациклическим" << endl;
    }
    else {
        cout << "Граф не является ациклическим" << endl;
    }

    return 0;
}



