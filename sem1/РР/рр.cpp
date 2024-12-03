#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

// Функции для алгоритма Косарайю

//Первый проход DFS для заполнения порядка вершин
void Order(int v, vector<vector<int>>& list, vector<bool>& used, vector<int>& order)
{
    used[v] = true;

    for (int i : list[v])
        if (!used[i])
            Order(i, list, used, order);
    
    order.push_back(v);
}

// Второй проход DFS для нахождения сильных компонент связности
void DFS(int v, vector<vector<int>>& list, vector<bool>& used, vector<int>& component)
{
    used[v] = true;
    component.push_back(v);

    for (int i : list[v])
        if (!used[i])
            DFS(i, list, used, component);
}

//Инверсируем наш граф (меянем направление рёбер на противоположное)
vector<vector<int>> Inversion(int V, vector<vector<int>>& list)
{
    vector<vector<int>> g(V);

    for (int v = 0; v < V; v++)
        for (int i : list[v])
            g[i].push_back(v);
    return g;
}

//Алгоритм Косарайю
void Output(int V, vector<vector<int>>& list)
{
    vector<int> order;
    vector<bool> used(V, false);

    for (int i = 0; i < V; i++)
        if (!used[i])
            Order(i, list, used, order);

    vector<vector<int>> g = Inversion(V, list);

    for (int i = 0; i < V; i++) {
        used[i] = false; 
    } 

    for (auto it = order.rbegin(); it != order.rend(); ++it) {
        int v = *it;
        if (!used[v]) {
            vector<int> component; 
            DFS(v, g, used, component); 
            for (int vertex : component)
                cout << vertex << " ";
            cout << endl;
        }
    }
}

int main() {
    setlocale(LC_ALL, "RU");

    int V, E;
    string filename;

    cout << "Введите имя файла с данными: ";
    cin >> filename;

    ifstream infile(filename);

    if (!infile) {
        cout << "Ошибка открытия файла!" << endl;
        return 1;
    }

    infile >> V;
    vector<vector<int>> list(V);

    infile >> E;

    for (int i = 0; i < E; i++) {
        int u, v;
        infile >> u >> v;
        list[u].push_back(v);
    }

    infile.close();

    cout << "Сильные компоненты связности в графе: \n";
    Output(V, list);

    return 0;
}
