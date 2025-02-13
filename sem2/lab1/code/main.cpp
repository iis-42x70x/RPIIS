

#include <iostream>
#include <vector>
#include <fstream>
#include "header.h"
using namespace std;

int main() {
    int vertex=0, edges=0;
    vector<vector<pair<int, int>>> graph(vertex);
    cout << "Введите 1, если хотите заполнить граф  вручную"<<endl;
    cout <<"Введите 2, если хотите чтоб нраф был заполнен данными из файла"<<endl;
    int check_vvod;
    cin >> check_vvod;
    switch(check_vvod){
        case 1:{
            ruchnoi_vvod(graph,vertex,edges);
        }break;
        case 2:{
            reading_file(graph,vertex,edges);
        }break;
        default:{
            reading_file(graph,vertex,edges);
        }break;
    }

    vivod_graphs(graph ,vertex);

    cout << endl;
    int number=0;
    cout << "Ввелите 1, если хотите удалить вершину в графе"<<endl;
    cout << "Введите 2, если хотите добавить вершину в граф"<<endl;
    cout << "Введите 3, если хотите удалить дугу в графе"<<endl;
    cout << "Введите 4, если хотите добавить дуг в граф"<<endl;
    cout << "Введите 5, если хотите сделать обход в ширину"<<endl;
    cout << "Введите 6, если хотите выйти из программы"<<endl;

    while(number != 6) {
        cin >> number;
        switch (number) {
            case 1: {
                delete_vertex(graph, vertex, edges);
                vivod_graphs(graph, vertex);
                cout << endl;
            }
                break;
            case 2: {
                insert_data(graph, vertex);
                vivod_graphs(graph, vertex);
                cout << endl;
            }
                break;
            case 3: {
                delete_edge(graph, vertex, edges);
                vivod_graphs(graph, vertex);
                cout << endl;

            }
                break;
            case 4: {
                insert_new_edge(graph, vertex, edges);
                vivod_graphs(graph, vertex);
                cout << endl;
            }
                break;
            case 5: {
                BFS(graph);
            }break;
            case 6:{
                cout<<"Вы вышли из программы";
                return 0;
            } break;
            default: {
                cout << "Введите корректно число!!!"<<endl;
            }
                break;
        }
    }

    return 0;
}
