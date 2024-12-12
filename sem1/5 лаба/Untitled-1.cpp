#include <iostream>
#include <string>
using namespace std;

int readWord(string str, int pos, char razd) { //длина слова до разделителя razd с позиции pos
    int l;
    for (l = 0; pos < str.size(); ++l) {
        if (str[pos] == razd) {
            break;
        }
        pos++;
    }
    return l;
}


int main() {
    setlocale(LC_ALL, "Russian");

    string inputStr;
    cout << "Введите строку: ";
    getline(cin, inputStr);

    char razd = *" ";
    char zam = *"_";

    for (int i = 0; i < inputStr.size(); i++)
    {
        if (inputStr[i] == razd)
        {
            inputStr[i] = zam;
        }
    }

    for (int i = 0; i < inputStr.size(); i = i + 1 + readWord(inputStr, i, zam))
    {
        if (readWord(inputStr, i, zam) > 1)
        {
            inputStr.replace(i, 1, "<");
            int j = i + readWord(inputStr, i, zam);
            inputStr.replace(j - 1, 1, ">");
        }
    }

    cout << "Замена строки:  " << inputStr << endl;

    return 0;
}