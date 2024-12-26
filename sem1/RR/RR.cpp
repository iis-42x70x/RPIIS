#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>


using namespace std;

class Graph {
private:
    int V;
    vector<vector<int>> adj;

public:
    Graph(int V) {
        this->V = V; 
        adj.resize(V); 
    }

    void addEdge(int v, int w) {
        adj[v].push_back(w);
        adj[w].push_back(v);
    }

    void printGraph() {
        for (int i = 0; i < V; i++) {
            cout << "Вершина " << i << ": ";
            for (int j : adj[i]) {
                cout << j << " ";
            }
            cout << endl;
        }
    }

    vector<int> BFS(int start) {
        vector<int> distance(V, INT_MAX);
        queue<int> q;
        q.push(start);
        distance[start] = 0;

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int neighbor : adj[v]) {
                if (distance[neighbor] == INT_MAX) {
                    distance[neighbor] = distance[v] + 1;
                    q.push(neighbor);
                }
            }
        }
        return distance;
    }

    int findRadius() {
        int radius = INT_MAX;

        for (int i = 0; i < V; i++) {
            vector<int> distances = BFS(i);
            int maxDistance = 0;

            for (int d : distances) {
                if (d != INT_MAX) { 
                    maxDistance = max(maxDistance, d);
                }
            }

            if (maxDistance < radius) {
                radius = maxDistance;
            }
        }
        return radius;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    int n, m, x, y;

    cout << "Количество вершин:\n";
    cin >> n;
    Graph g(n);

    cout << "Количество рёбер:\n";
    cin >> m;

    cout << "Введите ребра смежности: \n";
    for (int i = 0; i < m; i++) {
        cin >> x;
        cin >> y;
        g.addEdge(x, y);
    }

    g.printGraph();

    int radius = g.findRadius();
    cout << "Радиус графа: " << radius << endl;

    return 0;
}
