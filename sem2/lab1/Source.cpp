#include "AVL.h"
#include <iostream>
#include <conio.h>
using namespace std;

template<typename T>
T getValidatedInput() {
	T value;
	while (!(cin >> value)) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Error. Try again: ";
	}
	return value;
}

int menu() {
	cout << "1. Add element to AVL" << endl
		<< "2. Delete element from AVL by key" << endl
		<< "3. Print PreOrder" << endl
		<< "4. Print PostOrder" << endl
		<< "5. Print InOrder" << endl
		<< "6. Get data by key" << endl
		<< "7. Get AVL size" << endl
		<< "8. Find max" << endl
		<< "9. Find min" << endl
		<< "10. Find nearest max" << endl
		<< "11. Find nearest min" << endl
		<< "12. Clear AVL" << endl
		<< "Any other key to exit" << endl
		<< "Please make choice: ";
	int choice;
	cin >> choice;
	return (cin.fail()) ? 0 : choice;
}

int main()
{
	using T1 = int;
	using T2 = int;
	AVL<T1, T2> avl;

	T1 key;
	T2 data;
	avl.insert(30, 1);
	avl.insert(15, 1);
	avl.insert(45, 1);
	avl.insert(7, 1);
	avl.insert(20, 1);
	avl.insert(37, 1);
	avl.insert(50, 1);
	avl.insert(4, 1);
	avl.insert(70, 1);
	avl.insert(5, 1);
	avl.insert(60, 1);

	while (true) {
		switch (menu()) {
		case 1:
			cout << "Enter key: ";
			key = getValidatedInput<T1>();
			cout << "Enter data: ";
			data = getValidatedInput<T2>();
			avl.insert(key, data);
			break;

		case 2:
			cout << "Enter key to delete: ";
			key = getValidatedInput<T1>();
			avl.deleteAt(key);
			break;

		case 3: avl.printPreOrder(); break;

		case 4: avl.printPostOrder(); break;

		case 5: avl.printInOrder(); break;

		case 6:
			cout << "Enter key to get data: ";
			key = getValidatedInput<T1>();
			cout << "Data: " << avl.getDataAt(key) << endl;
			break;

		case 7:	cout << "AVL size is " << avl.getSize() << endl; break;

		case 8: cout << "Max key is " << avl.getMax() << endl; break;

		case 9:  cout << "Min key is " << avl.getMin() << endl; break;

		case 10:  
			cout << "Enter key: ";
			key = getValidatedInput<T1>();
			cout << "Nearest max key is " << avl.getNearestMax(key) << endl; break;

		case 11:  
			cout << "Enter key: ";
			key = getValidatedInput<T1>();
			cout << "Nearest min key is " << avl.getNearestMin(key) << endl; break;

		case 12:
			avl.clear();
			cout << "AVL has been successfully cleared!" << endl;
			break;

		default:
			cout << "Exiting program..." << endl;
			return 0;
		}
		cout << "Press any key to continue..." << endl;
		_getch();
		system("cls");
	}
}