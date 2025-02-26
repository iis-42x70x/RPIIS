#include <iostream>
#include "D:\учёба\пивас\dn_spisok\лаба_1\Header.h"

using namespace std;


int main()
{
    Node* list1 = nullptr;
    Node* list2 = nullptr;
    while (true)
    {
        menu();
        int k;
        cin >> k;
        vybor(k, &list1, &list2);
    }
}
