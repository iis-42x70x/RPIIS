#include <iostream>
#include <string>
#include <vector>
#include "SetParser.h"
#include <gtest/gtest.h>

using namespace std;

int main(int argc, char** argv) {
    setlocale(LC_ALL, "Russian");
    cout << "Выберите режим:\n1. Ручной ввод\n2. Запустить тесты\n";

    int choice;
    cin >> choice;
    cin.ignore(); 

    if (choice == 1) {
        cout << "Введите количество множеств: ";
        int count;
        cin >> count;
        cin.ignore();

        vector<vector<string>> sets;
        for (int i = 0; i < count; ++i) {
            cout << "Введите множество " << i + 1 << " в формате {a,b,c}: ";
            string input;
            getline(cin, input);
            auto parsed = string_to_vector(input);
            if (parsed.empty()) {
                cerr << "Множество " << i + 1 << " некорректно и будет пропущено.\n";
                continue;
            }
            sets.push_back(parsed);         
        }

        auto result = cartesianProduct(sets);
        cout << "Декартово произведение:\n";
        for (const auto& tuple : result) {
            cout << "< ";
            for (size_t i = 0; i < tuple.size(); ++i) {
                cout << tuple[i];
                if (i < tuple.size() - 1)
                    cout << ", ";
            }
            cout << " >\n";
        }

    }
    else if (choice == 2) {
        ::testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
    }
    else {
        cout << "Неверный выбор.\n";
    }

    return 0;
}
