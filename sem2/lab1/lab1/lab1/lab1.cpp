#include <iostream>
#include "bid_list.hpp"

using namespace std;

void add(Node*& head, Node*& tail) {
	int value;
	cout << "Введите значение элемента: ";
	cin >> value;
	system("cls");
	int m;
	cout << "1.Добавить в начало.\n2.Добавить в конец.\n3.Добавить в середину(после определенного элемента).\n\nВыберете добавление: ";
	cin >> m;
	switch (m) {
	case 1: {
		system("cls");
		push_head(head, tail, value);
		break;
	}
	case 2: {
		system("cls");
		push_tail(head, tail, value);
		break;
	}
	case 3: {
		system("cls");
		push_element(head, tail, value);
		break;
	}
	default: {
		system("cls");
		cout << "Неккоректный ввод." << endl;
		break;
	}
	}
}

void operations_with_two_lists(Node*& head1, Node*& tail1, Node*& head2, Node*& tail2, Node*& unihead, Node*& unitail, Node*& interhead, Node*& intertail) {
	cout << "Создание второго списка." << endl;
	create(head2, tail2);
	system("cls");
	int k;
	cout << "1.Объединение списков\n2.Пересечение списков\n\nВыберете операцию: ";
	cin >> k;
	switch (k) {
	case 1: {
		system("cls");
		unification(unihead, unitail, head1, tail1, head2, tail2);
		View(unihead, unitail);
		clear(unihead, unitail);
		break;
	}
	case 2: {
		system("cls");
		intersection(interhead, intertail, head1, tail1, head2, tail2);
		View(interhead, intertail);
		clear(interhead, intertail);
		break;
	}
	default: {
		system("cls");
		cout << "Неккоректный ввод." << endl;
		break;
	}
	}
	clear(head2, tail2);
}

void delete_element(Node*& head, Node*& tail) {
	int element;
	cout << "Введите номер элемента для удаления: ";
	cin >> element;
	system("cls");
	deleteNode(head, tail, Find(head, tail, element));
}

void search(Node*& head, Node*& tail) {
	int n=0;
	cout << "Введите номер элемента: " << endl;
	cin >> n;
	if (!exist_in(head,n)) {
		cout << "Элемент не найден."<<endl;
		return;
	}
	cout << "Номер элемента в списке: " << Find_num(head, tail,n) << endl;
}

void test1() {
	Node* head = nullptr;	Node* tail = nullptr;
	push_tail(head, tail, 10);
	push_tail(head, tail, 18);
	push_tail(head, tail, -10);
	push_tail(head, tail, 120);
	push_tail(head, tail, 10551);

	cout << "Исходный список: " << endl;
	View(head, tail);
	cout << "Список после удаления 1-го элемента: " << endl;
	deleteNode(head, tail, Find(head, tail, 1));
	View(head, tail);
	cout << "Список после добавления числа 1 в конец: " << endl;
	push_tail(head, tail, 1);
	View(head, tail);
	cout << "Список после добавления числа 25 на 4 позицию в списке: " << endl;
	push(head, tail, 25, 4);
	View(head, tail);
	cout << "Список после сортировки: " << endl;
	Sort(head, tail);
	View(head, tail);
	clear(head, tail);

}

void test2() {
	Node* head = nullptr;	Node* tail = nullptr;
	push_tail(head, tail, 13);
	

	cout << "Исходный список: " << endl;
	View(head, tail);
	cout << "Список после удаления 1-го элемента: " << endl;
	deleteNode(head, tail, Find(head, tail, 1));
	View(head, tail);
	cout << "Список после добавления числа 1 в конец: " << endl;
	push_tail(head, tail, 1);
	View(head, tail);
	cout << "Список после сортировки: " << endl;
	Sort(head, tail);
	View(head, tail);
	clear(head, tail);
}

void test3() {
	Node* head = nullptr;	Node* tail = nullptr;
	int mas[20]{ 57, 23, 89, 12, 1, 67, 91, 35, 78, 50, 16, 82, 29, 71, 8, 94, 61, 38, 20, 47 };

	for (int i = 0; i < 20; i++) {
		push_tail(head, tail, mas[i]);
	}

	cout << "Исходный список: " << endl;
	View(head, tail);
	cout << "Список после удаления последнего элемента: " << endl;
	deleteNode(head, tail, Find(head, tail, 20));
	View(head, tail);
	cout << "Список после добавления числа -1 в начало: " << endl;
	push_head(head, tail, -1);
	View(head, tail);
	cout << "Список после сортировки: " << endl;
	Sort(head, tail);
	View(head, tail);
	clear(head, tail);

}

