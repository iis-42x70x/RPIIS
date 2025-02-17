#include "BinarySearchTree.h"
#include <iostream>
#include <vector>

using namespace std;

void DisplayMenu() {
	cout << "Меню операций с бинарным деревом поиска:\n";
	cout << "1. Вставить узел\n";
	cout << "2. Поиск узла\n";
	cout << "3. Удалить узел\n";
	cout << "4. Симметричный (in-order) обход\n";
	cout << "5. Прямой (pre-order) обход\n";
	cout << "6. Обратный (post-order) обход\n";
	cout << "7. Построить дерево из массива\n";
	cout << "8. Очистить дерево\n";
	cout << "9. Выход\n";
	cout << "Введите ваш выбор: ";
}

int main() {
	setlocale(LC_ALL, "ru");
	BinarySearchTree tree;
	int choice;
	int value;
	vector<int> values;

	do {
		DisplayMenu();
		cin >> choice;

		switch (choice) {
		case 1:
			cout << "Введите значение для вставки: ";
			cin >> value;
			tree.Insert(value);
			cout << "Значение вставлено.\n";
			break;
		case 2:
			cout << "Введите значение для поиска: ";
			cin >> value;
			if (tree.Search(value)) {
				cout << "Значение " << value << " найдено в дереве.\n";
			}
			else {
				cout << "Значение " << value << " не найдено в дереве.\n";
			}
			break;
		case 3:
			cout << "Введите значение для удаления: ";
			cin >> value;
			tree.Remove(value);
			cout << "Значение удалено (если оно существовало).\n";
			break;
		case 4:
			cout << "Симметричный (in-order) обход: ";
			tree.InOrderTraversal();
			break;
		case 5:
			cout << "Прямой (pre-order) обход: ";
			tree.PreOrderTraversal();
			break;
		case 6:
			cout << "Обратный (post-order) обход: ";
			tree.PostOrderTraversal();
			break;
		case 7:
			cout << "Введите количество элементов: ";
			int n;
			cin >> n;
			values.clear();
			values.resize(n);
			cout << "Введите " << n << " элементов: ";
			for (int i = 0; i < n; ++i) {
				cout << "Введите элемент " << i + 1 << ": ";
				cin >> values[i];
			}
			tree.BuildFromArray(values);
			cout << "Дерево построено из массива.\n";
			break;
		case 8:
			tree.Clear();
			cout << "Дерево очищено.\n";
			break;
		case 9:
			cout << "Выход...\n";
			break;
		default:
			cout << "Некорректный выбор. Пожалуйста, попробуйте снова.\n";
			break;
		}
	} while (choice != 9);

	return 0;
}
