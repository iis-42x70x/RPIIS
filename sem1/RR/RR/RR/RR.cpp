#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <queue>

using namespace std;

const int INF = 1e9;

string example(short int choose) {
    string filename;

    switch (choose) {
    case 1: {
        filename = "example1.txt"; break; 
    }
    case 2: {
        filename = "example2.txt"; break;
    }
    case 3: {
        filename = "example3.txt"; break; 
    }
    case 4: {
        filename = "example4.txt"; break; 
    }
    case 5: {
        filename = "example5.txt"; break; 
    }
    default: {
        cout << "Ожидалось 1-5. Введено:" << choose;
        exit(0);
        break;
    }
    }
    return filename;
}

vector<vector<int>> read_file(string& filename) {

    ifstream file;

    file.open(filename);
    if (!file.is_open()) {
        cout << "! Ошибка при открытии файла !" << endl;
        exit(0);
    }

    string line;

    vector<vector<int>> graph;

    while (getline(file, line)) {
        stringstream s(line);

        int vertex;
        s >> vertex;
        if (vertex >= graph.size())
            graph.resize(vertex + 1);

        vector<int> neighbors;
        int neighbor;
        while (s >> neighbor) {
            neighbors.push_back(neighbor);
        }
        graph[vertex] = neighbors;
    }
    file.close();

    return graph;
}

vector<int> bfs(vector<vector<int>>& graph, int start) {

    vector<int> distance(graph.size(), INF);
    queue<int> q;

    distance[start] = 0;
    q.push(start);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        for (int neighbor : graph[current]) {
            if (distance[neighbor] == INF) {
                distance[neighbor] = distance[current] + 1;
                q.push(neighbor);
            }
        }
    }
    return distance;
}

bool connected(vector<vector<int>>& graph) {
    vector<int> dist = bfs(graph, 0);

    for (int elem : dist) {
        if (elem == INF)
            return false;
    }
    return true;
}

double average_diameter(vector<vector<int>>& graph) {

    double sumdist = 0;
    int num = 0;

    for (int start = 0; start < graph.size(); start++) {
        vector<int> dist = bfs(graph, start);
        for (int end = 0; end < graph.size(); end++) {

            if (start != end && dist[end] != INF) {
                sumdist += dist[end];
                num++;
            }
        }
    }

    return sumdist / num;

}

int main() {
    setlocale(LC_ALL, "RU");
    short int choose;
    string filename;
    cout << "1. Пример 1.\n2. Пример 2.\n3. Пример 3.\n4. Пример 4.\n5. Пример 5.\nСделайте выбор: ";
    cin >> choose;
    cout << endl;

    filename = example(choose);

    vector<vector<int>> graph = read_file(filename);

    if (!connected(graph)) {
        cout << "Средний диаметр неопределен(граф несвязный)" << endl;
        exit(1);
    }

    cout << "Средний диаметр равен: " << average_diameter(graph) << endl;

    return 0;
}