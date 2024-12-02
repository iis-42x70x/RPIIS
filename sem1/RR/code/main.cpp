#include <iostream>
#include <vector>
#include <queue>
#include <fstream>

using namespace std;

const int INF = 1e9;

void ruchnoi(int &vertex, int &edge, vector<vector<pair<int, int>>> &graph, int &start) {
    cout << "Введите количество вершин: ";
    cin >> vertex;
    cout << "Введите количество ребер: ";
    cin >> edge;
    graph.resize(vertex);

    cout << "Введите ребра в формате: вершина1 вершина2 вес" << endl;
    for (int i = 0; i < edge; i++) {
        int a, b, weight;
        cin >> a >> b >> weight;
        graph[a].push_back({b, weight});
        graph[b].push_back({a, weight});
    }

    cout << "Введите вершину, для которой вы хотите найти дерево кратчайших путей: ";
    cin >> start;
}
void osnov_alg(int vertex, int edge, vector<vector<pair<int, int>>> &graph, int start) {
    vector<int> dist(vertex, INF);
    vector<int> pr(vertex, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;

    dist[start] = 0;
    q.push({0, start});

    while (!q.empty()) {
        pair<int, int> g = q.top();
        q.pop();

        int d = g.first;
        int v = g.second;

        if (d > dist[v]) continue;

        for (auto edg : graph[v]) {
            int to = edg.first;
            int weight = edg.second;
            if (dist[to] > dist[v] + weight) {
                dist[to] = dist[v] + weight;
                pr[to] = v;
                q.push({dist[to], to});
            }
        }
    }

    // Вывод кратчайших путей и расстояний
    for (int finish = 0; finish < vertex; finish++) {
        vector<int> path;
        int cur = finish;

        if (dist[finish] == INF) {
            cout << "Вершина " << finish << " не достижима" << endl;
            continue;
        }

        while (cur != -1) {
            path.push_back(cur);
            cur = pr[cur];
        }

        cout << "Кратчайший путь до вершины " << finish << ": ";
        for (int i = path.size() - 1; i >= 0; i--) {
            cout << path[i] << (i > 0 ? " -> " : "");
        }
        cout << " расстояние: " << dist[finish] <<  endl;
    }
    cout << endl;

    cout << "Расстояния до вершин: ";
    for (auto di: dist){//вывод  самих расстояний до вершин
        if (di==INF){
            cout << "X"<<" ";
        }
        else{
            cout << di << " ";
        }
    }
    cout << endl;
}


void read_file(int &vertex, int &edge, vector<vector<pair<int, int>>> &graph, int &start) {
    ifstream file("input.txt");
    if (!file.is_open()) {
        cout << "Ошибка открытия файла" << endl;
        return;
    }

    for (int i= 0;i < 5; i++) {
        if (i> 0) { // пропускаем пустую строку между тестами
            string emptyLine;
            getline(file, emptyLine);
        }

        file >> vertex >> edge;
        graph.clear();
        graph.resize(vertex);

        for (int j = 0; j < edge; j++) {
            int a, b, weight;
            file >> a >> b >> weight;
            graph[a].push_back({b, weight});
            graph[b].push_back({a, weight});
        }
        file >> start;
        file.ignore(); // игнорируем символ новой строки после стартовой вершины
        osnov_alg(vertex, edge, graph, start);
    }

    file.close();
}


int main() {
    int cass, vertex = 0, edge = 0, start = 0;
    vector<vector<pair<int, int>>> graph;

    cout << "Введите 1, если хотите считать тестовые значения из файла" << endl;
    cout << "Введите 2, если хотите вручную заполнять граф" << endl;
    cin >> cass;

    switch (cass) {
        case 1: {
            read_file(vertex, edge, graph, start);
        }
            break;
        case 2: {
            ruchnoi(vertex, edge, graph, start);
            osnov_alg(vertex, edge, graph, start);
        }
            break;
        default: {
            ruchnoi(vertex, edge, graph, start);
            osnov_alg(vertex, edge, graph, start);
        }
            break;
    }

    return 0;
}


/*
#include <iostream>
#include <vector>

using namespace std;

const int  INF = 1e9;
int main(){
    int vertex, edge;
    cout << "Введите количество вершин: ";
    cin >> vertex;
    cout << "Введите количество ребер: ";
    cin>> edge;
    // создание графа
    vector <vector<pair<int , int>>> graph(vertex);
    cout << "Введите вершины графа и длину ребер между ними";
    for (int i = 0; i < edge; i++){
        int a, b, weight;
        cin>> a >> b >> weight;
        graph[a].push_back({b, weight});
        graph[b].push_back({a, weight});
    }
    cout << endl;
    cout <<"Получившийся граф: ";
    cout << endl;
    for (int i = 0; i <graph.size(); i++){
        for (auto a: graph[i]){
            cout << " вершина" << " " << i << " " << "соединена";
            cout <<" "<<"с вершиной "<< a.first <<" "<< "ребром,длина которого равна "<<" "<<a.second<<endl;
        }
    }

    int start;
    cout << "Введите стартовую вершину: ";
    cin >> start;

    vector <int> dist(graph.size(), INF);
    vector <bool> visited(graph.size());
    dist[start] = 0;
    vector <int> from(graph.size(), -1);
    for (int i = 0; i < vertex; i++){
        int nearest = -1;
        for (int j = 0; j < vertex; j++){
            if (visited[j]==0 && (nearest == -1  dist[j]< dist[nearest])){
                nearest = j;
            }
        }
        visited[nearest] = 1;
        for (auto &[k, weight] : graph[nearest]){
            if (dist[k]> dist[nearest]+ weight){
                dist[k] = dist[nearest] + weight;
                from[k] = nearest;
            }
        }

    }
    int finish;
    cout << "введите номер вершины до которой хотите посмотреть путь:";
    cin >> finish;
    vector<int> path;

    int cur = finish;         //текущая вершина пути
    path.push_back(cur);

    while (from[cur] != -1) {   //пока существует предыдущая вершина
        cur = from[cur];        //переходим в неё
        path.push_back(cur);    //и дописываем к пути
    }

    for (auto d: dist){
        if (d == INF){
            cout << "X"<<" ";
        }
        else{
            cout << d<<" ";
        }
    }
    cout << endl;
    for (auto p: path){
        cout << p<< " ";
    }
    cout << endl;
    for (auto l: from){
        cout << l<< " ";
    }


    return 0;
}*/

/*#include <iostream>
#include <vector>

using namespace std;

const int  INF = 1e9;
int main(){
    int vertex, edge;
    cout << "Введите количество вершин: ";
    cin >> vertex;
    cout << "Введите количество ребер: ";
    cin>> edge;
    // создание графа
    vector <vector<pair<int , int>>> graph(vertex);
    cout << "Введите вершины графа и длину ребер между ними";
    for (int i = 0; i < edge; i++){
        int a, b, weight;
        cin>> a >> b >> weight;
        graph[a].push_back({b, weight});
        graph[b].push_back({a, weight});
    }
    cout << endl;
    cout <<"Получившийся граф: ";
    cout << endl;
    for (int i = 0; i <graph.size(); i++){
        for (auto a: graph[i]){
            cout << " вершина" << " " << i << " " << "соединена";
            cout <<" "<<"с вершиной "<< a.first <<" "<< "ребром,длина которого равна "<<" "<<a.second<<endl;
        }
    }

    int start;
    cout << "Введите стартовую вершину: ";
    cin >> start;

    vector <int> dist(graph.size(), INF);
    vector <bool> visited(graph.size());
    dist[start] = 0;
    vector <int> from(graph.size(), -1);
    for (int i = 0; i < vertex; i++){
        int nearest = -1;
        for (int j = 0; j < vertex; j++){
            if (visited[j]==0 && (nearest == -1  dist[j]< dist[nearest])){
                nearest = j;
            }
        }
        visited[nearest] = 1;
        for (auto k : graph[nearest]){
            if (dist[k.first]> dist[nearest]+ k.second){
                dist[k.first] = dist[nearest] + k.second;
                from[k.first] = nearest;
            }
        }

    }
    vector <int> path;
    int finish;
    cin >> finish;
    int cur  = finish;
    path.push_back(cur);


while(from[cur] != -1) {
        cur = from[cur];
        path.push_back(cur);

    }

    for (auto d: dist){
        if (d == INF){
            cout << "X"<<" ";
        }
        else{
            cout << d<<" ";
        }
    }
    cout << endl;
    for (auto p:path){
        cout << p << " ";
    }


    return 0;
}*/