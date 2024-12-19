#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

const int INF = 2147483647;

int main()
{
    int n;
    cout << "Vvedite kolichestvo vershin v grafe: ";
    cin >> n;
    cin.ignore(); // Очистка буфера после ввода числа

    // Матрица смежности
    vector<vector<int>> matrix(n, vector<int>(n));

    // Ввод элементов матрицы строками через пробел
    cout << "Vvedite elementy matricy smejnosty strokami cherez probel:" << endl;

    for (int i = 0; i < n; i++)
    {
        string line;
        getline(cin, line);
        stringstream ss(line);

        for (int j = 0; j < n; j++)
        {
            if (!(ss >> matrix[i][j]))
            {
                cout << "Oshibka vvoda! Vvodite tolko chisla." << endl;
                return 0;
            }

            // Заменяем нулевые веса на бесконечность, если нет ребра, кроме диагонали
            if (i != j && matrix[i][j] == 0)
            {
                matrix[i][j] = INF;
            }
        }
    }

    // Инициализация матрицы кратчайших расстояний
    vector<vector<int>> dist = matrix;

    // Алгоритм Флойда-Уоршелла
    for (int k = 0; k < n; k++)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (dist[i][k] != INF && dist[k][j] != INF)
                {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    // Нахождение периферийных вершин
    vector<int> peripheralNodes;

    for (int i = 0; i < n; i++)
    {
        int maxDist = 0;

        for (int j = 0; j < n; j++)
        {
            if (dist[i][j] != INF)
            {
                maxDist = max(maxDist, dist[i][j]);
            }
        }

        peripheralNodes.push_back(i); // Добавляем вершину, так как она периферийная
    }

    // Вычисление минимального и среднего расстояния между периферийными вершинами
    int minDistance = INF;
    double totalDistance = 0;
    int pairCount = 0;

    for (int i = 0; i < peripheralNodes.size(); i++)
    {
        for (int j = i + 1; j < peripheralNodes.size(); j++)
        {
            int u = peripheralNodes[i];
            int v = peripheralNodes[j];

            if (dist[u][v] != INF)
            {
                minDistance = min(minDistance, dist[u][v]);
                totalDistance += dist[u][v];
                pairCount++;
            }
        }
    }

    double averageDistance = (pairCount > 0) ? totalDistance / pairCount : 0;

    // Вывод результатов
    cout << "Minimalnoe rasstoyanie mejdy perefiriynymi vershinamy: " << minDistance << endl;
    cout << "Srednee rasstoyanie mejdy perefiriynymy vershinamy: " << averageDistance << endl;

    return 0;
}
