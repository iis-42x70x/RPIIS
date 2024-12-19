#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

void calculateVertexDegrees(const vector<vector<int>>& graph, vector<int>& degrees) {
    int n = graph.size();
    for (int i = 0; i < n; i++) {
        int degree = 0;
        for (int j = 0; j < n; j++) {
            if (graph[i][j] == 1) {
                degree++;
            }
        }
        degrees[i] = degree;
    }
}

int findMinEdgeDegree(const vector<vector<int>>& graph, const vector<int>& degrees) {
    int n = graph.size();
    int minEdgeDegree;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i][j] == 1) {  // edge is True
                int edgeDegree = degrees[i] + degrees[j];
                if (edgeDegree < minEdgeDegree) {
                    minEdgeDegree = edgeDegree;
                }
            }
        }
    }
    return minEdgeDegree;
}

int main() {
    ifstream inputFile("graph.txt");
    if (!inputFile) {
        cerr << "Ошибка: не удалось открыть файл!" << endl;
        return 1;
    }
    int n;
    inputFile >> n;  // кол-во вершин
    vector<vector<int>> graph(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inputFile >> graph[i][j]; // знак ">>" означает игнорирование \n, tab и пробелы
        }
    }
    inputFile.close();
    vector<int> vertexDegrees(n);
    calculateVertexDegrees(graph, vertexDegrees);
    int minEdgeDegree = findMinEdgeDegree(graph, vertexDegrees);
    if (minEdgeDegree == -1) {
        cout << "Рёбра отсутствуют" << endl;
    } else {
        cout << "Минимальная степень рёбра: " << minEdgeDegree << endl;
    }
    return 0;
}