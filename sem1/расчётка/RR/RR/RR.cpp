#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <limits>
using namespace std;

int main() {
    setlocale(LC_ALL, "ru");

    cout << "Введите количество вершин: ";

    int numberOfVertices;
    cin >> numberOfVertices;

    vector<vector<int>> adjacencyList(numberOfVertices);
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < numberOfVertices; ++i) {
        cout << "Вершина " << i + 1 << ": ";
        string line;
        getline(cin, line);
        line.erase(0, line.find(':') + 1);
        stringstream s(line);
        int vertexNumber;
        while (s >> vertexNumber) {
            adjacencyList[i].push_back(vertexNumber);
        }
    }

    vector<int> incomingEdges(numberOfVertices, 0);
    vector<int> outgoingEdges(numberOfVertices, 0);

    for (int i = 0; i < numberOfVertices; i++) {
        outgoingEdges[i] = adjacencyList[i].size();
        for (int j = 0; j < adjacencyList[i].size(); j++) {
            int toVertex = adjacencyList[i][j];
            int toIdx = toVertex - 1;
            incomingEdges[toIdx]++;
        }

    }

    cout << "\nОкружение орграфа:\n";
    for (int i = 0; i < numberOfVertices; ++i) {
        cout << "Вершина " << i + 1
            << ": входящих = " << incomingEdges[i]
            << ", исходящих = " << outgoingEdges[i] << "\n";
    }

    return 0;
}