#include <iostream>
#include "Human.hpp"
using namespace std;

bool correctInput() {
	if (cin.fail() || cin.peek() != '\n') {
		cin.clear();
		cin.ignore(32767, '\n');
		cout << "Неверный ввод!" << endl;
		return false;
	}
	else {
		cin.ignore();
		return true;
	}
}

Human addHum() {
	char* newFIO = new char[100];
	int newPoints, newPlace;
	Human newHuman;
	cout << "Введите ФИО: ";
	cin.get(newFIO, 100, '\n');
	if (!correctInput())
		return addHum();
	newHuman.FIO = newFIO;
	cout << "Введите очки: ";
	cin >> newPoints;
	if (newPoints < 0) {
		cin.clear();
		cin.ignore(32767, '\n');
		cout << "Неверный ввод!" << endl;
		return addHum();
	}
	if (!correctInput())
		return addHum();
	newHuman.points = newPoints;
	cout << "Введите место: ";
	cin >> newPlace;
	if (newPlace < 0) {
		cin.clear();
		cin.ignore(32767, '\n');
		cout << "Неверный ввод!" << endl;
		return addHum();
	}
	if (!correctInput())
		return addHum();
	newHuman.place = newPlace;
	return newHuman;
}

void addHash(Human key, Human* H, int amount) {
	int i = key.place % amount;
	if (H[i].place != -1) {
		while (H[i].place != -1) {
			int c = 1 + (key.place % (amount - 2)); //c = 1 + (key % (size(H) - 2)
			i -= c;
			if (i < 0) {
				i += amount;
			}
		}
	}
	H[i] = key;
}

void search(Human* H, int amount) {
	int key;
	cout << "\nВведите ключевое поле (место): ";
	cin >> key;
	if (!correctInput()) {
		cout << "\nВведите ключевое поле (место): ";
		cin >> key;
	}
	if (key < 1) {
		cout << "\nВведите ключевое поле (место): ";
		cin >> key;
	}
	cout << endl;
	int i = key % amount;
	while (H[i].place != -1) {
		if (H[i].place == key) {
			cout << "ФИО: " << H[i].FIO << endl << "Его(ее) очки: " << H[i].points << endl << "Его(ее) место: " << H[i].place << endl;
			break;
		}
		int c = 1 + (key % (amount-2));
		i -= c;
		if (i < 0) {
			i += amount;
		}
	}
	if (H[i].place == -1) {
		cout << "Такого места нет!\n";
	}
}

void deleteH(Human* H, int amount) {
	int key;
	cout << "\nВведите ключевое поле (место): ";
	cin >> key;
	if (!correctInput()) {
		cout << "\nВведите ключевое поле (место): ";
		cin >> key;
	}
	if (key < 1) {
		cout << "\nВведите ключевое поле (место): ";
		cin >> key;
	}
	cout << endl;
	int i = key % amount;
	while (H[i].place != -1) {
		if (H[i].place == key) {
			H[i].place = -1;
			break;
		}
		int c = 1 + (key % (amount - 2));
		i -= c;
		if (i < 0) {
			i += amount;
		}
	}
	cout << "Такого места теперь нет!\n\n";
}

Human* createH(int amount) {
	Human* newH = new Human[amount];
	for (int i = 0; i < amount; i++) {
		newH[i].FIO = NULL;
		newH[i].points = NULL;
		newH[i].place = -1;
	}
	return newH;
}

int main(){
	system("chcp 1251");
	int amount = 0, amountH = amount + 5;
	int oper;
	Human* tourney = new Human[amount];
	Human* H = new Human[amountH];
	H = createH(amountH);
	while (true) {
		cout << "Выберите операцию: 0 - Создать массив;\n"
			"1 - Добавить человека;\n"
			"!!!При вводе 0 и 1 хеш-таблица перепишется\n"
			"2 - Вывести массив;\n"
			"3 - Вывести хэш-таблицу;\n"
			"4 - Найти человека в хеш-таблице по ключу;\n"
			"5 - Удалить человека из хеш-таблицы по ключу;\n"
			"6 - Выйти" << endl;
		cin >> oper;
		if (!correctInput())
			continue;
		switch (oper) {
		case 0: {
			cout << "Введите количество участников турнира: ";
			if (tourney) {
				delete[] tourney;
			}
			cin >> amount;
			if (!correctInput()) {
				cout << "Введите количество участников турнира: ";
				cin >> amount;
			}
			tourney = new Human[amount];
			for (int i = 0; i < amount; i++) {
				tourney[i] = addHum();
			}
			cout << endl;
			amountH = amount + 5;
			delete[] H;
			H = createH(amountH);
			for (int i = 0; i < amount; i++) {
				addHash(tourney[i], H, amountH);
			}
			break;
		}
		case 1: {
			amount++;
			Human* newtourney = new Human[amount];
			for (int i = 0; i < (amount - 1); i++) {
				newtourney[i] = tourney[i];
			}
			newtourney[amount - 1] = addHum();
			delete[] tourney;
			tourney = newtourney;
			delete[] H;
			amountH++;
			H = createH(amountH);
			for (int i = 0; i < amount; i++) {
				addHash(tourney[i], H, amountH);
			}
			cout << endl;
			break;
		}
		case 2: {
			if (!tourney) {
				cout << "Не записаны участники турнира!\n";
				break;
			}
			for (int i = 0; i < amount; i++) {
				cout << "ФИО: " << tourney[i].FIO << endl << "Его(ее) очки: " << tourney[i].points << endl << "Его(ее) место: " << tourney[i].place << endl << endl;
			}
			break;
		}
		case 3: {
			if (!H) {
				cout << "Не записаны участники турнира!\n";
				break;
			}
			cout << endl << "Хеш таблица:" << endl;
			for (int i = 0; i < amountH; i++) {
				if (H[i].FIO) {
					cout << "H[" << i << "] = " << H[i].place << endl;
				}
			}
			cout << endl;
			break;
		}
		case 4:{
			search(H, amountH);
			cout << endl;
			break;
		}
		case 5: {
			deleteH(H, amountH);
			break;
		}
		case 6: return 0;
		default: cout << "Попробуй еще раз =)\n";
		}
	}
}