#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <sstream>

using namespace std;

void dfs(int v, vector<bool>& visited, const map<int, vector<int>>& adj_list, vector<int>& component) {
    visited[v] = true;
    component.push_back(v);
    for (int neighbor : adj_list.at(v)) {
        if (!visited[neighbor]) {
            dfs(neighbor, visited, adj_list, component);
        }
    }
}

vector<vector<int>> find_connected_components(int n, const map<int, vector<int>>& adj_list) {
    vector<bool> visited(n + 1, false);
    vector<vector<int>> components;

    for (const auto& [vertex, _] : adj_list) {
        if (!visited[vertex]) {
            vector<int> component;
            dfs(vertex, visited, adj_list, component);
            components.push_back(component);
        }
    }

    return components;
}

int main() {
    int n;
    cout << "Введите количество вершин: ";
    cin >> n;

    map<int, vector<int>> adj_list;
    cin.ignore();

    cout << "Введите список смежности (по одной строке для каждой вершины):\n";
    for (int i = 1; i <= n; i++) {
        string line;
        getline(cin, line);
        stringstream ss(line);

        int vertex;
        ss >> vertex;

        int neighbor;
        while (ss >> neighbor) {
            adj_list[vertex].push_back(neighbor);
        }

        if (adj_list.find(vertex) == adj_list.end()) {
            adj_list[vertex] = {};
        }
    }

    vector<vector<int>> components = find_connected_components(n, adj_list);

    cout << "Количество компонент связности: " << components.size() << endl;

    for (size_t i = 0; i < components.size(); i++) {
        cout << "Вершины, принадлежащие " << (i + 1) << "-ой компоненте: ";
        for (size_t j = 0; j < components[i].size(); j++) {
            cout << components[i][j];
            if (j < components[i].size() - 1) cout << " ";
        }
        cout << endl;
    }

    return 0;
}

