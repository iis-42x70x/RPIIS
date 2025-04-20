#include "Header.h"
#include <iostream>
using namespace std;

int main()
{
	vector<Union> sets;
	vector<string> result;
	int count, choice = -1;
	setlocale(LC_ALL, "Russian");
	while (choice <= 0 || choice > 2)
	{
		cout << "Выберите пункт меню: " << endl;
		cout << "--------------------------" << endl;
		cout << "1 - Ввести множества вручную" << endl;
		cout << "2 - Считать множества из файла" << endl;
		cout << "0 - Завершить программу досрочно" << endl;
		cout << "--------------------------" << endl;
		cout << "Ваш выбор: ";
		while (!(cin >> choice))
		{
			cout << "Вы ввели строку. Повторите попытку: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		
		switch (choice)
		{
		case 1:
		{
			cout << "Введите количество множеств: ";
			while (!(cin >> count) || count < 0)
			{
				cout << "Вы ввели строку или отрицательное число. Повторите попытку: ";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			cin.ignore();
			sets.resize(count);
			for (int i = 0; i < count; i++)
			{
				string set;
				cout << "Введите " << i + 1 << "-е множество: ";
				getline(cin, set);
				while (!sets[i].Correct_Set(set))
				{
					getline(cin, set);
				}
				sets[i].add(set);
			}
			break;
		}
		case 2:
		{
			read_file(sets);
			for (int i = 0; i < sets.size(); i++)
			{
				cout << i + 1 << "-е множество: ";
				printUnion(sets[i].getSet());
			}
			break;
		}
		case 0:
		{
			cout << "Программа завершена" << endl;
			break;
		}
		default:
		{
			cout << "Неверный вводповторите попытку" << endl;
			break;
		}
		}
	}

	result = sets[0].getSet();
	cout << "Объединение множеств: ";
	for (int i = 1; i < sets.size(); i++)
	{
		result = sets[i].setsUnion(result);
	}
	printUnion(result);
	return 0;
}