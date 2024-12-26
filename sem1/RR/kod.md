#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    int n; // Количество вершин графа
    cout << "Введите количество вершин графа: ";
    cin >> n;

    vector<vector<int>> Matrix(n, vector<int>(n)); // Матрица смежности

    cout << "Введите матрицу смежности:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> Matrix[i][j];
        }
    }

    int min = INT_MAX; // Инициализируем минимальное количество единиц большим значением

    for (int i = 0; i < n; ++i) {
        int count1 = 0;

        for (int j = 0; j < n; ++j) {
            if (Matrix[i][j] == 1) {
                count1++;
            }
        }

        // Обновляем минимальное количество единиц и индекс строки, если текущий счетчик меньше
        if (count1 < min) {
            min = count1;
        }
    }

    cout <<  "Наименьшая степень вершин графа: " << min  << endl;

    return 0;
}
