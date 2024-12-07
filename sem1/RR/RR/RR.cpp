#include <iostream>
#include <vector>
using namespace std;
void Sort(vector<int>& vec)
{
	vector <int> uniquevec;  // Вектор для хранения уникальных элементов
	for (int i = 0; i < vec.size(); i++)
	{
		bool isunique = true; // Переменная для проверки уникальности элемента
		for (int j = 0; j < uniquevec.size(); j++)
		{
			if (vec[i] == uniquevec[j])
			{
				isunique = false; // Элемент не уникален
				break; // Остановка выполнения цикла при выявлении дубликата
			}
		}
		// Если элемент уникальный, добавляем его в вектор уникальных элементов
		if (isunique)
		{
			uniquevec.push_back(vec[i]);
		}
	}
	vec.clear();
	vec = uniquevec;
}
void Sort2(vector<pair<int, int>>& A) // для удаления повторяющихся пар
{
	for (int i = 0; i < A.size(); i++)
	{
		for (int j = i + 1; j < A.size(); j++)
		{
			if (A[i] == A[j])
			{
				for (int k = j; k < A.size() - 1; k++)
				{
					A[k] = A[k + 1];
				}
				A.pop_back();
				j--;
			}
		}
	}
}
vector<pair<int, int>>Union2(vector<pair<int, int>> A, vector < pair<int, int>> B)
{
	vector<pair<int, int>> result;
	result = A;
	for (int i = 0; i < B.size(); i++)
	{
		result.emplace_back(B[i].first, B[i].second);
	}
	Sort2(result);
	return result;
}
vector<int> Union(vector<int> a, vector<int> b)
{
	vector<int> result;
	result = a;
	for (int i = 0; i < b.size(); i++) {
		result.push_back(b[i]);
	}
	Sort(result);
	return result;
}
int main() {
	setlocale(LC_ALL, "Russian");
	int ver1, ver2, edge1, edge2;
	cout << "Введите количество вершин первого графа: ";
	cin >> ver1;
	while (ver1 <= 0)
	{
		cout << "Невозможно задать граф из " << ver1 << " вершин, попробуйте еще раз." << endl << "Введите количество вершин первого графа: ";
		cin >> ver1;
	}
	cout << "Введите вершины: ";
	vector<int> vertices1;
	for (int i = 0; i < ver1; i++)
	{
		int a;
		cin >> a;
		vertices1.push_back(a);
	}
	int** graph1 = new int* [ver1];
	for (int i = 0; i < ver1; i++)
	{
		graph1[i] = new int[ver1];
	}
	cout << "Введите количество ребер: ";
	cin >> edge1;
	while (edge1 > (ver1 * (ver1 - 1)) / 2)
	{
		cout << "Слишком много ребер, попробуйте еще раз" <<endl;
		cin >> edge1;
	}
	cout << endl << "Введите ребра (пары вершин)" << endl;
	vector<pair<int, int>> edges1;
	edges1.reserve(edge1);
	for (int i = 0; i < edge1; i++)
	{
		int v1, v2;
		cin >> v1 >> v2;
		edges1.emplace_back(v1, v2);
	}
	for (int i = 0; i < ver1; i++)
	{
		for (int j = 0; j < ver1; j++)
		{
			graph1[i][j] = 0;
		}
	}
	for (int i = 0; i < edge1; ++i) {
		int u = -1, v = -1;

		// Находим индексы вершин для рёбер
		for (int j = 0; j < ver1; ++j) {
			if (vertices1[j] == edges1[i].first) u = j;
			if (vertices1[j] == edges1[i].second) v = j;
		}

		if (u != -1 && v != -1) {
			graph1[u][v] = 1;
			graph1[v][u] = 1;  // Для неориентированного графа
		}
	}
	cout << "Матрица смежности графа:" << endl;
	for (int i = 0; i < ver1; ++i) {
		for (int j = 0; j < ver1; ++j) {
			cout << graph1[i][j] << " ";
		}
		cout << endl;
	}
	cout << "Введите количество вершин второго графа: ";
	cin >> ver2;
	while (ver2 <= 0)
	{
		cout << "Невозможно задать граф из " << ver2 << " вершин, попробуйте еще раз." << endl << "Введите количество вершин второго графа: ";
		cin >> ver2;
	}
	cout << "Введите вершины: ";
	vector<int> vertices2;
	for (int i = 0; i < ver2; i++)
	{
		int a;
		cin >> a;
		vertices2.push_back(a);
	}
	int** graph2 = new int* [ver2];
	for (int i = 0; i < ver2; i++)
	{
		graph2[i] = new int[ver2];
	}
	cout << "Введите количество ребер: ";
	cin >> edge2;
	while (edge2 > (ver2 * (ver2 - 1)) / 2)
	{
		cout << "Слишком много ребер, попробуйте еще раз" << endl;
		cin >> edge2;
	}
	cout << endl << "Введите ребра (пары вершин)" << endl;
	vector<pair<int, int>> edges2;
	edges2.reserve(edge2);
	for (int i = 0; i < edge2; i++)
	{
		int v1, v2;
		cin >> v1 >> v2;
		edges2.emplace_back(v1, v2);
	}
	for (int i = 0; i < ver2; i++)
	{
		for (int j = 0; j < ver2; j++)
		{
			graph2[i][j] = 0;
		}
	}
	for (int i = 0; i < edge2; ++i) {
		int u = -1, v = -1;

		// Находим индексы вершин для рёбер
		for (int j = 0; j < ver2; ++j) {
			if (vertices2[j] == edges2[i].first) u = j;
			if (vertices2[j] == edges2[i].second) v = j;
		}

		if (u != -1 && v != -1) {
			graph2[u][v] = 1;
			graph2[v][u] = 1;  // Для неориентированного графа
		}
	}
	cout << "Матрица смежности графа:" << endl;
	for (int i = 0; i < ver2; ++i) {
		for (int j = 0; j < ver2; ++j) {
			cout << graph2[i][j] << " ";
		}
		cout << endl;
	}
	cout << "Объединение графов: " << endl;
	vector <int> C;
	C = Union(vertices1,vertices2);
	for (int i = 0; i < C.size(); i++)
	{
		cout << C[i] << " ";
	}
	cout << endl;
	vector<pair<int, int>>forunion;
	forunion = Union2(edges1, edges2);
	for (int i = 0; i < forunion.size(); i++)
	{
		cout << forunion[i].first << " " << forunion[i].second << endl;
	}
	int** graph3 = new int* [C.size()];
	for (int i = 0; i < C.size(); i++)
	{
		graph3[i] = new int[C.size()];
	}
	for (int i = 0; i < C.size(); i++)
	{
		for (int j = 0; j < C.size(); j++)
		{
			graph3[i][j] = 0;
		}
	}
	for (int i = 0; i < forunion.size(); ++i) {
		int u = -1, v = -1;

		// Находим индексы вершин для рёбер
		for (int j = 0; j < C.size(); ++j) {
			if (C[j] == forunion[i].first) u = j;
			if (C[j] == forunion[i].second) v = j;
		}

		if (u != -1 && v != -1) {
			graph3[u][v] = 1;
			graph3[v][u] = 1;  // Для неориентированного графа
		}
	}
	cout << "Матрица смежности графа:" << endl;
	for (int i = 0; i < C.size(); ++i) {
		for (int j = 0; j < C.size(); ++j) {
			cout << graph3[i][j] << " ";
		}
		cout << endl;
	}
	return 0;
}
