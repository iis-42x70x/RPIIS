#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

struct Edge {
    int to;    
    int weight; 
};

int max_matrix(vector<vector<int>> matrix, int vertexes){
    int max = matrix[0][0];
    for (int i = 0; i < vertexes; i++) {
        for (int j = 0; j < vertexes; j++) {
            if (matrix[i][j] > max)
                max = matrix[i][j];
        }
    }
    return max;
}

int find_diametr(vector<vector<Edge>> adjList, int vertexes){
    int diametr;
    const int INF = 1e9;

    vector<vector<int>> dist(vertexes, vector<int>(vertexes, INF));
    for (int i = 0; i < vertexes; i++) {
        dist[i][i] = 0;
    }

    for (int i = 0; i < vertexes; i++) {
        for (int j = 0; j < adjList[i + 1].size(); j++) {
            dist[i][adjList[i + 1][j].to - 1] = adjList[i + 1][j].weight;
        }
    }

    for (int p = 0; p < vertexes; p++){
        for (int i = 0; i < vertexes; i++){
            if (dist[i][p] != INF){
                for (int j = 0; j < vertexes; j++){
                    if (dist[p][j] != INF && dist[i][j] > dist[i][p] + dist[p][j] && i != j){
                        dist[i][j] = dist[i][p] + dist[p][j];
                    }
                }
            }
        }
    }
   
    diametr = max_matrix(dist, vertexes);
    return diametr;
}

int main() {

    const int INF = 1e9;

    setlocale(LC_ALL, "RU");

    ifstream file("test.txt");
    if (!file.is_open()) {
        cout << "Ошибка при чтении файла" << endl;
        return 1; 
    }

    for (int i = 1; i <= 5; i++){
        cout << "Тест номер " << i << " :" << endl;

        int vertexes, edges;
        file >> vertexes >> edges;

        vector<vector<Edge>> adjList(vertexes + 1); //+1 для 1-индексации

        file.ignore(); //игнорируем символ новой строки после считывания чисел

        for (int j = 1; j <= vertexes; j++){
            string line;
            getline(file, line); // vertex j
            istringstream iss(line);

            int vertex;
            iss >> vertex; 

            int neighbor, weight;
            while (iss >> neighbor >> weight){ 
                adjList[vertex].push_back({ neighbor, weight });
            }
        }

        int diametr = find_diametr(adjList, vertexes);
        if (diametr == INF)
            cout << endl << "Диаметр графа равен бесконечности" << endl;
        else
            cout << endl << "Диаметр графа: " << diametr << endl;
        cout << endl; 
    }

    file.close(); 
    return 0;
}