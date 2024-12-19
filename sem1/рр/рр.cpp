//найти радиус неориентированного невзвешенного графа
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int INF = 1e9;

//ф-ция BFS
vector<int> bfs(vector<vector<int>>& graph, int start)
{
    vector<int> dist(graph.size(), INF);
    queue<int> q;
    dist[start] = 0;
    q.push(start);

    while (!q.empty())
    {
        int v = q.front();
        q.pop();

        for (int to = 0; to < graph.size(); to++)
        {
            if (graph[v][to] == 1 && dist[to] == INF)
            {
                dist[to] = dist[v] + 1;
                q.push(to);
            }
        }
    }
    return dist;
}

int main() {
    setlocale(LC_ALL, "ru");
    int n;
    cout << "Введите количество вершин в графе: ";
    cin >> n;
    vector<vector<int>> graph(n, vector<int>(n));

    cout << "Введите матрицу смежности (0 и 1):" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];
        }
    }
    int minEccentricity = INF; 

    for (int start = 0; start < graph.size(); start++) {
        vector<int> dist = bfs(graph, start);

        int Max = 0;
        for (int d : dist) {
            if (d < INF) {
                Max = max(Max, d);
            }
        }
        cout << "Эксцентриситет вершины " << start << ": " << Max << endl;

        minEccentricity = min(minEccentricity, Max);
    }

    cout << "Радиус графа: " << minEccentricity << endl;

    return 0;
}
