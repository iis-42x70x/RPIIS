//#include <iostream>
//#include <vector>
//using namespace std;
//
//class FenwickTree {
//private:
//    vector<long long> mass; 
//    vector<long long> core;  
//    int num;                 
//
//public:
//    FenwickTree(int size) : num(size), mass(size + 1, 0), core(size + 1, 0) {}
//
//  
//    long long sum(int count) {
//        long long summa = 0;
//        for (int i = count; i >= 0; i = (i & (i + 1)) - 1)
//            summa += mass[i];
//        return summa;
//    }
//
//   
//    void update(int position, long long value) {
//        for (int j = position; j <= num; j = j | (j + 1))
//            mass[j] += value;
//    }
//
//    void set(int position, long long value) {
//        long long delta = value - core[position];
//        update(position, delta);
//        core[position] = value;
//    }
//
//    long long query(int l, int r) {
//        return sum(r) - sum(l - 1);
//    }
//};
#include "FenwikTree.hpp";



int main() {
    setlocale(LC_ALL, "Russian");

    cout << "¬ведите количество элементов массива: ";
    int num;
    cin >> num;
    cout << endl;

    cout << "¬ведите количество операций, которые вы хотите провести (если не уверены, введите большое число): ";
    int oper;
    cin >> oper;
    cout << endl;

    FenwickTree fenwickTree(num);

    cout << "‘орма запроса: (A i x) - присвоить i-тому элементу массива значение x; (Q l r) - найти сумму значений элементов на позици€х от l до r." << endl;
    cout << "ƒл€ преждевременного прекращени€ работы программы введите 'End' вместо 'A' или 'Q'." << endl;

    for (int i = 0; i < oper; i++) {
        char swch;
        int count1, count2;
        cout << "¬ведите свой запрос в форме 'A i x' или 'Q l r': " << endl;
        cin >> swch >> count1 >> count2;

        if (swch == 'End') {
            break;
        }
        else if (swch == 'A') {
            fenwickTree.set(count1, count2);
        }
        else if (swch == 'Q') {
            cout << "—умма равна " << fenwickTree.query(count1, count2) << endl;
        }
    }

    return 0;
}