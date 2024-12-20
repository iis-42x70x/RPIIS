#include <iostream>
#include <limits> 

using namespace std;

int main()
{
    int k, l, min, o, n, i, j;
    min=0;
    k = 5;
    l = k;
    int* counter = new int[k];
    int mas[5][5] = { { 0, 1, 1, 1, 0}, // матрица смежности
                      { 1, 0, 1, 1, 0},
                      { 1, 1, 0, 0, 1},
                      { 1, 1, 0, 0, 1},
                      { 0, 0, 1, 1, 0},
    };

    cout << "Выберите матрицу: \n 1 - моя заданная матрица смежности \n 2 - задать матрицу смежности самому" << endl;
    cin >> o;

    switch(o)
    {
        // 1 - заданная матрица
        case 1: { 
            for (int i = 0; i < 5; i++)
            {
                counter[i] = 0;
                for (int j = 0; j < 5; j++)
                {
                    if (mas[i][j]) 
                    {
                        if (i == j)
                        {
                            counter[i] += 2; // Для самосоединений
                        } 
                        else 
                        {
                            counter[i] += 1; // Для обычных рёбер
                        }
                    }
                }
            }

            min = counter[0];

            for (int i = 1; i < 5; i++)
            {
                if (counter[i] < min)
                    min = counter[i];

            }

            // Расчёт суммы степеней двух соединённых вершин
            int sumOfDegrees = 0;
            int minSum = INT_MAX; // Переменная для хранения минимальной суммы
            int minVertex1 = -1, minVertex2 = -1; // Для хранения вершин с минимальной суммой
            for (int i = 0; i < 5; i++)
            {
                for (int j = i + 1; j < 5; j++) // j начинается с i + 1, чтобы избежать дублирования
                {
                    if (mas[i][j] == 1) // Если существует ребро между вершинами i и j
                    {
                        sumOfDegrees = counter[i] + counter[j];

                        // Проверка на минимальную сумму
                        if (sumOfDegrees < minSum)
                        {
                            minSum = sumOfDegrees;
                            minVertex1 = i;
                            minVertex2 = j;
                        }
                    }
                }
            }

            // Выводим минимальную сумму
            if (minVertex1 != -1 && minVertex2 != -1)   
            {
                cout << "Минимальная степень ребра: " << minSum << endl;
            } 
            else 
            {
                cout << "Нет соединенных вершин." << endl;
            }

            delete[] counter;}
            break;

        // 2 - пользовательская матрица
        case 2:{
            cout << "Введите размерность матрицы (nxn): " << endl;
            cin >> n;
            cout << endl;
            double** mas1;
            mas1 = new double* [n];
            for (i = 0; i < n; i++)
                mas1[i] = new double[n];

            cout << "вводите элементы массива построчно" << endl;
            for (i = 0; i < n; i++)
                for (j = 0; j < n; j++)
                {
                    cin >> mas1[i][j];
                }

            for (int i = 0; i < n; i++)
            {
                counter[i] = 0;
                for (int j = 0; j < n; j++)
                {
                    if (mas[i][j]) 
                    {
                        if (mas[i][j])
                        {
                                if (i == j)
                            {
                                counter[i] += 2; // Для самосоединений
                            }    
                            else 
                            {
                                counter[i] += 1; // Для обычных рёбер
                            }
                        }
                    }
                }
            }

            
            min = counter[0];

            for (int i = 1; i < n; i++)
            {
                if (counter[i] < min)
                    min = counter[i];

            }

            // Расчёт суммы степеней двух соединённых вершин
            int sumOfDegrees = 0;
            int minSum = INT_MAX; // Переменная для хранения минимальной суммы
            int minVertex1 = -1, minVertex2 = -1; // Для хранения вершин с минимальной суммой
            for (int i = 0; i < n; i++)
            {
                for (int j = i + 1; j < n; j++) // j начинается с i + 1, чтобы избежать дублирования
                {
                    if (mas1[i][j] == 1) // Если существует ребро между вершинами i и j
                    {
                        int sumOfDegrees = counter[i] + counter[j];

                        // Проверка на минимальную сумму
                        if (sumOfDegrees < minSum)
                        {
                            minSum = sumOfDegrees;
                            minVertex1 = i;
                            minVertex2 = j;
                        }
                    }
                }
            }

            // Выводим минимальную сумму
            if (minVertex1 != -1 && minVertex2 != -1)   
            {
                cout << "Минимальная степень ребра: " << minSum << endl;
            } 
            else 
            {
                cout << "Нет соединенных вершин." << endl;
            }

            delete[] counter;
            for (i = 0; i < n; i++)
            delete[] mas1[i];
            delete[] mas1;
            mas1 = NULL;}
            break;
        }
    return 0;
}
