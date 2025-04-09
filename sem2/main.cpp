#include "SetOperations.h"


void showMenu() {
    cout << "\n=== Меню работы с множествами ===\n";
    cout << "1. Загрузить множества из файла\n";
    cout << "2. Показать загруженные множества\n";
    cout << "3. Выполнить объединение множеств\n";
    cout << "4. Очистить текущие множества\n";
    cout << "0. Выход\n";
    cout << "Выберите действие: ";
}

int main() {
    vector<string> sets;
    string result;
    int choice;

    do {
        showMenu();
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: {
                ifstream inputFile("/Users/matvejnevodnicenko/projects/C/C++/HashTable/HashTable/sets.txt");
                if (inputFile.is_open()) {
                    sets.clear();
                    readFile(sets, inputFile);
                    if (sets.empty()) {
                        cout << "Файл sets.txt пуст или содержит только пустые строки\n";
                    } else {
                        cout << "Загружено " << sets.size() << " множеств из файла sets.txt\n";
                    }
                } else {
                    cout << "Не удалось открыть файл sets.txt\n";
                }
                break;
            }
            case 2: {
                if (sets.empty()) {
                    cout << "Сначала загрузите множества из файла (пункт 1)\n";
                } else {
                    displaySets(sets);
                }
                break;
            }
            case 3: {
                if (sets.empty()) {
                    cout << "Сначала загрузите множества из файла (пункт 1)\n";
                } else {
                    unionSets(sets, result);
                }
                break;
            }
            case 4: {
                if (sets.empty()) {
                    cout << "Нет загруженных множеств для очистки\n";
                } else {
                    sets.clear();
                    result.clear();
                    cout << "Все множества очищены\n";
                }
                break;
            }
            case 0: {
                cout << "Программа завершена\n";
                break;
            }
            default: {
                cout << "Неверный выбор. Попробуйте снова\n";
                break;
            }
        }
    } while (choice != 0);

    return 0;
}
