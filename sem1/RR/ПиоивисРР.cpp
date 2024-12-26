#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// Поиск в глубину
void DFS(int vertice, const vector<vector<int>>& incidenceMatrix, vector<bool>& viewed) {
    stack<int> s;
    s.push(vertice);
    viewed[vertice] = true;

    while (!s.empty()) {
        int v = s.top();
        s.pop();

        for (int i = 0; i < incidenceMatrix[v].size(); i++) {
            if (incidenceMatrix[v][i] == 1) { // Просматриваемая вершина инцидентна с ребром
                for (int j = 0; j < incidenceMatrix.size(); j++) {
                    if (incidenceMatrix[j][i] == 1 && !viewed[j]) { // Смежная вершина
                        viewed[j] = true;
                        s.push(j);
                    }
                }
            }
        }
    }
}

// Счет компонентов связности
int countConnectedComponents(const vector<vector<int>>& incidenceMatrix) {
    int numVertices = incidenceMatrix.size();
    vector<bool> viewed(numVertices, false);
    int connectedComponents = 0;

    for (int i = 0; i < numVertices; i++) {
        if (!viewed[i]) {
            DFS(i, incidenceMatrix, viewed);
            connectedComponents++;
        }
    }

    return connectedComponents;
}

int main() {
    setlocale(LC_ALL, "Russian");
    // Матрица инцидентности 1
    vector<vector<int>> incidenceMatrix1 = {
        {1, 0, 0},
        {1, 1, 0}, 
        {0, 1, 1}, 
        {0, 0, 1}  
    };

    int connectedComponents1 = countConnectedComponents(incidenceMatrix1);
    cout << "Количество компонентов связности матрицы 1: " << connectedComponents1 << endl;

    // Матрица инцидентности 2
    vector<vector<int>> incidenceMatrix2 = {
        {0, 0, 0}, 
        {1, 0, 0}, 
        {0, 1, 1},  
        {0, 1, 0}, 
        {0, 0, 1} 
    };

    int connectedComponents2 = countConnectedComponents(incidenceMatrix2);
    cout << "Количество компонентов связности матрицы 2: " << connectedComponents2 << endl;

    return 0;
}