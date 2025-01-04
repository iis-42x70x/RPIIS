// пользователю предлагается ввести граф 
// программа выводит граф кротчайших путей в виде матрицы смежности
// программа работает для внг и вог

#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#define INT_MAX 2147483647

using namespace std;

void input(int& n, vector<vector<int>>& vec)
{

}

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
    queue<int> node;       // очередь вершин, которым предстоит 

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
}

int main() {
    setlocale(LC_ALL, "ru");

    int n = 7;
    vector<vector<int>> graph(n, vector<int>(n, 0));


    
    // неориентриванный
    //           0  1  2  3  4  5  6 
    /*graph[0] = { 0, 5, 3, 0, 0, 0, 0 };
    graph[1] = { 5, 0, 2, 6, 0, 0, 0 };
    graph[2] = { 3, 2, 0, 0, 4, 0, 0 };
    graph[3] = { 0, 6, 0, 0, 1, 2, 0 };
    graph[4] = { 0, 0, 4, 1, 0, 1, 7 };
    graph[5] = { 0, 0, 0, 2, 1, 0, 3 };
    graph[6] = { 0, 0, 0, 0, 7, 3, 0 };*/

    /*  ans      0  1  2  3  4  5  6
    graph[0] = { 0, 5, 3, 0, 0, 0, 0 };
    graph[1] = { 5, 0, 0, 0, 0, 0, 0 };
    graph[2] = { 3, 0, 0, 0, 4, 0, 0 };
    graph[3] = { 0, 0, 0, 0, 1, 0, 0 };
    graph[4] = { 0, 0, 4, 1, 0, 1, 0 };
    graph[5] = { 0, 0, 0, 0, 1, 0, 3 };
    graph[6] = { 0, 0, 0, 0, 0, 3, 0 };
    */

    // ориентированный 
    //           0  1  2  3  4  5  6 
    graph[0] = { 0, 5, 3, 0, 0, 0, 0 };
    graph[1] = { 0, 0, 0, 6, 0, 0, 0 };
    graph[2] = { 0, 2, 0, 0, 4, 0, 0 };
    graph[3] = { 0, 0, 0, 0, 1, 2, 0 };
    graph[4] = { 0, 0, 0, 1, 0, 1, 7 };
    graph[5] = { 0, 0, 0, 0, 0, 0, 3 };
    graph[6] = { 0, 0, 0, 0, 0, 0, 0 };
    
    vector<vector<int>> ans = graph;
    bfs(ans);
    output(ans, n);


    return 0;
}

