#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <sstream>

using namespace std;

// DFS
void dfs(const vector<vector<int>>& graph, int v, vector<bool>& visited, const set<int>& removedVertices) {
    visited[v] = true;
    for (int neighbor : graph[v]) {
        if (!visited[neighbor] && removedVertices.find(neighbor) == removedVertices.end()) { //мнво удаленных вершин
            dfs(graph, neighbor, visited, removedVertices);
        }
    }
}

//компоненты связности
int concomp(const vector<vector<int>>& graph, int vertexCount, const set<int>& removedVertices) {
    vector<bool> visited(vertexCount, false);//массив visited длиной vertexCount
    int components = 0;

    for (int i = 0; i < vertexCount; i++) {
        if (!visited[i] && removedVertices.find(i) == removedVertices.end()) {
            dfs(graph, i, visited, removedVertices);
            components++;
        }
    }

    return components;
}

int main() {
    setlocale(LC_ALL, "RU");

    ifstream file("test.txt");
    if (!file.is_open()) {
        cout << "Ошибка при чтении файла" << endl;
        return 1;
    }

    for (int g = 1; g <= 5; g++) {
        int vertexCount, edgeCount;

        string line;
        while (getline(file, line) && line.empty());

        if (line.empty()) break;//конец файла

        stringstream ss(line);
        ss >> vertexCount >> edgeCount;

        vector<vector<int>> graph(vertexCount);

        // чиение списка смежности
        for (int i = 0; i < vertexCount; i++) {
            getline(file, line);
            stringstream ss(line);

            int vertex, neighbor;
            ss >> vertex;
            vertex--;

            while (ss >> neighbor) {
                neighbor--;
                graph[vertex].push_back(neighbor);
            }
        }

        //если несвязн
        if (concomp(graph, vertexCount, {}) > 1) {
            cout << "Число вершинной связности для графа " << g << ": 0" << endl;
            continue;
        }

        int сonnectivity = 1e9;

        // перебор всех подмножеств вершин
        for (int mask = 1; mask < (1 << vertexCount); mask++) {
            set<int> removedVertices;
            for (int i = 0; i < vertexCount; i++) {
                if (mask & (1 << i)) {//включена ли вершина
                    removedVertices.insert(i);
                }
            }

            int components = concomp(graph, vertexCount, removedVertices);

            // Если граф стал несвязным (компонент > 1)
            if (components > 1) {
                сonnectivity = min(сonnectivity, (int)removedVertices.size());
            }
        }

        cout << "Число вершинной связности для графа " << g << ": " << сonnectivity << endl;
    }

    file.close();
    return 0;
}

