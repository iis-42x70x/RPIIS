#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <algorithm>

using namespace std;

vector<int> disc, low, component;
vector<bool> inStack;
stack<int> st;
int timer = 0;

void Scc(int v, const vector<vector<int>>& SmMatr, vector<vector<int>>& sccs) {
    disc[v] = low[v] = ++timer;
    st.push(v);
    inStack[v] = true;

    for (int u = 0; u < SmMatr.size(); ++u) {
        if (SmMatr[v][u] != 0) {
            if (disc[u] == -1) {
                Scc(u, SmMatr, sccs);
                low[v] = min(low[v], low[u]);
            } else if (inStack[u]) {
                low[v] = min(low[v], disc[u]);
            }
        }
    }

    if (low[v] == disc[v]) {
        vector<int> scc;
        while (true) {
            int u = st.top();
            st.pop();
            inStack[u] = false;
            scc.push_back(u);
            component[u] = sccs.size();
            if (u == v) break;
        }
        sccs.push_back(scc);
    }
}

set<pair<int, int>> edges;
void CondGraph(int V, const vector<vector<int>>& adjMatrix, const vector<vector<int>>& sccs) {
    edges.clear();

    for (int v = 0; v < V; ++v) {
        for (int u = 0; u < adjMatrix.size(); ++u) {
            if (adjMatrix[v][u] != 0 && component[v] != component[u]) {
                edges.insert({component[v], component[u]});
            }
        }
    }
}

int main() {
    int V, E;
    cout << "Введите количество вершин и рёбер: ";
    cin >> V >> E;

    vector<vector<int>> incidenceMatrix(V, vector<int>(E, 0));
    cout << "Введите матрицу инцидентности (вершины исходят из -1, входят в +1):" << endl;
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < E; ++j) {
            cin >> incidenceMatrix[i][j];
        }
    }

    vector<vector<int>> MatrSm(V, vector<int>(V, 0));
    for (int j = 0; j < E; ++j) {
        int from = -1, to = -1;
        for (int i = 0; i < V; ++i) {
            if (incidenceMatrix[i][j] == -1) from = i;
            if (incidenceMatrix[i][j] == 1) to = i;
        }
        if (from != -1 && to != -1) {
            MatrSm[from][to] = 1;
        }
    }

    disc.assign(V, -1);
    low.assign(V, -1);
    component.assign(V, -1);
    inStack.assign(V, false);
    vector<vector<int>> sccs;

    for (int i = 0; i < V; ++i) {
        if (disc[i] == -1) {
            Scc(i, MatrSm, sccs);
        }
    }

    CondGraph(V, MatrSm, sccs);

    vector<vector<int>> incMatr(sccs.size(), vector<int>(edges.size(), 0));
    int index = 0;
    for (auto& edge : edges) {
        incMatr[edge.first][index] = -1;
        incMatr[edge.second][index] = 1;
        index++;
    }

    cout << "Матрица инцидентности конденсированного графа:" << endl;
    for (int i = 0; i < incMatr.size(); ++i) {
        for (int j = 0; j < incMatr[i].size(); ++j) {
            cout << incMatr[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
