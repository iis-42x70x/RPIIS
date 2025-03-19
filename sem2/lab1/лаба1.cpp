#include"Header.h"
#include <iostream>
#include <vector>
#include <locale> 
#include <algorithm>

using namespace std;

void main()
{
 
    setlocale(LC_ALL, "Russian");
    bool swich = false;
	int o,n,kod,l,r,otvet=999,pos,otvet_mod;
    cout << "введите количествочисел  : ";
    cin >> n;
    o = 4 * n;
    int* t=new int [o]; 
    int* mas = new int[n];
    cout << "введите " << n << " чисел  : "<<endl;
    for (int i = 0; i < n; ++i) {
        int num;
        cin >> num;
        mas[i] = num;
        
    }
    if (n % 2 == 0)
        mas[n] = 0;

    cout << "исходный массив " << endl;
    for (int i = 0; i < n; ++i) {
        cout << mas[i]<<"\n";
    }
    
     while (true) {
        cout << "\nпостроить дерево   - 1.\nнайти максимум на отрезке  - 2.\nизменить элемент   - 3.\nEXIT - 0.\nWiew - 4.\n";
        cin >> kod;
        cout << endl;

        switch (kod) {
        case 1:
            build(mas, 1, 0, n - 1, t);
            cout << endl;
            for (int i = 1; i <o ; ++i) {
                cout << t[i] << "\n";
            }
            

        break;
        case 2:
            cout << endl;
            cout << "границы включены в отрезок " << endl;
            cout << "введите левую  границу отрезка(индекс в ранне заданом массиве ) " << endl;   
            cin >> l;
            cout << "введите правую границу отрезка(индекс в ранне заданом массиве ) " << endl;
            cin >> r;
            otvet=Max(1, 0, n - 1, l, r,t);
            cout << "максимум на отрезке от " << mas[l] << " до " << mas[r] << " равен= " << otvet;
            cout << endl;
        break;
        case 3:
            cout << "введите индекс меняемого элемента " << endl;
            cin >> pos;
            cout << "введите новое значение  меняемого элемента " << endl;
            cin >>otvet_mod;
            Mod(1, 0, n - 1,pos, otvet_mod, t);        
        break;
        case 4:
            cout << "Дерево отрезков:\n";
            printTree(t, 1, 0, n - 1);
            break;
        case 0:
            return;
        }
    }
     delete[]mas;
     delete[]t;     
}  
/*max(&mas)  так над будет передать вектор http://e-maxx.ru/algo/segment_tree */
