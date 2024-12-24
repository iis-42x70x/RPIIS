#include <iostream>

using namespace std;

const int MAX_VERTICES = 100; // Максимальное количество вершин в графе

// Функция для нахождения хорд в неориентированном графе
int countChords(int incidenceMatrix[MAX_VERTICES][MAX_VERTICES], int numVertices, int numEdges) {
    int chordCount = 0;

    // Перебираем все пары вершин
    for (int i = 0; i < numVertices; ++i) {
        for (int j = i + 1; j < numVertices; ++j) {
            // Проверяем, являются ли i и j соседями (инцидентными)
            bool areNeighbors = false;
            for (int k = 0; k < numEdges; ++k) {
                if (incidenceMatrix[i][k] == 1 && incidenceMatrix[j][k] == 1) {
                    areNeighbors = true; // i и j имеют общее ребро
                    break;
                }
            }

            // Если i и j не соседи, проверяем, образует ли эта пара хорду в цикле
            if (!areNeighbors) {
                // Проверяем, существует ли путь между i и j через других соседей
                bool isChord = true;
                for (int k = 0; k < numVertices; ++k) {
                    if (k != i && k != j) {
                        if (incidenceMatrix[i][k] == 1 && incidenceMatrix[j][k] == 1) {
                            isChord = false; // Если есть путь между i и j через соседей, это не хорда
                            break;
                        }
                    }
                }
                if (isChord) {
                    chordCount++; // Это хорда
                }
            }
        }
    }

    return chordCount;
}

int main() {
    int numVertices, numEdges;

    setlocale(LC_ALL, "ru");

    // Запрашиваем количество вершин и количество ребер у пользователя
    cout << "Введите количество вершин (максимум " << MAX_VERTICES << "): ";
    cin >> numVertices;

    cout << "Введите количество ребер: ";
    cin >> numEdges;

    // Проверка на допустимое количество вершин и ребер
    if (numVertices < 1 || numVertices > MAX_VERTICES || numEdges < 0) {
        cout << "Ошибка: количество вершин должно быть в диапазоне от 1 до " << MAX_VERTICES << ", количество ребер не должно быть отрицательным." << endl;
        return 1;
    }

    int incidenceMatrix[MAX_VERTICES][MAX_VERTICES] = { 0 }; // Инициализация матрицы инцидентности

    // Ввод матрицы инцидентности
    cout << "Введите матрицу инцидентности (размер " << numVertices << " x " << numEdges << "):" << endl;
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numEdges; ++j) {
            cin >> incidenceMatrix[i][j];
        }
    }

    // Вывод матрицы инцидентности
    cout << "Матрица инцидентности графа:" << endl;
    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numEdges; ++j) {
            cout << incidenceMatrix[i][j] << " ";
        }
        cout << endl;
    }

    // Подсчет хорд
    int chordCount = countChords(incidenceMatrix, numVertices, numEdges);
    cout << "Количество хорд в графе: " << chordCount << endl;

    return 0;
}

