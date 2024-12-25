#include <vector>
#include <iostream>
#include <ctime>

using namespace std;

vector<vector<int>> sort(vector<vector<int>>& arr)
{
    vector<vector<int>> arr1;
    arr1.resize(arr.size(), vector<int>(arr.size()));

    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr.size(); j++) {
            if (i == j) {
                arr1[i][j] = 0;
            }
            else if (arr[i][j] != arr[j][i]) {
                arr1[i][j] = arr[i][j];
                arr1[j][i] = arr[i][j];
            }
            else if (arr[i][j] == arr[j][i]) {
                arr1[i][j] = arr[i][j];
                arr1[j][i] = arr[i][j];
            }
        }
    }

    arr.clear();
    arr = arr1;
    return arr;
}

vector<vector<int>> sort_after1(vector<vector<int>>& arr) 
{
    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr.size(); j++) {
            if (i != j && arr[i][j] == 0) {
                arr[i][j] = 1000;
            }
        }
    }

    return arr;
}

vector<vector<int>> sort_after2(vector<vector<int>>& arr)
{
    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr.size(); j++) {
            if (i != j && arr[i][j] == 1000) {
                arr[i][j] = 0;
            }
        }
    }

    return arr;
}

vector<int> sort_after3(vector<int>& per)
{
    vector<int> result; 

    for (int i = 0; i < per.size(); ++i) {
        bool isUnique = true; 
        for (int j = 0; j < result.size(); ++j) {
            if (per[i] == result[j]) {
                isUnique = false;  
                break; 
            }
        }
        if (isUnique) {
            result.push_back(per[i]);
        }
    }
    per.clear();
    per = result;
    return per;
}

int exc(vector<vector<int>>& arr) 
{
    int a = 0;
    vector<int> per;

    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr.size(); j++) {
            if (a < arr[i][j]) {
                a = arr[i][j];
            }
        }
    }

    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr.size(); j++) {
            if (a == arr[i][j]) {
                per.push_back(i);
                per.push_back(j);
            }
        }
    }

    sort_after3(per);

    for (int n = 0; n < per.size(); n++) {
        for (int k = 0; k < per.size(); k++) {
            if (a >= arr[per[n]][per[k]] && n!=k) {
                a = arr[per[n]][per[k]];
            }
        }
    }

    cout << "Минимальное расстояние между перефирийными вершинами данного графа = " << a << ";" << endl;
    return a;
}

double exc_average(vector<vector<int>>& arr)
{
    int a = 0;
    vector<int> per;

    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr.size(); j++) {
            if (a < arr[i][j]) {
                a = arr[i][j];
            }
        }
    }

    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr.size(); j++) {
            if (arr[i][j] == a) {
                per.push_back(i);
                per.push_back(j);
            }
        }
    }

    sort_after3(per);

    // Вычисляем среднее расстояние между всеми периферийными вершинами

    double b = 0;
    int c = 0;

    for (int i = 0; i < per.size(); i++) {
        for (int j = i + 1; j < per.size(); j++) {
            b += arr[per[i]][per[j]];
            c++;
        }
    }

    double d = c > 0 ? b / c : 0;

    cout << "Среднее расстояние между периферийными вершинами данного графа = " << d << ";\n\n\n" << endl;
    return d;
}

vector<vector<int>> path(vector<vector<int>>& arr)
{
    sort_after1(arr);

    for (int k = 0; k < arr.size(); k++) {
        for (int i = 0; i < arr.size(); i++) {
            for (int j = 0; j < arr.size(); j++) {
                if (arr[i][j] > arr[i][k] + arr[k][j]) {
                    arr[i][j] = arr[i][k] + arr[k][j];
                }
            }
        }
    }

    sort_after2(arr);
    return arr;
}

vector<vector<int>> matrix(int n, vector<vector<int>>& arr)
{
    int t;
    arr.resize(n, vector<int>(n));

    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr.size(); j++) {
            t = rand() % 2;
            arr[i][j] = t;
        }
        cout << endl;
    }

    sort(arr);
    return arr;
}

void output(vector<vector<int>> arr)
{
    cout << "Матрица смежности размером " << arr.size() << "x" << arr.size() << " (для графа, имещего " << arr.size() << " вершин)" << ":\n" << endl;

    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr.size(); j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;
}

void output_after(vector<vector<int>> arr)
{
    cout << "Матрица кратчайших путей после применения алгоритма Флойда-Уоршелла для данного графа: \n" << endl;

    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr.size(); j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;
}

int main()
{
    setlocale(LC_ALL, "Rus");
    srand(time(NULL));
    
    int a;
    vector<vector<int>> arr;

    do {
        cout << "Выберите одну из 6 опций:\n\n\t1. Решение задания для графа, имеющего 5 вершин;\n\t2. Решение задания для графа, имеющего 6 вершин;\n\t3. Решение задания для графа, имеющего 7 вершин;\n\t4. Решение задания для графа, имеющего 8 вершин;\n\t5. Решение задания для графа, имеющего 9 вершин;\n\t6. Выход.\n\n\tВаш выбор: ";
        cin >> a;
    
        switch (a) {
        case 1: 
            output(matrix(5, arr));
            output_after(path(arr)); 
            exc(arr);
            exc_average(arr);
            arr.clear();
            break;
        case 2:
            output(matrix(6, arr));
            output_after(path(arr));
            exc(arr);
            exc_average(arr);
            arr.clear();
            break;
        case 3:
            output(matrix(7, arr));
            output_after(path(arr));
            exc(arr);
            exc_average(arr);
            arr.clear();
            break;
        case 4:
            output(matrix(8, arr));
            output_after(path(arr));
            exc(arr);
            exc_average(arr);
            arr.clear();
            break;
        case 5:
            output(matrix(9, arr));
            output_after(path(arr));
            exc(arr);
            exc_average(arr);
            arr.clear();
            break;
        case 6:
            cout << "\nВыход из программы." << endl;
            break;
        }
    } while (a != 6);
}