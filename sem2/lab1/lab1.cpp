#include<iostream>
using namespace std;
void CreatTree(double*, double*, int, int, int);
void SeeTree(double*, int, int, int, int);
double Sum(double*, int, int, int, int, int);
void Update(double*, int, int, int, int, int, double);
void Test1();
void Test2();
void Test3();
void Test4();
void Test5();
int main() {
	setlocale(LC_ALL, "RU");
	int choice, choice1;
	double* mas, * tree;
	do {
		cout << "1.Ручной ввод\n2.Тесты\n3.Выход из программы\nВаш выбор: ";
		cin >> choice;
		switch (choice) {
		case 1:
			int size, l, r;
			cout << "Введите размер дерева: ";
			cin >> size;
			if (size <= 0) {
				cout << "Ошибка: размер дерева должен быть положителен" << endl;
				break;
			}
			mas = new double[size];
			tree = new double[4 * size + 1];
			for (int i = 0; i < size; i++) {
				cout << "Введите " << i + 1 << " элемент дерева: ";
				cin >> mas[i];
			}
			CreatTree(tree, mas, 1, 0, size - 1);
			do {
				cout << "1.Просмотр дерева\n2.Запрос суммы\n3.Запрос обновления\n4.Выход из выбора\nВаш выбор: ";
				cin >> choice1;
				switch (choice1) {
				case 1:
					SeeTree(tree, 1, 0, size - 1, 0);
					break;
				case 2:
					cout << "Введите левую и правую границы запроса суммы\nЛевая: ";
					cin >> l;
					cout << "Правая: ";
					cin >> r;
					if (l<0 || r>size - 1) {
						cout << "Ошибка: ваши границы не должны выходить за рамки дерева" << endl;
					}
					else {
						cout << "Сумма на отрезке [" << l << "," << r << "]: " << Sum(tree, 1, 0, size - 1, l, r) << endl;
					}
					break;
				case 3:
					cout << "Введите левую и правую границы запроса обновления\nЛевая: ";
					cin >> l;
					cout << "Правая: ";
					cin >> r;
					if (l<0 || r>size - 1) {
						cout << "Ошибка: ваши границы не должны выходить за рамки дерева" << endl;
					}
					else {
						int zn;
						cout << "Введите новое значение для элементов отрезка: ";
						cin >> zn;
						Update(tree, 1, 0, size - 1, l, r, zn);
					}
					break;
				case 4:
					cout << "Выход из выбора\n";
					break;
				default:
					cout << "Неверный выбор\nПопробуйте снова\n";
				}
			} while (choice1 != 4);
			delete[] mas;
			delete[] tree;
			break;
		case 2:
			do {
				cout << "1.Тест 1\n2.Тест 2\n3.Тест 3\n4.Тест 4\n5.Тест 5\n6.Выход из выбора\nВаш выбор: ";
				cin >> choice1;
				switch (choice1) {
				case 1:
					Test1();
					break;
				case 2:
					Test2();
					break;
				case 3:
					Test3();
					break;
				case 4:
					Test4();
					break;
				case 5:
					Test5();
					break;
				case 6:
					cout << "Выход из выбора\n";
					break;
				default:
					cout << "Неверный выбор\nПопробуйте снова\n";
				}
			} while (choice1!=6);
			break;
			case 3: 
				cout << "Выход из программы";
				return 0;
			default:
				cout << "Неверный выбор\nПопробуйте снова\n";
		}
	} while (choice != 3);
	return 0;
}
void CreatTree(double* tree, double* mas, int i, int l, int r) {
	if (l == r) {
		tree[i] = mas[l];
	}
	else {
		int m = (l + r) / 2;
		CreatTree(tree, mas, 2 * i, l, m);
		CreatTree(tree, mas, 2 * i + 1, m + 1, r);
		tree[i] = tree[2 * i] + tree[2 * i + 1];
	}
}
void SeeTree(double* tree, int i, int l, int r, int level) {
	if (l == r) {
		for (int j = 0; j < level; j++) {
			cout << "    ";
		}
		cout << tree[i] << endl;
		return;
	}
	else {
		int m = (l + r) / 2;
		SeeTree(tree, 2 * i + 1, m + 1, r, level + 1);
		for (int j = 0; j < level;j++) {
			cout << "    ";
		}
		cout << tree[i] << endl;
		SeeTree(tree, 2 * i, l, m, level + 1);

	}
}
double Sum(double* tree, int i, int l, int r, int s_l, int s_r) {
	if (s_l > s_r) {
		return 0;
	}
	if (l == s_l && r == s_r) {
		return tree[i];
	}
	int m = (r + l) / 2;
	return Sum(tree, 2 * i, l, m, s_l, min(m, s_r)) + Sum(tree, 2 * i + 1, m + 1, r, max(m+1, s_l), s_r);
}
void Update(double* tree, int i, int l, int r, int s_l, int s_r, double zn) {
	if (s_l > s_r) {
		return;
	}
	if (l == r) {
		tree[i] = zn;
	}
	else {
		int m = (r + l) / 2;
		Update(tree, 2 * i, l, m, s_l, min(m, s_r), zn);
		Update(tree, 2 * i + 1, m + 1, r, max(m + 1, s_l), s_r, zn);
		tree[i] = tree[2 * i] + tree[2 * i + 1];
	}
}
void Test1() {
	cout << "Тест 1: Проверка суммы на отрезке" << endl;
	int size = 5;
	double mas[] = { 1, 3, 5, 7, 9 };
	cout << "Массив: { 1, 3, 5, 7, 9 }" << endl;
	double* tree = new double[4 * size + 1];
	CreatTree(tree, mas, 1, 0, size - 1);
	double result = Sum(tree, 1, 0, size - 1, 1, 3);
	cout << "Сумма на отрезке [1, 3]: " << result << " (ожидается: 15)" << endl;
	if (result == 15) {
		cout << "Успешно" << endl;
	}
	else {
		cout << "Фиаско" << endl;
	}
	delete[] tree;
}
void Test2() {
	cout << "Тест 2: Проверка обновления отрезка и суммы" << endl;
	int size = 5;
	double mas[] = { 1, 3, 5, 7, 9 };
	cout << "Массив: { 1, 3, 5, 7, 9 }" << endl;
	double* tree = new double[4 * size + 1];
	CreatTree(tree, mas, 1, 0, size - 1);
	cout << "Обновляем элементы на отрезке [1, 3] на значение 2" << endl;
	Update(tree, 1, 0, size - 1, 1, 3, 2);
	double result = Sum(tree, 1, 0, size - 1, 1, 3);
	cout << "Сумма на отрезке [1, 3] после обновления: " << result << " (ожидается: 6)" << endl;
	if (result == 6) {
		cout << "Успешно" << endl;
	}
	else {
		cout << "Фиаско" << endl;
	}
	delete[] tree;
}
void Test3() {
	cout << "Тест 3: Проверка обновления одного элемента" << endl;
	int size = 5;
	double mas[] = { 1, 3, 5, 7, 9 };
	cout << "Массив: { 1, 3, 5, 7, 9 }" << endl;
	double* tree = new double[4 * size + 1];
	CreatTree(tree, mas, 1, 0, size - 1);
	cout << "Обновляем элемент на позиции 2 (значение 5) на значение 10" << endl;
	Update(tree, 1, 0, size - 1, 2, 2, 10);
	double result = Sum(tree, 1, 0, size - 1, 0, 4);
	cout << "Сумма на отрезке [0, 4] после обновления: " << result << " (ожидается: 30)" << endl;
	if (result == 30) {
		cout << "Успешно" << endl;
	}
	else {
		cout << "Фиаско" << endl;
	}
	delete[] tree;
}
void Test4() {
	cout << "Тест 4: Проверка суммы на всем массиве" << endl;
	int size = 5;
	double mas[] = { 1, 3, 5, 7, 9 };
	cout << "Массив: { 1, 3, 5, 7, 9 }" << endl;
	double* tree = new double[4 * size + 1];
	CreatTree(tree, mas, 1, 0, size - 1);
	cout << "Проверка суммы на всем массиве [0, 4]" << endl;
	double result = Sum(tree, 1, 0, size - 1, 0, 4);
	cout << "Сумма на отрезке [0, 4]: " << result << " (ожидается: 25)" << endl;
	if (result == 25) {
		cout << "Успешно" << endl;
	}
	else {
		cout << "Фиаско" << endl;
	}
	delete[] tree;
}
void Test5() {
	cout << "Тест 5: Проверка обновления и суммы на пустом отрезке" << endl;
	int size = 5;
	double mas[] = { 1, 3, 5, 7, 9 };
	double* tree = new double[4 * size + 1];
	cout << "Массив: { 1, 3, 5, 7, 9 }" << endl;
	CreatTree(tree, mas, 1, 0, size - 1);
	cout << "Проверка суммы на пустом отрезке [3, 2]" << endl;
	double result = Sum(tree, 1, 0, size - 1, 3, 2);
	cout << "Сумма на отрезке [3, 2]: " << result << " (ожидается: 0)" << endl;
	if (result == 0) {
		cout << "Успешно" << endl;
	}
	else {
		cout << "Фиаско" << endl;
	}
	delete[] tree;
}
