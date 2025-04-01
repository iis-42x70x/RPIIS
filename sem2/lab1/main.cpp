#include <iostream>
#include <vector>
#include "../lab1_1/Header.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	vector<mnozh> set;
	int size;
	cout << "Введите количество множеств ";
	cin >> size;
	create(size, set);
	cout << "1 - Определение множества по элементу " << '\n' << "2 - Объединение множеств " << '\n' << "3 - Просмотр множества" << '\n' << "4 - Выход" << '\n';
	int choice;
	while (true) {

		cout <<'\n'<< "Выберите действие: ";
		cin >> choice;
		switch (choice) {

		case 1: cout << "Выберите элемент ";
			char ch;
			cin >> ch;
			find(set, ch);
			break;

		case 2: cout << "Выберите множества ";
			int a, b;
			cin >> a >> b;
			Union(a, b, set);
			break;

		case 3: view(set);
			break;

		case 4: return 0;
			break;

		}
	}
}