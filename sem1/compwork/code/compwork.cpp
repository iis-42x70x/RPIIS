#include<fstream>
#include <iostream>
#include <vector>

using namespace std;

//функция для создания матрицы инцендентности для пути в графе
vector<vector<int>> make_matrix(vector<vector<int>> matrix, int rows, int cols, vector<int> way_edge) {
	vector<vector<int>> new_matrix(rows, vector<int>(cols));
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			new_matrix[i][j] = matrix[i][way_edge[j]];
		}
	}


	return new_matrix;
}

//обход в глубину
void dfs_realize(vector<vector<int>> smeg_list, int start, vector<int>& visited) {
	visited[start] = 1;

	for (int i = 0; i < smeg_list[start].size(); i++) {
		if(!visited[smeg_list[start][i]])
		dfs_realize(smeg_list, smeg_list[start][i], visited);
	}
}

//функция для соединения путей
void insert_way(vector<int>& way_edge, vector<int>& way_start, vector<int> miniway_edge, vector<int> miniway_start) {
	miniway_start.push_back(miniway_start[0]);
	for (int i = 0; i < way_start.size(); i++) {
		if (way_start[i] == miniway_start[0]) {
			for (int j = 0; j < miniway_edge.size(); j++) {
				way_start.insert(way_start.begin() + i, miniway_start[j + 1]);
				way_edge.insert(way_edge.begin() + i, miniway_edge[j]);
			}
			break;
		}
	}
}

//проверка существования цикла эйлера
bool check_graph(vector<vector<int>> matrix) {
	int rows = matrix.size();
	int cols = matrix[0].size();
	//проверка четности вершин
	for (int i = 0; i < rows; i++) {
		int counter = 0;
		for (int j = 0; j < cols; j++) {
			counter += matrix[i][j];
		}
		if (counter % 2 != 0)
			return false;
	}

	//переводим матрицу инцендентности в список смежности
	vector<vector<int>> smeg_list(rows);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (matrix[i][j] == 1) {
				for (int p = 0; p < rows; p++) {
					if (p != i && matrix[p][j] == 1) {
						smeg_list[i].push_back(p);
						
					}
				}
			}
		}
	}

	//ищем стартовую вершину для обхода в ширину
	int start = -1;
	for (int i = 0; i < rows; i++) {
		if (smeg_list[i].size() != 0) {
			start = i;
			break;
		}
	}
	// если в графе нет ребер, то он несвязный
	if (start == -1)
		return false;

	vector<int> visited(rows);
	dfs_realize(smeg_list, start, visited);

	for (int i = 0; i < rows; i++) {
		if (!visited[i])
			return false;
	}

	return true;
}

//алгоритм поиска пути
void find_part_way(vector<vector<int>> matrix, int rows, int cols, int start, int edge, vector<int>& visited, vector<int>& way_edge, vector<int>& way_start) {
	way_edge.push_back(edge);
	way_start.push_back(start);
	

	for (int i = 0; i < rows; i++) {
		if (i != start && matrix[i][edge]) {
			visited[edge] = 1;
			for (int j = 0; j < cols; j++) {
				if (!visited[j] && j != edge && matrix[i][j]) {
					find_part_way(matrix, rows, cols, i, j, visited, way_edge, way_start);
					break;
				}
			}
			break;
		}
	}
}

//функция поиска цикла эйлера
void find_way(vector<vector<int>> matrix, vector<int>& way_edge, vector<int>& way_start) {
	
	if (!check_graph(matrix)) {
		cout << "Цикл Эйлера не существует" << endl;
	}
	else {
		int start = 0;
		int edge = -1;
		int rows = matrix.size();
		int cols = matrix[0].size();
		vector<int> visited(cols);
		vector<int> way;
		//ищем первую вершину и ребро
		for (int i = 0; i < cols; i++) {
			if (matrix[0][i] == 1) {
				edge = i;
				break;
			}
		}
		find_part_way(matrix, rows, cols, start, edge, visited, way_edge, way_start);
		way_start.push_back(start);

		for (int i = 0; i < cols; i++) {
			if (!visited[i]) {
				vector<int> miniway_edge;
				vector<int> miniway_start;
				for (int j = 0; j < rows; j++) {
					if (matrix[j][i]) {
						find_part_way(matrix, rows, cols, j, i, visited, miniway_edge, miniway_start);
						insert_way(way_edge, way_start, miniway_edge, miniway_start);
						break;
					}
				}
			}
		}
		matrix = make_matrix(matrix, rows, cols, way_edge);
		cout << "Edge: ";
		for (int i = 0; i < way_edge.size(); i++) {
			cout << way_edge[i] << " ";
		}
		cout << endl << "Start: ";
		for (int i = 0; i < way_start.size(); i++) {
			cout << way_start[i] << " ";
		}
		cout << endl;
		cout << "Matrix:" << endl;
		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				cout << matrix[i][j] << " ";
			}
			cout << endl;
		}
	}
}

//функция для пользовательского ввода
void user_func() {
	vector<int> way_edge;
	vector<int> way_start;
	int rows, cols;
	cout << "Введите количество вершин графа: ";
	cin >> rows;
	cout << "Введите колитчество ребер графа: ";
	cin >> cols;
	vector<vector<int>> matrix_1(rows, vector<int>(cols));
	cout << "Введите матрицу инцендентности для графа:" << endl;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			cin >> matrix_1[i][j];
		}
		cout << endl;
	}
	find_way(matrix_1, way_edge, way_start);
}

int main() {
	setlocale(LC_ALL, "ru");
	

	cout << "Ввод данных: 1 - с клавиатуры, 2 - из файла: ";
	int n;
	cin >> n;
	switch (n) {
	case 1: {
		user_func();
		break;
	}
	case 2: {
		ifstream file("test.txt");
		if (!file.is_open()) {
			cout << "Ошибка при чтении файла" << endl;
		}
		for (int a = 1; a < 6; a++) {
			vector<int> way_edge;
			vector<int> way_start;
			cout << "Test " << a << ":" << endl;
			int rows, cols;
			file >> rows;
			file >> cols;
			vector<vector<int>> matrix(rows, vector<int>(cols));
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < cols; j++) {
					file >> matrix[i][j];
				}
			}
			find_way(matrix, way_edge, way_start);
			cout << endl;
		}
		break;
	}
	default:
		cout << "Выход" << endl;
		break;
	}

	return 0;
}