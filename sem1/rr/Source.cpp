#include <iostream>
#include <vector>

using namespace std;

void dfs(vector < vector<int> > graph, vector<int>& metki, int v0, int kol) {
    metki[v0] = kol;
    for (int j = 0; j < graph[v0].size(); j++) {
        if (!metki[graph[v0][j]]) {
            dfs(graph, metki, graph[v0][j], kol);
        }
    }
}

void poisk_komp(vector < vector<int> > graph, int v) {
    int kol = 1;
    vector<int> metki(v);
    for (int i = 0; i < v; i++) {
        if (!metki[i]) {
            dfs(graph, metki, i, kol);
            kol++;
        }
    }
    kol--;
    vector<vector<int>>komp(kol);
    for (int i = 0; i < v; i++) {
        komp[metki[i] - 1].push_back(i);
    }
    cout << endl << "Количество компонент связности: " << kol << endl;
    for (int i = 0; i < kol; i++) {
        cout << "Вершины принадлежащие " << i + 1 << "-ой компоненте: ";
        for (int j = 0; j < komp[i].size(); j++) {
            cout << komp[i][j] << ' ';
        }
        cout << endl;
    }
}

void graph1(vector < vector<int> >& graph, int& v) {
    v = 10;
    graph.resize(v);
    graph[0] = { 1,2 };
    graph[1] = { 0,4,8 };
    graph[2] = { 0 };
    graph[3] = { 6,7 };
    graph[4] = { 1 };
    graph[5] = {};
    graph[6] = { 3 };
    graph[7] = { 3,9 };
    graph[8] = { 1 };
    graph[9] = { 7 };
    poisk_komp(graph, v);
}

void graph2(vector < vector<int> >& graph, int& v) {
    v = 8;
    graph.resize(v);
    graph[0] = { 1,3 };
    graph[1] = { 0,2,3 };
    graph[2] = { 1 };
    graph[3] = { 0,1,5,6 };
    graph[4] = { 7 };
    graph[5] = { 3,6 };
    graph[6] = { 3,5 };
    graph[7] = { 4 };
    poisk_komp(graph, v);
}

void graph3(vector < vector<int> >& graph, int& v) {
    v = 4;
    graph.resize(v);
    graph[0] = { 1,2,3 };
    graph[1] = { 0 };
    graph[2] = { 0 };
    graph[3] = { 0 };
    poisk_komp(graph, v);
}

void graph4(vector < vector<int> >& graph, int& v) {
    v = 6;
    graph.resize(v);
    graph[0] = { 1,2 };
    graph[1] = { 0,2 };
    graph[2] = { 0,1 };
    graph[3] = {};
    graph[4] = { 5 };
    graph[5] = { 4 };
    poisk_komp(graph, v);
}

void graph5(vector < vector<int> >& graph, int& v) {
    v = 5;
    graph.resize(v);
    graph[0] = { 1 };
    graph[1] = { 0 };
    graph[2] = { 3 };
    graph[3] = {2,4};
    graph[4] = { 3 };
    poisk_komp(graph, v);
}
int main()
{
    setlocale(LC_ALL, "RU");
    vector < vector<int> > graph;
    int v;
    graph1(graph, v);
    graph2(graph, v);
    graph3(graph, v);
    graph4(graph, v);
    graph5(graph, v);
    return 0;
}