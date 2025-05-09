#include <iostream>
#include "B-Tree.h"

using namespace std;

int main()
{
	BTree b_t(3); 
	PrettyPrint printer;

	srand(2478);



	cout << "\n \t----------ВСТАВКА----------\n";
	for (unsigned i = 0; i < 16; ++i)
	{
		int p = rand() % 100;
		cout << "\n## Дерево после вставки " << p << ":\n\n";
		b_t.insert_key(p);
		printer.print(b_t);
	}



	cout << "\n\n\t----------УДАЛЕНИЕ----------\n";

	cout << "Дерево после удаления 0: \n";
	b_t.delete_key(0);
	printer.print(b_t);

	cout << "\nДерево после удаления 32: \n";
	b_t.delete_key(32);
	printer.print(b_t);



	cout << "\n\n \t----------ПОИСК----------\n";

	(b_t.search_key(7)) ? cout << "Ключ 7 есть в дереве" : cout << "Ключ 7 не найден";
	cout << endl << endl;

	(b_t.search_key(17)) ? cout << "Ключ 17 есть в дереве" : cout << "Ключ 17 не найден";
	cout << endl;

	return 0;
}























/*cout << "\n \t----------ВСТАВКА----------\n";

b_t.insert_key(1);
cout << " 7: \n";
printer.print(b_t);
cout << "\n";
b_t.insert_key(3);
cout << "Дерево после вставки 3: \n";
printer.print(b_t);
cout << "\n";
b_t.insert_key(7);
cout << "Дерево после вставки 1: \n";
printer.print(b_t);
cout << "\n";
b_t.insert_key(10);
cout << "Дерево после вставки 33: \n";
printer.print(b_t);
cout << "\n";
b_t.insert_key(11);
cout << "Дерево после вставки 11: \n";
printer.print(b_t);
cout << "\n";
b_t.insert_key(13);
cout << "Дерево после вставки 13: \n";
printer.print(b_t);
cout << "\n";
b_t.insert_key(14);
cout << "Дерево после вставки 14: \n";
printer.print(b_t);
cout << "\n";
b_t.insert_key(15);
cout << "Дерево после вставки 15: \n";
printer.print(b_t);
cout << "\n";
b_t.insert_key(18);
cout << "Дерево после вставки 18: \n";
printer.print(b_t);
cout << "\n";
b_t.insert_key(16);
cout << "Дерево после вставки 16: \n";
printer.print(b_t);
cout << "\n";
b_t.insert_key(19);
cout << "Дерево после вставки 19: \n";
printer.print(b_t);
cout << "\n";
b_t.insert_key(24);
cout << "Дерево после вставки 24: \n";
printer.print(b_t);
cout << "\n";
b_t.insert_key(25);
cout << "Дерево после вставки 25: \n";
printer.print(b_t);
cout << "\n";
b_t.insert_key(26);
cout << "Дерево после вставки 26: \n";
printer.print(b_t);
cout << "\n";
b_t.insert_key(21);
cout << "Дерево после вставки 21: \n";
printer.print(b_t);
cout << "\n";
b_t.insert_key(4);
cout << "Дерево после вставки 4: \n";
printer.print(b_t);
cout << "\n";
b_t.insert_key(5);
cout << "Дерево после вставки 5: \n";
printer.print(b_t);
cout << "\n";
b_t.insert_key(20);
cout << "Дерево после вставки 20: \n";
printer.print(b_t);
cout << "\n";
b_t.insert_key(22);
cout << "Дерево после вставки 22: \n";
printer.print(b_t);
cout << "\n";
b_t.insert_key(2);
cout << "Дерево после вставки 2: \n";
printer.print(b_t);
cout << "\n";
b_t.insert_key(17);
cout << "Дерево после вставки 17: \n";
printer.print(b_t);
cout << "\n";
b_t.insert_key(12);
cout << "Дерево после вставки 12: \n";
printer.print(b_t);
cout << "\n";
b_t.insert_key(6);
cout << "Дерево после вставки 6: \n";
printer.print(b_t);*/