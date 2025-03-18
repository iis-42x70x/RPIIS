#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "C:\Users\Анастасия\source\repos\пиоивис\лаба2пиоивис\lab2.h";
using namespace std;

int main() {
	setlocale(LC_ALL, "RU");
	string unionResult, fileName;
	vector<string> sets;


	int kod;
	while (true) {
		cout << "Открыть файл - 1" << endl;
		cout << "Вывести множества - 2" << endl;
		cout << "Объединить множества - 3" << endl;
		cin >> kod;
		switch (kod) {
		case 1: {
			ifstream inputFile("mn.txt");
			if (inputFile.is_open()) {
				cout << "Файл открыт успешно!!!" << endl;
				cout << "----------------------" << endl;
				cout << "Вывести множества - 2" << endl;
				cout << "Объединить множества - 3" << endl;
				readFile(sets, inputFile);
			}
			else {
				cout << "Ошибка открытия файла " << endl;
			}
			break;
		}
		case 2:
			displaySets(sets);
			break;
		case 3:
			unionSets(sets, unionResult);
			exit(0);
			break;
		}
	}
	return 0;
}
