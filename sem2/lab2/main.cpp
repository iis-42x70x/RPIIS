#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main() {
    setlocale(LC_ALL, "RU");
    string differenceResult, fileName;
    vector<string> sets;

    int kod;
    while (true) {
        cout << "Открыть файл - 1." << endl;
        cout << "Вывести множества - 2." << endl;
        cout << "Найти разность множеств - 3." << endl;
        cin >> kod;
        switch (kod) {
        case 1: {
            ifstream inputFile("C:\\Users\\user\\Desktop\\пиоивис2\\mn.txt.txt");
            if (inputFile.is_open()) {
                cout << "Файл открыт успешно!" << endl;
                cout << "--------------------" << endl;
                readFile(sets, inputFile);
            }
            else {
                cout << "Ошибка открытия файла." << endl;
            }
            break;
        }
        case 2:
            displaySets(sets);
            break;
        case 3:
            differenceSets(sets, differenceResult);
            exit(0);
            break;
        }
    }
    return 0;
}
