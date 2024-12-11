#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

int shortestCycle(vector<vector<int>>& adjMatrix, int numberofsize) {
    int minCycle = numeric_limits<int>::max();

    for (int start = 0; start < numberofsize; start++) {
        vector<int> distance(numberofsize, -1);
        queue<int> bfsQueue;

        bfsQueue.push(start);
        distance[start] = 0;

        while (!bfsQueue.empty()) {
            int cur = bfsQueue.front();
            bfsQueue.pop();

            for (int neighbor = 0; neighbor < numberofsize; neighbor++) {
                if (adjMatrix[cur][neighbor] == 1) {
                    if (distance[neighbor] == -1) {
                        distance[neighbor] = distance[cur] + 1;
                        bfsQueue.push(neighbor);
                    } else if (neighbor == start) {
                        minCycle = min(minCycle, distance[cur] + 1);
                    }
                }
            }
        }
    }
    return (minCycle == numeric_limits<int>::max()) ? -1 : minCycle;
}

int main() {
    setlocale(LC_ALL, "ru");

    string fileName;
    cout << "Введите имя файла: ";
    cin >> fileName;

    ifstream inputFile(fileName);
    if (!inputFile.is_open()) {
        cerr << "Ошибка: не удалось открыть файл." << endl;
        return 1;
    }

    ofstream outputFile("obhvat.txt");
    if (!outputFile.is_open()) {
        cerr << "Ошибка: не удалось создать выходной файл." << endl;
        return 1;
    }

    int numberof_usl, numberof_rebr;
    inputFile >> numberof_usl >> numberof_rebr;

    vector<vector<int>> adjMatrix(numberof_usl, vector<int>(numberof_usl, 0));

    for (int i = 0; i < numberof_rebr; i++) {
        int usl, s_usl;
        inputFile >> usl >> s_usl;
        usl--, s_usl--;
        adjMatrix[usl][s_usl] = 1;
    }

    inputFile.close();

    int cycleLength = shortestCycle(adjMatrix, numberof_usl);
    if (cycleLength == -1) {
        outputFile << "Обхват графа: бесконечность" << endl;
    } else {
        outputFile << "Обхват графа: " << cycleLength << endl;
    }

    outputFile.close();
    return 0;
}