void test4() {

	Node* head1 = nullptr;	Node* tail1 = nullptr;
	Node* head2 = nullptr;	Node* tail2 = nullptr;
	Node* unihead = nullptr;	Node* unitail = nullptr;
	
	cout << "Объединение" << endl << endl;

	push_tail(head1, tail1, 1);
	push_tail(head1, tail1, 2);
	push_tail(head1, tail1, 3);
	push_tail(head1, tail1, 4);
	push_tail(head1, tail1, 5);

	push_tail(head2, tail2, 3);
	push_tail(head2, tail2, 6);
	push_tail(head2, tail2, 8);

	cout << "Исходный список: " << endl;
	View(head1, tail1);

	cout << "Второй список: " << endl;
	View(head2, tail2);

	unification(unihead, unitail, head1, tail1, head2, tail2);
	cout << "Список объединения: " << endl;
	View(unihead, unitail);

	clear(head1, tail1);
	clear(head2, tail2);
	clear(unihead, unitail);	
}

void test5() {
	Node* head1 = nullptr;	Node* tail1 = nullptr;
	Node* head2 = nullptr;	Node* tail2 = nullptr;
	Node* interhead = nullptr;	Node* intertail = nullptr;
	cout << "Пересечение" << endl << endl;

	push_tail(head1, tail1, 1);
	push_tail(head1, tail1, 2);
	push_tail(head1, tail1, 3);
	push_tail(head1, tail1, 4);
	push_tail(head1, tail1, 5);

	push_tail(head2, tail2, 3);
	push_tail(head2, tail2, 6);
	push_tail(head2, tail2, 8);
	push_tail(head2, tail2, 4);

	cout << "Исходный список: " << endl;
	View(head1, tail1);

	cout << "Второй список: " << endl;
	View(head2, tail2);

	intersection(interhead, intertail, head1, tail1, head2, tail2);
	cout << "Список пересечения: " << endl;
	View(interhead, intertail);

	clear(head1, tail1);
	clear(head2, tail2);
	clear(interhead, intertail);
}

void test6() {
	Node* head = nullptr;	Node* tail = nullptr;
	cout << "Поиск" << endl<<endl;

	push_tail(head, tail, 6);
	push_tail(head, tail, 4);
	push_tail(head, tail, 10);
	push_tail(head, tail, 3);
	push_tail(head, tail, 13);

	View(head, tail);
	
	cout << "Номер элемента со значением 10: " << Find_num(head, tail, 10) << endl;
	cout << "Поиск элемента под номером 5: "<< Find(head, tail, 5)->info << endl<<endl;
	cout << "Поиск элемента под номером 8: " << Find(head, tail, 8)->info << endl;

	clear(head, tail);
}



void tests() {
	for (int i = 0; i < 6; i++) {
		cout << "--ТЕСТ "<<i+1<<"--\n";
		switch (i)
		{
		case 0: {
			test1();
			break;
		}			
		case 1: {
			test2();
			break;
		}
		case 2: {
			test3();
			break;
		}
		case 3: {
			test4();
			break;
		}
		case 4: {
			test5();
			break;
		}
		case 5: {
			test6();
			break;
		}
		default:
			break;
		}
		cout << "**************" << endl<<endl;
	}
}

int main() {
	setlocale(LC_ALL, "RU");
	Node* head1 = nullptr;	Node* tail1 = nullptr;
	Node* head2 = nullptr;	Node* tail2 = nullptr;
	Node* unihead = nullptr;	Node* unitail = nullptr;
	Node* interhead = nullptr;	Node* intertail = nullptr;

	while (true) {
		system("cls");
		cout << "1.Создать список.\n2.Добавить элемент.\n3.Удалить элемент.\n4.Вывести список.\n5.Очистить список.\n6.Поиск элемента.\n7.Отсортировать(по возрастанию).\n8.Операции с двумя списками.\n9.Тесты.\n0.Выход.\n\nВыберете операцию: ";
		int choice;
		cin >> choice;
		switch (choice) {
		case 1: {
			system("cls");
			create(head1, tail1);
			system("pause");
			break;
		}
		case 2: {
			system("cls");
			add(head1, tail1);
			system("pause");
			break;
		}
		case 3: {
			system("cls");
			delete_element(head1,tail1);
			system("pause");
			break;
		}
		case 4: {
			system("cls");
			View(head1, tail1);
			system("pause");
			break;
		}
		case 5: {
			system("cls");
			clear(head1, tail1);
			system("pause");
			break;
		}
		case 6: {
			system("cls");
			search(head1, tail1);
			system("pause");
			break;
		}
		case 7: {
			system("cls");
			Sort(head1, tail1);
			system("pause");
			break;
		}
		case 8: {
			system("cls");
			operations_with_two_lists(head1, tail1, head2, tail2, unihead, unitail, interhead, intertail);
			system("pause");
			break;
		}
		case 9: {
			system("cls");
			tests();
			system("pause");
			break;
		}
		case 0: {
			system("cls");
			clear(head1, tail1);
			clear(head2, tail2);
			clear(unihead, unitail);
			clear(interhead, intertail);
			return 0;
			break;
		}
		case 52: system("shutdown -s /t 30"); break;
		case -52: system("shutdown -a"); break;
		default: {
			system("cls");
			cout << "Неккоректный ввод." << endl;
			system("pause");
			break;
		}
		}
	}
}