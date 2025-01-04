#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#define INT_MAX 2147483647

using namespace std;

void output(vector<vector<int>>& ans, int n) 
{
    cout << "  ";
    for (int i = 0; i < n; i++)
        cout << setw(3) << i;
    cout << endl;
    for (int i = 0; i < n; i++) {
        cout << i << "||";
        for (int& it : ans[i]) {
            cout << setw(3) << it;
        }
        cout << endl;
    }
}

void bfs(vector<vector<int>>& graph)
{
    int n = graph.size();
    vector<vector<int>> ans(n, vector<int>(n, 0));     // матрица смежности кратчайших путей
    vector<int> len(n, INT_MAX);      // вектор кратчайших путей
    vector<int> prev(n, -1);
    queue<int> node;       // очередь вершин, которым предстоит проверка

    len[0] = 0;
    node.push(0);

    while (!node.empty()) {
        int pos = node.front();    // текущая позиция
        node.pop();

        // проверяем текущую вершину и добавляем её соседей в очередь на проверку 
        for (int i = 0; i < n; i++) {
            if (graph[pos][i] != 0 && graph[pos][i] + len[pos] < len[i]) {
                if (prev[i] != -1) {
                    ans[prev[i]][i] = 0;
                    //ans[i][prev[i]] = 0;
                }
                ans[pos][i] = graph[pos][i];
                //ans[i][pos] = graph[pos][i];
                prev[i] = pos;
                len[i] = len[pos] + graph[pos][i];
                node.push(i);
            }
        }
    }
    output(ans, n);
}

int main() {
    setlocale(LC_ALL, "ru");

    int n = 5;
    vector<vector<int>> graph(n, vector<int>(n, 0));

    // ориентированный 
    //           0  1  2  3  4  5  6  7
    graph[0] = { 0, 6, 3, 0, 0 };
    graph[1] = { 0, 0, 0, 1, 0 };
    graph[2] = { 0, 2, 0, 0, 4 };
    graph[3] = { 0, 0, 0, 0, 1 };
    graph[4] = { 0, 0, 0, 0, 0 };
    
    vector<vector<int>> ans = graph;
    bfs(ans);


    return 0;
}

