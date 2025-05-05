#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

vector<string> parseSet(const string& input) {
    vector<string> elements;
    if (input.empty() || input.front() != '{' || input.back() != '}') {
        throw invalid_argument("Неверный формат множества");
    }

    string content = input.substr(1, input.size() - 2);
    size_t start = 0;
    int brace_level = 0;

    for (size_t i = 0; i < content.size(); ++i) {
        char c = content[i];
        if (c == '{' || c == '<') brace_level++;
        if (c == '}' || c == '>') brace_level--;

        if (c == ',' && brace_level == 0) {
            string element = content.substr(start, i - start);
            element.erase(0, element.find_first_not_of(" \t"));
            element.erase(element.find_last_not_of(" \t") + 1);
            if (!element.empty() || (element.empty() && i > start)) {
                elements.push_back(element);
            }
            start = i + 1;
        }
    }

    string last = content.substr(start);
    last.erase(0, last.find_first_not_of(" \t"));
    last.erase(last.find_last_not_of(" \t") + 1);
    if (!last.empty() || (last.empty() && content.size() > start)) {
        elements.push_back(last);
    }

    return elements;
}

void generatePermutations(vector<string>& elements, size_t level, vector<vector<string>>& result) {
    if (level == elements.size()) {
        result.push_back(elements);
        return;
    }

    for (size_t i = level; i < elements.size(); ++i) {
        swap(elements[level], elements[i]);
        generatePermutations(elements, level + 1, result);
        swap(elements[level], elements[i]);
    }
}

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    setlocale(LC_ALL, "RUS");
    cout << "Программа для генерации всех перестановок множества\n";

    while (true) {
        cout << "1 - Создать новое множество\n";
        cout << "2 - Выйти из программы\n";
        cout << "Выберите действие (1 или 2): ";

        int choice;
        cin >> choice;

        if (cin.fail()) {
            cout << "Ошибка: введите число 1 или 2\n\n";
            clearInputBuffer();
            continue;
        }

        clearInputBuffer();

        if (choice == 2) {
            break;
        }
        else if (choice != 1) {
            cout << "Неверный выбор. Пожалуйста, введите 1 или 2\n\n";
            continue;
        }

        cout << "Введите множество: ";
        string input;
        getline(cin, input);

        try {
            vector<string> elements = parseSet(input);
            vector<vector<string>> permutations;

            generatePermutations(elements, 0, permutations);

            cout << "\nВсе перестановки (" << permutations.size() << "):\n";
            for (const auto& perm : permutations) {
                cout << "{";
                for (size_t i = 0; i < perm.size(); ++i) {
                    cout << perm[i];
                    if (i != perm.size() - 1) cout << ", ";
                }
                cout << "}\n";
            }
            cout << endl;

        }
        catch (const exception& e) {
            cout << "Ошибка: " << e.what() << "\n\n";
        }
    }

    cout << "Программа завершена.\n";
    return 0;
}
