#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> buildShortestPathsTree(const vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> dist(n, INT_MAX);
    vector<int> parent(n, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    const int start = 0;
    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        int current_dist = pq.top().first;
        pq.pop();

        if (current_dist > dist[u]) continue;

        for (int v = 0; v < n; ++v) {
            if (graph[u][v] == 0) continue;

            int weight = graph[u][v];
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    
    vector<vector<int>> tree(n, vector<int>(n, 0));
    for (int v = 0; v < n; ++v) {
        if (parent[v] != -1) {
            tree[parent[v]][v] = graph[parent[v]][v];
        }
    }

    return tree;
}

void printMatrix(const vector<vector<int>>& m) {
    for (const auto& row : m) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
    cout << "----------------\n";
}

int main() {
    vector<vector<int>> ng = {
        {0, 1, 1, 0},
        {1, 0, 1, 1},
        {1, 1, 0, 0},
        {0, 1, 0, 0}
    };

    vector<vector<int>> og = {
        {0, 1, 1, 0, 0},
        {0, 0, 0, 1, 0},
        {0, 1, 0, 0, 1},
        {0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0}
    };

    vector<vector<int>> vng = {
        {0, 3, 2, 0, 0},
        {3, 0, 1, 4, 0},
        {2, 1, 0, 0, 5},
        {0, 4, 0, 0, 2},
        {0, 0, 5, 2, 0}
    };

    vector<vector<int>> vog = {
        {0, 6, 3, 0},
        {0, 0, 0, 1},
        {0, 2, 0, 0},
        {0, 0, 0, 0}
    };

    
    cout << "Tree for ng:\n"; printMatrix(buildShortestPathsTree(ng));
    cout << "Tree for og:\n"; printMatrix(buildShortestPathsTree(og));
    cout << "Tree for vng:\n"; printMatrix(buildShortestPathsTree(vng));
    cout << "Tree for vog:\n"; printMatrix(buildShortestPathsTree(vog));

    return 0;
}