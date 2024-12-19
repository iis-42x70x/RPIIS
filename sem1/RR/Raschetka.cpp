#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int max_vertex_degree(const vector<vector<int>>& graph) {
    int max_degree = 0; // Начальное значение для максимальной степени вершины
    for (const auto& neighbors : graph) {
        max_degree = max(max_degree, static_cast<int>(neighbors.size())); // Сравниваем и обновляем максимальную степень
    }
    return max_degree; // Возвращаем максимальную степень
}

void print_graph_and_max_degree(const vector<vector<int>>& graph) {
    cout << "Граф:" << endl;
    for (int i = 0; i < graph.size(); i++) {
        cout << "Вершина " << i << ": ";
        for (int neighbor : graph[i]) {
            cout << neighbor << ' ';
        }
        cout << endl;
    }
    cout << "Максимальная степень вершины: " << max_vertex_degree(graph) << endl; // Печатаем максимальную степень
}

void graph1(vector < vector<int> >& graph, int& v) {
    v = 7;
    graph.resize(v);
    graph[0] = { 1 };
    graph[1] = { 0,2,3,4,5 };
    graph[2] = { 1,6 };
    graph[3] = { 1 };
    graph[4] = { 1,5 };
    graph[5] = { 1,4,6 };
    graph[6] = { 2,5 };
    print_graph_and_max_degree(graph);
}

void graph2(vector < vector<int> >& graph, int& v) {
    v = 8;
    graph.resize(v);
    graph[0] = { 1,2,6 };
    graph[1] = { 0,2,3 };
    graph[2] = { 0,1 };
    graph[3] = { 1,4 };
    graph[4] = { 3,5 };
    graph[5] = { 4,6 };
    graph[6] = { 0,5,7 };
    graph[7] = { 6 };
    print_graph_and_max_degree(graph);
}

void graph3(vector < vector<int> >& graph, int& v) {
    v = 5;
    graph.resize(v);
    graph[0] = { 1,2,3 };
    graph[1] = { 0,3 };
    graph[2] = { 0 };
    graph[3] = { 0,1 };
    graph[4] = {};
    print_graph_and_max_degree(graph);
}

void graph4(vector < vector<int> >& graph, int& v) {
    v = 6;
    graph.resize(v);
    graph[0] = { 1,4 };
    graph[1] = { 0,2,3,5 };
    graph[2] = { 1 };
    graph[3] = { 1,5 };
    graph[4] = { 0,5 };
    graph[5] = { 1,3,4 };
    print_graph_and_max_degree(graph);
}

void graph5(vector < vector<int> >& graph, int& v) {
    v = 5;
    graph.resize(v);
    graph[0] = { 1,3 };
    graph[1] = { 0,2 };
    graph[2] = { 1,3 };
    graph[3] = { 0,4 };
    graph[4] = { 3 };
    print_graph_and_max_degree(graph);
}


int main() {
    setlocale(LC_ALL, "RU");
    vector<vector<int>> graph;
    int v;
    graph1(graph, v);
    graph2(graph, v);
    graph3(graph, v);
    graph4(graph, v);
    graph5(graph, v);
    return 0;
}
