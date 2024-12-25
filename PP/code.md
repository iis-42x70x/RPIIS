
```C++
#include <iostream> 
#include <vector> 
#include <queue> 
#include <climits> 
#include <fstream> 
using namespace std;

struct Edge {
    int to;        // информация о конечной вершине *to* и весе *weight* ребра
    int weight;
};

int findEccentricity(vector<vector<Edge>>& adjList, int start, int n) {
    vector<int> dist(n, INT_MAX);
    dist[start] = 0;

    queue<int> q;
    q.push(start);

    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        for (const Edge& edge : adjList[cur]) {
            int neighbor = edge.to;
            int weight = edge.weight;

            if (dist[neighbor] > dist[cur] + weight) {
                dist[neighbor] = dist[cur] + weight;
                q.push(neighbor);
            }
        }
    }

    int maxDist = 0;
    for (int i = 0; i < n; ++i) {
        maxDist = max(maxDist, dist[i]);
    }

    return maxDist;
}

int findGraphRadius(vector<vector<Edge>>& adjList, int n) {
    int minEccentricity = INT_MAX;

    for (int i = 0; i < n; ++i) {
        int eccentricity = findEccentricity(adjList, i, n);
        minEccentricity = min(minEccentricity, eccentricity);
    }

    return (minEccentricity == INT_MAX) ? -1 : minEccentricity;
}

void run_testcase(const char* file) {
    ifstream input(file);
    if (!input.is_open()) {
        cerr << "Nevozmozhno otkryt fayl: " << file << endl;
        return;
    }

    int n, m;
    input >> n >> m;

    vector<vector<Edge>> adjList(n);

    cout << "Spisok smezhnosti: " << endl;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        input >> u >> v >> w;
        u--, v--;

        Edge edge_to_v = { v, w };
        Edge edge_to_u = { u, w };

        adjList[u].push_back(edge_to_v);
        adjList[v].push_back(edge_to_u);
        cout << u + 1 << "<->" << v + 1 << " " << w << endl;
    }

    input.close();

    int graphRadius = findGraphRadius(adjList, n);
    if (graphRadius == -1) {
        cout << "Graf nesvyaznyy ili pustoy " << endl;
    }
    else {
        cout << "Radius grafa dlya fayla " << file << ": " << graphRadius << endl;
    }
    cout << "--------------------------------------------------\n";
}

int main() {
    setlocale(LC_ALL, "ru");

    int choice;
    do {
        cout << "Выберите граф для анализа:\n";
        cout << "1. graph1.txt\n";
        cout << "2. graph2.txt\n";
        cout << "3. graph3.txt\n";
        cout << "4. graph4.txt\n";
        cout << "5. graph5.txt\n";
        cout << "0. Выход\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        switch (choice) {
        case 1:
            run_testcase("graph1.txt");
            break;
        case 2:
            run_testcase("graph2.txt");
            break;
        case 3:
            run_testcase("graph3.txt");
            break;
        case 4:
            run_testcase("graph4.txt");
            break;
        case 5:
            run_testcase("graph5.txt");
            break;
        case 0:
            cout << "Выход из программы." << endl;
            break;
        default:
            cout << "Неверный выбор. Пожалуйста, попробуйте снова." << endl;
        }
    } while (choice != 0);

    return 0;
}
```
