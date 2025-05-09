#include <iostream>
#include "library.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");
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

	cout << "Дерево после удаления 42: \n";
	b_t.delete_key(42);
	printer.print(b_t);

	cout << "\nДерево после удаления 26: \n";
	b_t.delete_key(26);
	printer.print(b_t);



	cout << "\n\n \t----------ПОИСК----------\n";

	(b_t.search_key(93)) ? cout << "Ключ 93 есть в дереве" : cout << "Ключ 7 не найден";
	cout << endl;
	cout << endl;
	(b_t.search_key(3)) ? cout << "Ключ 3 есть в дереве" : cout << "Ключ 17 не найден";
	cout << endl;

	return 0;
}
