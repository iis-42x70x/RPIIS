#include <iostream>
#include <vector>
#include <queue>

using namespace std;

bool isConnected(const vector<vector<int>>& graph) {
    int n = graph.size();
    if (n == 0) return false;

    vector<bool> visited(n, false);
    queue<int> q;
    q.push(0);
    visited[0] = true;

    int visitedCount = 0;

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        ++visitedCount;

        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    return visitedCount == n; // Все вершины должны быть посещены
}

bool isTree(const vector<vector<int>>& graph) {
    int n = graph.size();
    int edgeCount = 0;

    // Подсчёт количества рёбер
    for (const auto& neighbors : graph) {
        edgeCount += neighbors.size();
    }
    edgeCount /= 2; // Так как граф неориентированный

    // Условие для дерева
    return isConnected(graph) && edgeCount == n - 1;
}

int main() {
    vector<vector<int>> graph_1{
        {1},
        { 0, 2, 3 },
        { 1 },
        { 1 }
    };

    vector<vector<int>> graph_2{
        {1, 2},
        { 0, 2 },
        { 0, 1, 3 },
        { 2 }
    };

    if (isTree(graph_1)) {
        cout << "Graph_1 is a tree." << endl;
    }
    else {
        cout << "Graph_1 is not a tree." << endl;
    }

    if (isTree(graph_2)) {
        cout << "Graph_2 is a tree." << endl;
    }
    else {
        cout << "Graph_2 is not a tree." << endl;
    }

    return 0;
}
