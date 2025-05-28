#include <iostream>
#include <vector>
#include <string>
#include "Set_lib\Set.hpp"
#include <windows.h>

using namespace std;

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    vector<string> s1,s2;
    bool read = file_read(s1,s2);
    if (!read){
        cout << "Ошибка считывания множества!";
        return 0;
    }
    cout << "s1:\n";
    for(const auto& str: s1){
        cout << str << " ";
    }
    cout << endl;
    cout << "s2:\n";
    for(const auto& str: s2){
        cout << str << " ";
    }
    cout << endl;
    cout << "Для А/В: \n";
    difference(s1,s2);
    cout << "Для B/A: \n";
    difference(s2,s1);
    return 0;
}