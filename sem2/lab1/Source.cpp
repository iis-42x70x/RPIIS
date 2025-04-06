#include <iostream>
#include <vector>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
const int NUMBER = 1000;
long long mass[NUMBER], core[NUMBER];
int num, oper;

long long sum(int count)
{
    long long summa = 0;
    for (int i = count; i >= 0; i = (i & (i + 1)) - 1)
        summa += mass[i];
    return summa;
}

void update(int position, long long value)
{
    for (int j = position; j <= num; j = j | (j + 1))
    {
        mass[j] += value;
    }
}

int main()
{
    setlocale(LC_ALL, "Russian");

    cout << "¬ведите количество элементов массива: ";
    cin >> num; cout << endl;
    cout << "¬ведите количество операций, которые вы хотите провести (если не уверены, введите большое число): ";
    cin >> oper; cout << endl;
    cout << "‘орма запроса: (A i x) - присвоить i-тому элементу массива значение x; (Q l r) - найти сумму значений элементов на позици€х от l до r." << endl;
    cout << "ƒл€ преждевременного прекращени€ работы программы введите 'End' вместо 'A' или 'Q' " << endl;
    for (int i = 0; i < oper; i++)
    {
        char swch;
        int count1, count2;
        cout << "¬ведите свой запрос в форме 'A i x' или 'Q l r': " << endl;
        cin >> swch >> count1 >> count2;
        if (swch != 'End') {
            if (swch == 'A')
            {
                update(count1, count2 - core[count1]);
                core[count1] = count2;
            }
            else if (swch == 'Q') {
                cout << "Summa ravna " << sum(count2) - sum(count1 - 1) << endl;
            }
        }
    }
}