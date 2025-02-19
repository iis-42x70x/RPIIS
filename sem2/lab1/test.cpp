#include <iostream>
#include "spis.hpp"
#include <locale>
using namespace std;

void TestInsertion() {
    cout << "Тест: Вставка элементов в список" << endl;
    Spis* list = nullptr;

    list = InSpis(list, 10);
    list = InSpis(list, 20);
    list = InSpis(list, 30);

    cout << "Ожидаемый результат: 30 20 10" << endl;
    cout << "Фактический результат: ";
    View(list);

    Del_All(&list);
    cout << "--------------------------" << endl;
}

void TestDeletion() {
    cout << "Тест: Удаление элемента из списка" << endl;
    Spis* list = nullptr;

    list = InSpis(list, 10);
    list = InSpis(list, 20);
    list = InSpis(list, 30);

    Del_Elem(&list, 20); // Удаляем элемент 20

    cout << "Ожидаемый результат: 30 10" << endl;
    cout << "Фактический результат: ";
    View(list);

    Del_All(&list);
    cout << "--------------------------" << endl;
}

void TestSorting() {
    cout << "Тест: Сортировка списка" << endl;
    Spis* list = nullptr;

    list = InSpis(list, 3);
    list = InSpis(list, 1);
    list = InSpis(list, 4);
    list = InSpis(list, 2);

    Sort_info(list);

    cout << "Ожидаемый результат: 1 2 3 4" << endl;
    cout << "Фактический результат: ";
    View(list);

    Del_All(&list);
    cout << "--------------------------" << endl;
}

void TestSearch() {
    cout << "Тест: Поиск элемента" << endl;
    Spis* list = nullptr;

    list = InSpis(list, 10);
    list = InSpis(list, 20);
    list = InSpis(list, 30);

    cout << "Ожидаемый результат: Найден" << endl;
    cout << "Фактический результат: ";
    Search(list, 20);

    cout << "Ожидаемый результат: Не найден" << endl;
    cout << "Фактический результат: ";
    Search(list, 50);

    Del_All(&list);
    cout << "--------------------------" << endl;
}

void TestUnion() {
    cout << "Тест: Объединение списков" << endl;
    Spis* list1 = nullptr;
    Spis* list2 = nullptr;

    list1 = InSpis(list1, 1);
    list1 = InSpis(list1, 2);
    list1 = InSpis(list1, 3);

    list2 = InSpis(list2, 3);
    list2 = InSpis(list2, 4);
    list2 = InSpis(list2, 5);

    Union(list1, list2);

    Del_All(&list1);
    Del_All(&list2);
    cout << "--------------------------" << endl;
}

void TestIntersection() {
    cout << "Тест: Пересечение списков" << endl;
    Spis* list1 = nullptr;
    Spis* list2 = nullptr;

    list1 = InSpis(list1, 1);
    list1 = InSpis(list1, 2);
    list1 = InSpis(list1, 3);

    list2 = InSpis(list2, 3);
    list2 = InSpis(list2, 4);
    list2 = InSpis(list2, 5);

    Intersection(list1, list2);

    Del_All(&list1);
    Del_All(&list2);
    cout << "--------------------------" << endl;
}
#ifdef TEST_MODE 
int main(){
    setlocale(LC_ALL, "ru");
    TestInsertion();
    TestDeletion();
    TestSorting();
    TestSearch();
    TestUnion();
    TestIntersection();
    return 0;
}
#endif