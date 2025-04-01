#include "Header.h"

int main() {
    setlocale(LC_ALL, "ru");

    ifstream fin("Set.txt");
    if (!fin.is_open()) {
        cout << "Ошибка открытия файла!" << endl;
        return 1;
    }

    string line;
    while (getline(fin, line)) {
        string noSpaces;
        for (char c : line) {
            if (c != ' ') noSpaces += c;
        }
        line = noSpaces;

        size_t equalPos = line.find('=');
        if (equalPos != string::npos) {
            line = line.substr(equalPos + 1);
        }

        if (!ValidateStructure(line)) {
            cout << "Ошибка: некорректное множество \"" << line << "\"." << endl;
            continue;
        }

        RemoveOuterBraces(line);

        vector<string> set;
        vector<vector<string>> boolean;
        vector<string> el_of_boolean;

        if (Add(set, line) || Check_Elements(set)) continue;

        cout << "Введённое множество: { ";
        for (size_t i = 0; i < set.size(); i++) {
            cout << set[i];
            if (i < set.size() - 1) cout << ", ";
        }
        cout << " }" << endl;

        Generate_Boolean(set, boolean, el_of_boolean, 0);

        cout << "Булеан заданного множества:\n";
        for (const auto& s : boolean) {
            PrintSubset(s);
            cout << endl;
        }
    }

    fin.close();
    return 0;
}
