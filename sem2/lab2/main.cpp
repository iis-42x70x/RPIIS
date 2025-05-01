#include "pch.h"

using namespace std;


int main(int argc, char** argv) {
    setlocale(LC_ALL, "");
    string str = ReadFromFile();
    if (str.empty()) {
        cout << "Не удалось прочитать файл input.txt или файл пуст.\n";
        return 1;
    }
    cout << "Введенное множество: " << str << endl;
    str = NotSpace(str);
    if (!CheckStr(str)) return 0;
    int pos = 0;
    SetElement el = ParsingElements(str, pos);
    if (el.type == STRING) {
        cout << "Это не множество\n";
        return 0;
    }
    vector<SetElement> vec;
    vec.push_back({ el });
    vector<vector<SetElement>> all = Permute(vec);
    int count = 1;
    for (auto& v : all) {
        cout << count++ << ": ";
        for (auto& v1 : v) {
            Printf(v1);
            cout << '\n';
        }
    }
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
