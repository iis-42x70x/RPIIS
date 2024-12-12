#include <iostream>
#include <vector>

using namespace std;

void dfs(int v, const vector<vector<int>>& g, vector<bool>& visited) {
	visited[v] = true;
	for (int u = 0; u < g.size(); u++) {
		if (g[v][u] == 1 && !visited[u]) {
			dfs(u, g, visited);
		}
	}
}

vector<vector<int>> transposed(const vector<vector<int>>& g) {
	int n = g.size();
	vector<vector<int>> transposed(n, vector<int>(n, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (g[i][j] == 1) {
				transposed[j][i] = 1;
			}
		}
	}
	return transposed;
}

bool isStronglyConnected(const vector<vector<int>>& g) {
	int n = g.size();

	vector<bool> visited(n, false);
	dfs(0, g, visited);

	for (int i = 0; i < n; i++) {
		if (!visited[i]) {
			return false;
		}
	}
	vector<vector<int>> transposed_g = transposed(g);
	fill(visited.begin(), visited.end(), false);
	dfs(0, transposed_g, visited);

	for (int i = 0; i < n; i++) {
		if (!visited[i]) {
			return false;
		}
	}
	return true;
}

int main() {
	system("chcp 1251");
	int n, m;
	cout << "Введите колличество вершин :\n";
	cin >> n;
	cout << "Введите колличество ориентированных рёбер :\n";
	cin >> m;

	vector<vector<int>> graf(n, vector<int>(n, 0));  // вектор векторов по сути матрица 
	                                                 //смежности но только с ноликами
	cout << "ВВедите рёбра (вершина_1 вершина_2) :\n";
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		graf[u-1][v-1] = 1;
	}
	if (isStronglyConnected(graf) == true) {
		cout << "Ваш граф сильно - связный";
	}
	else {
		cout << "Ваш граф не сильно - связный";
	}
	return 0;
}
