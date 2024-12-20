#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;
const int INFINITY_ = numeric_limits<int>::max();

vector<vector<int>> MatrixIncedent(int numVertices, int numEdges) {
    vector<vector<int>> MIncendent(numVertices, vector<int>(numEdges, 0));
    vector<int> weights(numEdges);
    cout << "вводи ребра вот так: от какой вершины, к какой вершине, вес ребра (+/- направленность)" << endl;

    for (int j = 0; j < numEdges; ++j) {
        int src, dest, weight;
        cin >> src >> dest >> weight;
        MIncendent[src][j] = -weight; 
        MIncendent[dest][j] = weight; 
        weights[j] = weight;
    }

    return MIncendent;
}

vector<vector<int>> SmejnayaMatrixFromIncedent(const vector<vector<int>>& incidenceMatrix, int numVertices, int numEdges) {
    vector<vector<int>> Msmejnosti(numVertices, vector<int>(numVertices, INFINITY_));

    for (int j = 0; j < numEdges; ++j) {
        int u = -1, v = -1;
        for (int i = 0; i < numVertices; ++i) {
            if (incidenceMatrix[i][j] < 0) u = i; // конечная вершина
            if (incidenceMatrix[i][j] > 0) v = i; // начальная вершина
        }
        if (u != -1 && v != -1) {
            Msmejnosti[u][v] = incidenceMatrix[v][j]; // для веса
        }
    }

    for (int i = 0; i < numVertices; i++) {
        Msmejnosti[i][i] = 0;
    }

    return Msmejnosti;
}

void floydWarshall(vector<vector<int>>& dist) {
    int numVertices = dist.size();
    for (int k = 0; k < numVertices; k++) {
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                if (dist[i][k] != INFINITY_ && dist[k][j] != INFINITY_ && dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }
}

int findDiameter(const vector<vector<int>>& dist) {
    int maxDist = 0;
    for (const auto& row : dist) {
        for (int d : row) {
            if (d != INFINITY_) {
                maxDist = max(maxDist, d);
            }
        }
    }
    return maxDist;
}

void printMatrix(const vector<vector<int>>& matrix, string title) {
    cout << title << ":" << endl;
    for (const auto& row : matrix) {
        for (int val : row) {
            if (val == INFINITY_)
                cout << setw(5) << "INF"; //будет бахать когда бесконечность
            else
                cout << setw(5) << val; //будет бахать когда не бесконечность
        }
        cout << endl;
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    int numVertices, numEdges;

    cout << "число вертикалей введи: ";
    cin >> numVertices;
    cout << "а терь ребер: ";
    cin >> numEdges;

    auto incidenceMatrix = MatrixIncedent(numVertices, numEdges);
    auto adjacencyMatrix = SmejnayaMatrixFromIncedent(incidenceMatrix, numVertices, numEdges);

    printMatrix(incidenceMatrix, "инцидентная матрица");
    printMatrix(adjacencyMatrix, "смежная матрица");

    vector<vector<int>> dist = adjacencyMatrix;
    floydWarshall(dist);

    int diameter = findDiameter(dist);
    cout << "диаметр графа: " << diameter << endl;

}
