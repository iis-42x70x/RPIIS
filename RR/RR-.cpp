#include <iostream>
#include <vector>
using namespace std;

class Graph {
public:
    int V;
    vector<vector<int>> adj;

    Graph(int V) {
        this->V = V;
        adj = vector<vector<int>>(V, vector<int>(V, 0));
    }

    void addReb(int u, int v) {
        adj[u][v] = 1;
    }

    void DFS(int v, vector<bool>& visited) {
        visited[v] = true;
        for (int i = 0; i < V; i++) {
            if (adj[v][i] && !visited[i]) {
                DFS(i, visited);
            }
        }
    }

    bool isCon() {
        vector<bool> visited(V, false);
        DFS(0, visited);
        
        for (int i = 0; i < V; i++) {
            if (!visited[i]) return false;
        }
        return true;
    }

    int minRebToRem() {
        int RebRem = 0;

        for (int u = 0; u < V; u++) {
            for (int v = u + 1; v < V; v++) {
                if (adj[u][v]) {
                    
                    adj[u][v] = 0;
                    adj[v][u] = 0;
                    
                    if (!isCon()) {
                        RebRem++;
                    }
                    adj[u][v] = 1;
                    adj[v][u] = 1;
                }
            }
        }
        return RebRem;
    }
};

int main() {
    int V, E;
    cout << "Введите количество вершин: ";
    cin >> V;
    Graph g(V);

    cout << "Введите количество рёбер: ";
    cin >> E;

    cout << "Введите рёбра (u v):" << endl;
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        g.addReb(u, v);
    }

    int result = g.minRebToRem();
    cout << "Минимальное количество рёбер, которые нужно удалить для разъединения графа: " << result << endl;
    return 0;
}