#include <iostream>
using namespace std;

// Функция для нахождения максимальной степени вершины
int maxStepen(int** incidenceMatrix, int vertices, int edges) {
    int maxDegree = 0;

    for (int i = 0; i < vertices; ++i) {
        int degree = 0;

        // Считаем количество единиц в строке (степень вершины)
        for (int j = 0; j < edges; ++j) {
            if (incidenceMatrix[i][j] == 1) {
                degree++;
            }
        }

        // Обновляем максимальную степень
        if (degree > maxDegree) {
            maxDegree = degree;
        }
    }

    return maxDegree;
}

int main() {
    setlocale(LC_ALL, "Ru");

    int vershinu, rebra;

    // Ввод количества вершин и рёбер
    cout << "Введите количество вершин: ";
    cin >> vershinu;
    cout << "Введите количество рёбер: ";
    cin >> rebra;

    // Динамическое выделение памяти для матрицы инцидентности
    int** incidenceMatrix = new int* [vershinu];
    for (int i = 0; i < vershinu; ++i) {
        incidenceMatrix[i] = new int[rebra];
    }

    cout << "Введите матрицу инцидентности (строка за строкой):" << endl;

    // Ввод матрицы инцидентности
    for (int i = 0; i < vershinu; ++i) {
        for (int j = 0; j < rebra; ++j) {
            cin >> incidenceMatrix[i][j];
        }
    }

    // Вычисляем максимальную степень вершины
    int maxDegree = maxStepen(incidenceMatrix, vershinu, rebra);

    cout << "Максимальная степень вершины: " << maxDegree << endl;

    // Освобождение выделенной памяти
    for (int i = 0; i < vershinu; ++i) {
        delete[] incidenceMatrix[i];
    }
    delete[] incidenceMatrix;

    return 0;
}
