
#include "header.h"
bool checking_vvod(int data, int size) {
    if (data >0 && data <= size) return true;
    return false;
}
// Удаление вершины
void delete_element_from_vector(vector<pair<int, int>>& mas_pair, int& siz, int number) {
    if (number >= 0 && number < siz) {  // Изменено с number > 0 на number >= 0
        for (int i = number; i < siz - 1; i++) {
            mas_pair[i] = mas_pair[i + 1];
        }
        mas_pair.pop_back();
        siz--;
    }
}

void delete_vertex(vector<vector<pair<int, int>>>& graph, int& vertex, int& edges) {
    if (vertex <= 0) {  // Добавлена проверка на пустой граф
        cout << "Граф пуст!\n";
        return ;
    }

    int del_ver;
    cout << "Введите номер вершины, которую хотите удалить\n";
    cin >> del_ver;
    if (del_ver <= 0 && del_ver > vertex) {  // Добавлена проверка корректности ввода
        cout << "Некорректный номер вершины!\n";
        return ;
    }
    del_ver--;

    for (int i = 0; i < vertex; i++) {
        int size_of_reber = graph[i].size();
        for (int j = 0; j < size_of_reber; j++) {
            if (graph[i][j].first == del_ver) {
                delete_element_from_vector(graph[i], size_of_reber, j);
                edges--;
                j--;
            }
            else if (graph[i][j].first > del_ver) {
                graph[i][j].first--;
            }
        }
    }

    for (int i = del_ver; i < vertex - 1; i++) {
        graph[i] = graph[i + 1];
    }
    graph.pop_back();
    vertex--;
}
//Добавленеи вершины
void insert_data(vector<vector<pair<int, int>>>& graph, int& vertex) {
    graph.push_back(vector<pair<int,int>>());
    vertex++;
    cout << "Вершина"<<" "<<vertex<<" "<<"успешно добавлена";

}

//Добавление новых дуг в граф
void insert_new_edge(vector<vector<pair<int, int>>>& graph, int vertex, int& edges) {
    int number_first_vertex;
    cout << "Введите номер вершины от которой пойдет новая дуга: ";
    cin >> number_first_vertex;
    while (!checking_vvod(number_first_vertex, vertex)) {
        cout << "Неправильный ввод первой вершины!!!!";
        cin >> number_first_vertex;

    }
    number_first_vertex--;

    cout << "Введите номер вершины, в которую будет вести дуга: ";
    int number_second_vertex;
    cin >> number_second_vertex;
    while (!checking_vvod(number_second_vertex, vertex)) {
        cout << "Неправильный ввод второй вершины!!!!";
        cin >> number_second_vertex;

    }
    number_second_vertex--;


    graph[number_first_vertex].push_back({ number_second_vertex, 1 });
    edges++;
}

//Удаление дуги
void delete_edge(vector<vector<pair<int, int>>>& graph, int vertex, int& edges) {
    int first, second;
    cout << "Введите номер вершины из которой выходит ребро:\n";
    cin >> first;
    while (!checking_vvod(first, vertex)) {
        cout << "Неправильный ввод первой вершины!!!!";
        cin >> first;

    }
    first--;
    cout << "Введите вершину в которую ведет ребро:\n";
    cin >> second;
    while (!checking_vvod(second, vertex)) {
        cout << "Неправильный ввод второй вершины!!!!";
        cin >> second;

    }
    second--;

    int size_of_reber = graph[first].size();
    bool flag = false;
    if (!graph[first].empty()) {
        for (int i = 0; i < size_of_reber; i++) {
            if (graph[first][i].first == second) {
                flag = true;
                delete_element_from_vector(graph[first], size_of_reber, i);
                edges--;
                i--;
            }
        }
    }
    else {
        cout << "у графа нет ребер";
    }
    if (!flag) {
        cout << "такого ребра не сущестувет";
    }

}

void vivod_graphs(vector<vector<pair<int, int>>> graph, int vertex){
    cout << "\nСвязи между вершинами:\n";
    for (int i = 0; i < vertex; i++) {
        if (!graph[i].empty()) {
            cout << "Вершина " << i + 1 << " соединена с вершинами: ";
            for (const auto& edge : graph[i]) {
                cout << edge.first + 1 << " ";
            }
            cout << endl;
        }
        else {
            cout << "Вершина " << i + 1 << " не соединена не из одной вершин"<<endl;
        }
    }
}
void BFS(vector<vector<pair<int, int>>> graph) {
    vector<bool> used(graph.size(), false);
    queue<int> q;
    q.push(0);
    used[0] = true;

    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        cout << "BFS находится в вершине " << cur + 1 << endl;

        for (auto neighbor : graph[cur]) {
            if (!used[neighbor.first]) {
                q.push(neighbor.first);
                used[neighbor.first] = true;
            }
        }
    }
}
void reading_file(vector<vector<pair<int, int>>> &graph, int &vertex, int &edges){
    ifstream file ("input.txt");
    if (file.is_open()){
        string s;
        getline(file,s);
        file >> vertex;
        file>> edges;
        graph.clear();
        graph.resize(vertex);

        for (int j = 0; j < edges; j++) {
            int first, second;
            file >> first >>second;
            first--; second--;
            graph[first].push_back({second, 1});

        }
        file.close();

    }
    else{
        cout << "Проблемы с  открытием!!!";
    }

}
void ruchnoi_vvod(vector<vector<pair<int, int>>> &graph, int &vertex, int &edges){
    cout << "Введите количество вершин в графе: ";
    cin >> vertex;
    cout << "Введите количество ребер в графе: ";
    cin >> edges;
    graph.clear();
    graph.resize(vertex);
    if (vertex <= 0 && edges < 0) {  // Добавлена проверка корректности ввода
        cout << "Некорректные данные!\n";
        return ;
    }

    cout << "Заполните граф (укажите какая вершина связана с какой): ";
    for (int i = 0; i < edges; i++) {
        int first_vertex, second_vertex;
        cin >> first_vertex >> second_vertex;
        if (first_vertex <= 0 || first_vertex > vertex || second_vertex <= 0 || second_vertex > vertex) {  // Добавлена проверка
            cout << "Некорректные номера вершин!\n";
            i--;
            continue;
        }
        first_vertex--; second_vertex--;
        graph[first_vertex].push_back({ second_vertex, 1 });
    }

}
