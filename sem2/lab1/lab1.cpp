#include <iostream>
#include <locale>
using namespace std;
struct Spis {
	int info;
	Spis* next;
};
Spis* InSpis(Spis* p, int in) {
	Spis* t = new Spis;
	t->info = in;
	t->next = p;
	return t;
}
void View(Spis* p) {
	Spis* t = p;
	while (t != NULL) {
		cout <<t->info << " ";
		t = t->next;
	}
	cout << endl;
}
void Sort_info(Spis* p) {
	Spis* t = NULL, * t1;
	int r;
	do {
		for (t1 = p; t1->next != t; t1 = t1->next)
			if (t1->info > t1->next->info) {
				r = t1->info;
				t1->info = t1->next->info;
				t1->next->info = r;
			}
		t = t1;
	} while (p->next != t);
}
void Search(Spis* p,int elem) {
	Spis* t = p;
	while (t != NULL) {
		if (t->info == elem) {
			cout << "Элемент найден"<< endl;
			return;
		}
		t = t->next;
	}
	cout << "Элемент не найден" << endl;
}
void Del_Elem(Spis** p,int elem) {
	Spis* t = *p;
	Spis* prev = NULL;
	while (t != NULL) {
		if (t->info == elem) {
			if (prev == NULL) {
				*p = t->next;
				delete t;
				t = *p;
			}
			else {
				prev->next = t->next;
				delete t;
				t = prev->next;
			}
		}
		else {
			prev = t;
			t = t->next;
		}
	}
}
void Del_All(Spis** p) {
	Spis* t;
	while (*p != NULL) {
		t = *p;
		*p = (*p)->next;
		delete t;
	}
}
bool Contains(Spis* p, int elem) {
	Spis* t = p;
	while (t != nullptr) {
		if (t->info == elem) {
			return true;
		}
		t = t->next;
	}
	return false;
}
void Union(Spis* a, Spis* b) {
	Spis* t1=a;
	Spis* t2=b;
	Spis* res = NULL;
	while (t1 != NULL) {
		if (!Contains(res,t1->info)) {
			res=InSpis(res, t1->info);
		}
		t1 = t1->next;
	}
	while (t2 != NULL) {
			if (!Contains(res, t2->info)) {
				res = InSpis(res, t2->info);
			}
			t2 = t2->next;
	}
	cout << "Список объединения: ";
	View(res);
	Del_All(&res);
}
void Intersection(Spis* a, Spis* b) {
	Spis* t1 = a;
	Spis* res1 = NULL;
	while (t1 != NULL) {
		Spis* t2 = b;
		while (t2 != NULL) {
			if (t1->info == t2->info && !Contains(res1, t1->info)) {
				res1 = InSpis(res1, t1->info);
				break;
			}
			t2 = t2->next;
		}
		t1 = t1->next;
	}
	cout << "Список пересечения: ";
	View(res1);
	Del_All(&res1);
}
void menu() {
	cout << "Вставить элемент в список-1" << endl;
	cout << "Удалить элемент из списока-2" << endl;
	cout << "Отсортировать список-3" << endl;
	cout << "Найти элемент в списке-4" << endl;
	cout << "Объединение списков-5" << endl;
	cout << "Пересечение списков-6" << endl;
	cout << "Очистить память-7" << endl;
	cout << "Вывести списки-8" << endl;
	cout << "Выход-0" << endl;
	cout << "Выберите пункт: " << endl;
}
int main()
{
	setlocale(LC_ALL, "ru");
	int elem1, n1, elem2, n2, elem, choice, elem3;
	Spis* Spis1 = NULL;
	Spis* Spis2 = NULL;
	cout << "Введите количество элементов первого списка:";
	cin >> n1;
	cout << "Введите элементы первого списка:" << endl;;
	for (int i = 0; i < n1; i++) {
		cin >> elem1;
		Spis1 = InSpis(Spis1, elem1);
	}
	cout << "Введите количество элементов второго списка:";
	cin >> n2;
	cout << "Введите элементы второго списка:" << endl;;
	for (int i = 0; i < n2; i++) {
		cin >> elem2;
		Spis2 = InSpis(Spis2, elem2);
	}
	do {
		menu();
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "Какой элемент хотите вставить в список?" << endl;
			cin >> elem;
			int N_Spis;
			cout << "В какой список вставить элемент?В первый-1,во второй-2" << endl;
			cin >> N_Spis;
			switch (N_Spis) {
			case 1:
				Spis1 = InSpis(Spis1, elem);
				View(Spis1);
				break;
			case 2:
				Spis2 = InSpis(Spis2, elem);
				View(Spis2);
				break;
			}
			break;
		case 2:
			cout << "Какой элемент хотите удалить из списка?" << endl;
			cin >> elem3;
			int N_Spis2;
			cout << "В каком списоке удалить элемент?В первом-1,во втором-2" << endl;
			cin >> N_Spis2;
			switch (N_Spis2) {
			case 1:
				Del_Elem(&Spis1, elem3);
				break;
			case 2:
				Del_Elem(&Spis2, elem3);
				break;
			}
			break;
		case 3:
			cout << "Какой список хотите отсортировать?Первый-1,второй-2" << endl;
			int N_Spis3;
			cin >> N_Spis3;
			switch (N_Spis3) {
			case 1:
				Sort_info(Spis1);
				break;
			case 2:
				Sort_info(Spis2);
				break;
			}
			break;
		case 4:
			cout << "Какой элемент хотите найти в списке?" << endl;
			int elem4;
			cin >> elem4;
			cout << "В каком списке искать?В первом-1,во втором-2" << endl;
			int N_Spis4;
			cin >> N_Spis4;
			switch (N_Spis4) {
			case 1:
				Search(Spis1, elem4);
				break;
			case 2:
				Search(Spis2, elem4);
				break;
			}
			break;
		case 5:
			Union(Spis1, Spis2);
			break;
		case 6:
			Intersection(Spis1, Spis2);
			break;
		case 7:
			Del_All(&Spis1);
			Del_All(&Spis2);
			break;
		case 8:
			cout << "Первый список: ";
			View(Spis1);
			cout << "Второй список: ";
			View(Spis2);
			break;
		}
	} while (choice != 0);
	Del_All(&Spis1);
	Del_All(&Spis2);
	return 0;
  }