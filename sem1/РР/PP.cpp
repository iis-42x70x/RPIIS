#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Graph {
    int V;  // Количество вершин
    unordered_map<int, unordered_set<int>> adj;  // Список смежности

public:
    Graph(int V) : V(V) {}

    void addEdge(int u, int v) {
        adj[u].insert(v);
        adj[v].insert(u);
    }

    bool isPlanar() const;

    void removeVertex(int v);

    int vertexDegree(int v) const {
        return adj.at(v).size();
    }

    const unordered_map<int, unordered_set<int>>& getAdjacencyList() const {
        return adj;
    }
};

bool Graph::isPlanar() const {
    int E = 0;
    for (const auto& neighbors : adj) {
        E += neighbors.second.size();
    }
    E /= 2;  // Каждое ребро посчитано дважды

    // Проверка по неравенству E <= 3V - 6 для V >= 3
    return (V < 3) || (E <= 3 * V - 6);
}

void Graph::removeVertex(int v) {
    for (auto neighbor : adj[v]) {
        adj[neighbor].erase(v);
    }
    adj.erase(v);
    V--;  // Уменьшаем количество вершин
}

vector<int> findVerticesToRemove(Graph& g) {
    vector<int> removedVertices;
    while (!g.isPlanar()) {
        // Находим вершину с наибольшей степенью
        int maxDegree = -1;
        int vertexToRemove = -1;
        for (const auto& pair : g.getAdjacencyList()) {
            int degree = g.vertexDegree(pair.first);
            if (degree > maxDegree) {
                maxDegree = degree;
                vertexToRemove = pair.first;
            }
        }
        // Удаляем вершину с наибольшей степенью
        g.removeVertex(vertexToRemove);
        removedVertices.push_back(vertexToRemove);
    }
    return removedVertices;
}

int main() {
    setlocale(LC_ALL, "ru");
    int V, E;
    cout << "Введите количество вершин: ";
    cin >> V;

    Graph g(V);

    cout << "Введите количество рёбер: ";
    cin >> E;

    cout << "Введите рёбра (каждое ребро как две вершины u v):" << endl;
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }

    if (g.isPlanar()) {
        cout << "Граф планарный\n";
    }
    else {
        vector<int> removedVertices = findVerticesToRemove(g);
        cout << "Граф стал планарным после удаления следующих вершин: ";
        for (int v : removedVertices) {
            cout << v << " ";
        }
        cout << endl;
    }

    return 0;
}
