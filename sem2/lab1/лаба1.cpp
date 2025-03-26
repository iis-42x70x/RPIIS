
#include"Header.h"
#include <iostream>
#include <vector>
#include <locale> 
#include <algorithm>


using namespace std;
#include"Header.h"	

void main()
{
 
    setlocale(LC_ALL, "Russian");
    bool swich = false;
	int o,n=-1,kod,l,r,otvet=999,pos,otvet_mod;
    while (n < 0) {
        cout << "введите количествочисел  : ";
        cin >> n;
    }
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
        cout << "\n построить дерево - 1.\n найти максимум на отрезке - 2.\n изменить элемент - 3.\n показать дерево - 4.\n выход - 0.\n";
        cin >> kod;
        cout << endl;

        switch (kod) {
        case 1:
            build(mas, 1, 0, n - 1, t);
            cout << endl;
           cout << "дерево построено " << "\n";
                   

        break;
        case 2:
            cout << endl;
            cout << "границы включены в отрезок " << endl;
            cout << "введите левую  границу отрезка(индекс в ранне заданом массиве ) " << endl;   
            cin >> l;
            cout << "введите правую границу отрезка(индекс в ранне заданом массиве ) " << endl;
            cin >> r;
            if (l > n - 1 || r > n - 1 || l > r || l < 0 || r < 0) {
                cout << "ошибка ввода" << endl;
                break;
            }
            otvet=Max(1, 0, n - 1, l, r,t);
            cout << "максимум на отрезке от " << l << " до " << r<< " равен= " << otvet;
            cout << endl;
        break;
        case 3:
            cout << "введите индекс меняемого элемента " << endl;
            cin >> pos; 
            cout << "введите новое значение  меняемого элемента " << endl;
            cin >>otvet_mod;
            Mod(1, 0, n - 1,pos, otvet_mod, t); 
            cout << "элемент изменён \n";
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
 
