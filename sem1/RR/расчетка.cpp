#include <iostream>
#include <vector>
#include <limits>

using namespace std;

class Graph {
public:
    Graph(int vertices) : V(vertices) {
        adjList.resize(V);
    }

    void addEdge(int src, int dest, bool directed) {
        adjList[src].push_back(dest);
        if (!directed) {
            adjList[dest].push_back(src);
        }
    }

    void printGraph() {
        for (int i = 0; i < V; ++i) {
            cout << "Вершина " << i << " связана с: ";
            for (int neighbor : adjList[i]) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    bool isTree() {
        vector<bool> visited(V, false);
        if (hasCycle(0, visited, -1)) {
            return false;
        }
        for (bool v : visited) {
            if (!v) return false;
        }
        return true;
    }

private:
    int V;
    vector<vector<int>> adjList;

    bool hasCycle(int v, vector<bool>& visited, int parent) {
        visited[v] = true;
        for (int neighbor : adjList[v]) {
            if (!visited[neighbor]) {
                if (hasCycle(neighbor, visited, v)) {
                    return true;
                }
            }
            else if (neighbor != parent) {
                return true;
            }
        }
        return false;
    }
};

int main() {
    setlocale(LC_ALL, "RU");
    int vertices, edges;
    bool directed;

    cout << "Введите количество вершин графа: ";
    while (!(cin >> vertices) || vertices <= 0) {
        cout << "Неверный ввод. Введите положительное целое число: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Введите количество рёбер графа: ";
    while (!(cin >> edges) || edges < 0) {
        cout << "Неверный ввод. Введите неотрицательное целое число: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Ориентированный граф? (0 - нет, 1 - да): ";
    cin >> directed;

    Graph graph(vertices);

    cout << "Введите рёбра графа (формат: src dest):" << endl;
    for (int i = 0; i < edges; ++i) {
        int src, dest;
        while (!(cin >> src >> dest) || src < 0 || src >= vertices || dest < 0 || dest >= vertices) {
            cout << "Неверный ввод. Убедитесь, что src и dest это целые числа от 0 до " << vertices - 1 << ": ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        graph.addEdge(src, dest, directed);
    }

    cout << "Граф:" << endl;
    graph.printGraph();

    if (graph.isTree()) {
        cout << "Граф является деревом." << endl;
    }
    else {
        cout << "Граф не является деревом." << endl;
    }

    return 0;
}

//#include <iostream>
//#include <vector>
//#include <unordered_set>
//
//using namespace std;
//
//class Graph {
//public:
//    Graph(int vertices) : V(vertices) {
//        adjList.resize(V);
//    }
//
//    void addEdge(int src, int dest, bool directed) {
//        adjList[src].push_back(dest);
//        if (!directed) {
//            adjList[dest].push_back(src);
//        }
//    }
//
//    void printGraph() {
//        for (int i = 0; i < V; ++i) {
//            cout << "Вершина " << i << " связана с: ";
//            for (int neighbor : adjList[i]) {
//                cout << neighbor << " ";
//            }
//            cout << endl;
//        }
//    }
//
//    bool isTree() {
//        vector<bool> visited(V, false);
//        if (hasCycle(0, visited, -1)) {
//            return false;
//        }
//        for (bool v : visited) {
//            if (!v) return false;
//        }
//        return true;
//    }
//
//private:
//    int V;
//    vector<vector<int>> adjList;
//
//    bool hasCycle(int v, vector<bool>& visited, int parent) {
//        visited[v] = true;
//        for (int neighbor : adjList[v]) {
//            if (!visited[neighbor]) {
//                if (hasCycle(neighbor, visited, v)) {
//                    return true;
//                }
//            }
//            else if (neighbor != parent) {
//                return true;
//            }
//        }
//        return false;
//    }
//};
//
//int main() {
//    setlocale(LC_ALL, "RU");
//    int vertices, edges;
//    bool directed;
//
//    cout << "Введите количество вершин графа: ";
//    while (!(cin >> vertices)  vertices <= 0) {
//        cout << "Неверный ввод. Введите положительное целое число: ";
//        cin.clear();
//        cin.ignore(numeric_limits<streamsize>::max(), '\n');
//    }
//
//    cout << "Введите количество рёбер графа: ";
//    while (!(cin >> edges)  edges < 0) {
//        cout << "Неверный ввод. Введите неотрицательное целое число: ";
//        cin.clear();
//        cin.ignore(numeric_limits<streamsize>::max(), '\n');
//    }
//
//    cout << "Ориентированный граф? (0 - нет, 1 - да): ";
//    cin >> directed;
//
//    Graph graph(vertices);
//
//    cout << "Введите рёбра графа (формат: src dest):" << endl;
//    for (int i = 0; i < edges; ++i) {
//        int src, dest;
//        while (!(cin >> src >> dest)  src < 0  src >= vertices  dest < 0  dest >= vertices) {
//            cout << "Неверный ввод. Убедитесь, что src и dest это целые числа от 0 до " << vertices - 1 << ": ";
//            cin.clear();
//            cin.ignore(numeric_limits<streamsize>::max(), '\n');
//        }
//        graph.addEdge(src, dest, directed);
//    }
//
//    cout << "Граф:" << endl;
//    graph.printGraph();
//
//    if (graph.isTree()) {
//        cout << "Граф является деревом." << endl;
//    }
//    else {
//        cout << "Граф не является деревом." << endl;
//    }
//
//    return 0;
//}