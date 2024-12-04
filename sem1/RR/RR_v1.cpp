#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <string>

using namespace std;

// Чтение матрицы смежности из файла
vector<vector<int>> readMatrix(const string& filename) 
{
    ifstream file(filename);
  
    int n;
    file >> n;
  
    vector<vector<int>> matrix(n, vector<int>(n));
    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            file >> matrix[i][j];
        }
    }
    return matrix;
}

// Алгоритм для поиска числа вершинной связности (далее ЧВС)
int vertexConnectivity(const vector<vector<int>>& matrix) 
{
    int n = matrix.size();
    // Начальное значение для ЧВС ставим максимально большим
    int minCut = INT_MAX;

    for (int source = 0; source < n; ++source) 
    {
        for (int target = source + 1; target < n; ++target) 
        {
            // Копируем исходную матрицу
            vector<vector<int>> graph = matrix;
            // Вектор для хранения пути
            vector<int> parent(n, -1);
            // Вектор для хранения посещенных вершин
            vector<bool> visited(n, false);

            // Лямбда функция для BFS 
            auto bfs = [&](int s, int t) -> bool 
                {
                fill(visited.begin(), visited.end(), false);
                queue<int> q;
                q.push(s);
                visited[s] = true;
                parent[s] = -1;

                while (!q.empty()) 
                {
                    int u = q.front();
                    q.pop();

                    for (int v = 0; v < n; ++v) 
                    {
                        // Если вершина не посещена и есть ребро
                        if (!visited[v] && graph[u][v] > 0) 
                        {
                            if (v == t) 
                            {
                                parent[v] = u;
                                return true;
                            }
                            q.push(v);
                            parent[v] = u;
                            visited[v] = true;
                        }
                    }
                }
                return false;
                };

            int maxFlow = 0;
            
            while (bfs(source, target)) // Пока существует путь от источника к цели 
            {
                int pathFlow = INT_MAX;
                
                for (int v = target; v != source; v = parent[v]) // Нахожу ЧВС
                {
                    int u = parent[v];
                    pathFlow = min(pathFlow, graph[u][v]);
                }
              
                for (int v = target; v != source; v = parent[v]) // Обновляем остаточнрё растояние до рёбер
                {
                    int u = parent[v];
                    graph[u][v] -= pathFlow;
                    graph[v][u] += pathFlow;
                }
                maxFlow += pathFlow;
            }
          
            minCut = min(minCut, maxFlow); // Обновляю ЧВС
        }
    }
    return minCut;
}

// Функция для вывода матрицы
void printMatrix(const vector<vector<int>>& matrix) 
{
    for (const auto& row : matrix) 
    {
        for (int val : row) 
        {
            cout << val << " ";
        }
        cout << endl;
    }
}

int main() 
{
    setlocale(LC_ALL, "Russian");
    vector<vector<int>> matrices[5]; 
    for (int i = 0; i < 5; ++i) 
    { 
        matrices[i] = readMatrix("NG" + to_string(i + 1) + ".txt"); 
    }
    for (int i = 0; i < 5; ++i) 
    {
        cout << "матрица смежности для " << i + 1 << "-ого графа:\n";
        printMatrix(matrices[i]);

        int connectivity = vertexConnectivity(matrices[i]);
        cout << "Число вершинной связности графа: " << connectivity << endl;
        cout << endl;
    }
    return 0;
}
