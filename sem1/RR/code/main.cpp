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

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1e9;

int main(){
            int vertex, edge;
            cout << "Введите количество вершин: ";
            cin >> vertex;
            cout << "Введите количество ребер: ";
            cin >> edge;
            vector <vector<pair<int, int>>> graph(vertex);
            for (int i = 0; i < edge; i++){
                int a,b, weight;
                cin >> a >> b>>weight;
                graph[a].push_back({b, weight});
                graph[b].push_back({a,weight});
            }
            vector <int> dist(graph.size(), INF);//создание массива,
            // в котором будут хранится расстояния до вершин(изначально расстояния до всех вершин равно бесконечности)

            priority_queue <pair<int, int>, vector <pair<int, int>>, greater<pair<int, int>> > q;//создание очереди с приоритетом

            vector <int> pr(graph.size(), -1);//создание массива для восстановления кратчайших путей

            int start;//инициализация вершины, для которой хотим найти расстояния до других вершин
            cout <<"Введите вершину, для которой вы хотите найте дерево кратчайших путей: ";
            cin>> start;
            dist[start] = 0;//расстояние до стартовой вершины равно 0
            q.push({0,start});//ставим в очередь нашу стартовую вершину

            while(!q.empty()){//выполняем действия в цикле,  до тех пор пока очередь не пуста.
                pair <int, int> g = q.top();// извлекаем информацию о вершине
                q.pop();//удаляем вершину из очереди

                int d = g.first; //расстояние до вершины
                int v = g.second;//номер вершины

                if (d> dist[v]) continue;//мы уже обработали эту вершину, используя другой путь
                //перейти к следующей вершине

                for (auto edg : graph[v]){//проход по всем соседним вершинам
                    int to = edg.first;
                    int weight = edg.second;
                    if (dist[to]> dist[v] + weight){//проверяем: можно ли улучшить наше расстояние до соседа
                        dist[to] = dist[v] + weight;
                        pr[to]= v;// записываем вершину,из которой пришли
                        q.push({dist[to], to});//помещаем новую вершину в очередь
                    }
                }

            }




            vector <int> path;//создание массива, в котором и будут храниться наши вершины, которые
            //нужны для восстановления путей
            for (int finish = 0; finish < vertex; finish++) {// для всех вершин
                path.clear();//очистка массива path, для нахождения дерева кратчайших путей до следующей вершины
                int cur = finish;
                if (pr[finish] != -1 || finish==start){//проверка на не досягаемые вершины
                    path.push_back(cur);
                }
                else{
                    cout<<"Не досягаема";
                }
                //добавляем вершины до тез пор пока не встретим -1 в массиве pr(то есть пока не дойдем до конечной вершины)
                while (pr[cur] != -1) {
                    cur = pr[cur];
                    path.push_back(cur);
                }
                vector <int> new_path;// создание нового массива, в котором будут храниться элементы массива
                // path записанные в обратном порядке
                for (int i= path.size()-1; i >=0; i--){
                    new_path.push_back((path[i]));
                }
                for (auto f: new_path) {//вывод кратчайших путей(вершин, по которым проходят пути)
                    cout << f << " ";
                }
                cout << endl;
            }
            cout << endl;
            for (auto di: dist){//вывод  самих расстояний до вершин
                if (di==INF){
                    cout << "X"<<" ";
                }
                else{
                    cout << di << " ";
                }
            }
     return 0;
}
