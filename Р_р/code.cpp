#include <iostream>
#include <vector>
using namespace std;
const int MAX_NODES = 100;
int main() {
	setlocale(LC_ALL, "RU");
	int nodes, edges;
	cout << "Введите количество вершин и рёбер: ";
	cin >> nodes >> edges;
	vector<vector<int>> incidenceMatrix(nodes, vector<int>(edges));
	cout << "Введите матрицу инцидентности: ";
	for (int i = 0; i < nodes; i++) {
		for (int j = 0; j < edges; j++) {
			cin >> incidenceMatrix[i][j];
		}
	}
	vector<int> edgeStatus(edges, true);
	vector<vector<int>> cycles;
	for (int i = 0; i < edges; i++) {
		if (edgeStatus[i]) {
			vector<int> cycle;
			int current = i;
			vector<bool> visited(edges, false);
			do {
				int node1 = -1, node2 = -1;
				for (int j = 0; j < nodes; j++) {
					if (incidenceMatrix[j][current] == 1) {
						if (node1 == -1) {
							node1 = j;
						}
						else {
							node2 = j;
							break;
						}
					}
				}
				cycle.push_back(current);
				visited[current] = true;
				edgeStatus[current] = false;
				for (int j = 0; j < edges; j++) {

					if (visited[j]) {
						continue;
					}
					if (incidenceMatrix[node1][j] == 1 || incidenceMatrix[node2][j] == 1) {
						current = j;
						break;
					}
				}
			} while (current != i);
			if (cycle.size() >= 4) {
				cycles.push_back(cycle);
			}
		}
	}
	cout << "Циклы:\n";
	for (int i = 0; i < cycles.size(); i++) {
		cout << "Цикл " << i + 1 << ": ";
		for (int j = 0; j < cycles[i].size(); j++) {
			cout << cycles[i][j] << " ";
		}
		cout << endl;
	}
	cout << "Хорды:\n";
	for (int i = 0; i < edges; i++) {
		if (edgeStatus[i]) {
			cout << i << " ";
		}
	}
	cout << endl;
	return 0;
}
