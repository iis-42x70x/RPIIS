#include <iostream>
#include <vector>
#include <climits> // для INT_MAX

using namespace std;

// Функция для нахождения минимальной степени ребра
int findMinEdgeDegree(const vector<vector<int>>& incidenceMatrix) {
    
    int numVertices = incidenceMatrix.size();
    if (numVertices == 0) return -1; //Если нет вершин (пустая матрица)
    
    int numEdges = incidenceMatrix[0].size();
    if (numEdges == 0) return -1; // Если нет рёбер (0 столбцов в матрице)

    // 1. найдём степени всех вершин
    vector<int> vertexDegrees(numVertices, 0); //вектор для хранения степеней вершин
    for (int i = 0; i < numVertices; ++i) { //Проходим по всем элементам матрицы
        for (int j = 0; j < numEdges; ++j) { //Для каждой вершины (строки) подсчитываем количество рёбер (столбцов со значением 1)
            if (incidenceMatrix[i][j] == 1) {
                vertexDegrees[i]++;
            }
        }
    }

    // 2. для каждого ребра найдём его степень
    int minEdgeDegree = INT_MAX;
    for (int j = 0; j < numEdges; ++j) {
        // Находим две вершины, соединённые ребром j
        int u = -1, v = -1;
        for (int i = 0; i < numVertices; ++i) {
            if (incidenceMatrix[i][j] == 1) {
                if (u == -1) {
                    u = i;
                } else {
                    v = i;
                    break; // в неориентированном графе ребро соединяет ровно 2 вершины
                }
            }
        }

        if (u == -1 || v == -1) {
            continue; // петля или некорректное ребро (пропускаем)
        }

        // Степень ребра = deg(u) + deg(v) - 2
        int edgeDegree = vertexDegrees[u] + vertexDegrees[v] - 2;
        if (edgeDegree < minEdgeDegree) {
            minEdgeDegree = edgeDegree;
        }
    }

    /*Если граф не содержал рёбер (все проверки не сработали), возвращаем -1. 
    Иначе - найденную минимальную степень.*/
    return (minEdgeDegree == INT_MAX) ? -1 : minEdgeDegree;
}

int main() {
    // Пример матрицы инцидентности (4 вершины, 5 рёбер)
    vector<vector<int>> incidenceMatrix = {
        {1, 1, 0, 0, 0}, // Вершина 0 инцидентна рёбрам 0 и 1
        {1, 0, 1, 1, 0}, // Вершина 1 инцидентна рёбрам 0, 2 и 3
        {0, 1, 1, 0, 1}, // Вершина 2 инцидентна рёбрам 1, 2 и 4
        {0, 0, 0, 1, 1}  // Вершина 3 инцидентна рёбрам 3 и 4
    };

    int minEdgeDegree = findMinEdgeDegree(incidenceMatrix);
    cout << "Минимальная степень ребра: " << minEdgeDegree << endl;

    return 0;
}