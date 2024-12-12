#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <set>
#include <locale>
using namespace std;

void DFS(const vector<vector<int>>& graph, int n, vector<bool>& visited) {
    visited[n] = true;
    for (int neighbor : graph[n]) {
        if (!visited[neighbor]) {
            DFS(graph, neighbor, visited);
        }
    }
}

bool is_connected(const vector<vector<int>>& graph, int n) {
    vector<bool> visited(n, false);
    DFS(graph, 0, visited);
    for (bool v : visited) {
        if (!v) return false;
    }
    return true;
}

vector<vector<int>> write_ribs(const vector<vector<int>>& graph) {
    vector<vector<int>> ribs_list;
    for (int i = 0; i < graph.size(); i++) {
        for (int j : graph[i]) {
            if (i < j) {
                ribs_list.push_back({ i, j });
            }
        }
    }
    return ribs_list;
}

void solve(vector<vector<int>> graph, int& ribs_del_num, vector<int>& end_list) {
    if (!is_connected(graph, graph.size())) {
        end_list.push_back(write_ribs(graph).size());
        return;
    }

    vector<vector<int>> ribs_list = write_ribs(graph);
    int ribs_on_this_step = ribs_list.size();

    for (int i = 0; i < ribs_on_this_step; i++) {
        
        vector<vector<int>> buf_graph = graph;
        buf_graph[ribs_list[i][0]].erase(remove(buf_graph[ribs_list[i][0]].begin(), buf_graph[ribs_list[i][0]].end(), ribs_list[i][1]), buf_graph[ribs_list[i][0]].end());
        buf_graph[ribs_list[i][1]].erase(remove(buf_graph[ribs_list[i][1]].begin(), buf_graph[ribs_list[i][1]].end(), ribs_list[i][0]), buf_graph[ribs_list[i][1]].end());

        ribs_del_num++;
        solve(buf_graph, ribs_del_num, end_list);
    }
}

int main() {
    setlocale(LC_ALL, "RU");

    int ribs_del_num = 0;
    int max_unconnect = -1;
    int ribs_start_num;

    vector<int> end_list_2;
    vector<vector<int>> graph;

    int n, number_buf;
    string input_buf;

    cout << "Введите количество вершин графа: ";
    cin >> n;
    graph.resize(n);

    cout << "Введите список смежности графа:" << endl;
    cin.ignore();

    for (int i = 0; i < n; i++) {
        cout << i << ": ";
        getline(cin, input_buf);
        istringstream stream_buf(input_buf);
        while (stream_buf >> number_buf) {
            graph[i].push_back(number_buf);
        }
    }

    ribs_start_num = write_ribs(graph).size();

    solve(graph, ribs_del_num, end_list_2);

    cout << ribs_del_num << endl;

    //for (int i = 0; i < end_list_2.size(); i++) {
    //    cout << end_list_2[i] << " ";
    //    if (i % 10 == 0) cout << endl;
    //}

    for (int val : end_list_2) {
        max_unconnect = max(max_unconnect, val);
    }

    cout << "Ответ: " << (ribs_start_num - max_unconnect) << endl;

    return 0;
}
