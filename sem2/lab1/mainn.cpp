#include <iostream>
#include <string>
#include "Node.h"; 
#include "bor.h";
using namespace std;


int main(){
	setlocale(LC_ALL, "ru");

	int n = 0;
	string s;
	Node* root = new Node();
	root->back_ptr = new Node(root);

	do{
		cout << "Выберите действие:\n 1 - Добавить строку\n 2 - Удалить строку\n 3 - Найти строку\n 4 - Просмотреть\n 0 - Удалить бор и выйти \n" << endl;
		cin >> n;

		switch (n){
		case 1:
			cout << "Введите строку для добавления: ";
			cin >> s;
			add_string(s, root);
			break;
		case 2:
			cout << "Введите строку для удаления: ";
			cin >> s;
			delete_string(s, root);
			break;
		case 3:
			cout << "Введите строку для поиска: ";
			cin >> s;
			search_string(s, root);
			break;
		case 4:
			cout << "------Бор------" << endl;
			view_bor(root);
			break;
		case 0:
			delete root->back_ptr;
			delete_bor(root);
			return 0;
		default:
			cout << "Нет такого действия";
		}
	} while (true);
}