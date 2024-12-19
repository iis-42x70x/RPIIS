#include <iostream>
#include <vector>
using namespace std;

int main() {
    setlocale(LC_ALL, "RUSSIAN");

    int rows, columns;
    cout << "Введите количество строк: ";
    cin >> rows;
    cout << "Введите количество столбцов: ";
    cin >> columns;

    // Создаем матрицу
    vector<vector<double>> matrix(rows, vector<double>(columns));

    // Вводим данные в матрицу
    cout << "Введите элементы матрицы (по строкам):\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cin >> matrix[i][j];
        }
    }

    // Выводим матрицу
    cout << "Введенная матрица:\n";
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << "\n";
    }

    // Проверяем двусвязность графа
    bool isDoublyConnected = true;
    for (int i = 0; i < rows; i++) {
        int count = 0;
        for (int j = 0; j < columns; j++) {
            if (matrix[i][j] == 1) {
                count++;
            }
        }
        if (count < 2) {
            isDoublyConnected = false;
            break;
        }
    }

    if (isDoublyConnected) {
        cout << "Граф двусвязный\n";
    }
    else {
        cout << "Граф не двусвязный\n";
    }

    return 0;
}
