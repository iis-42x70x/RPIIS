#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <cstdlib>

using namespace std;
//удаление пробелов, табуляцию, перенос строки
string trim(const string& str) {
    string result = str;
    size_t start = result.find_first_not_of(" \t\n\r");
    size_t end = result.find_last_not_of(" \t\n\r");
    if (start == string::npos || end == string::npos) {
        return "";
    }
    result = result.substr(start, end - start + 1);

    size_t pos = result.find(" ");
    while (pos != string::npos) {
        result.erase(pos, 1);
        pos = result.find(" ", pos);
    }

    return result;
}
//поиск закрывающихся скобок
int find_next_bracker(const string& s, int i) {
    int cnt = 0;
    if (s[i] == '{') {
        for (int j = i + 1; j < s.size(); j++) {
            if (s[j] == '{') cnt++;
            if (s[j] == '}') {
                if (cnt) cnt--;
                else return j;
            }
        }
    }
    else if (s[i] == '<') {
        for (int j = i + 1; j < s.size(); j++) {
            if (s[j] == '<') cnt++;
            if (s[j] == '>') {
                if (cnt) cnt--;
                else return j;
            }
        }
    }
    return -1; // если не нашли
}

string corteges(string s);
string sets(string s);
// обработка кортежей
string corteges(string s) {
    s += ',';
    string result;
    vector<string> elements;
    string element;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '{') {
            int end = find_next_bracker(s, i) - 1;
            i++;
            string str = s.substr(i, end - i + 1);
            elements.push_back(sets(str));
            i = end + 2;
            element = "";
            continue;
        }
        if (s[i] == '<') {
            int end = find_next_bracker(s, i) - 1;
            i++;
            string str = s.substr(i, end - i + 1);
            elements.push_back(corteges(str));
            i = end + 2;
            element = "";
            continue;
        }

        if (s[i] != ',') {
            element += s[i];
        }
        else {
            elements.push_back(element);
            element = "";
        }
    }

    for (string i : elements) {
        result += i + ", ";
    }
    result.erase(result.size() - 2, 2);
    result = '<' + result + '>';
    return result;
}
// обработка множеств
string sets(string s) {
    s += ',';
    string result;
    multiset<string> elements;
    string element;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '{') {
            int end = find_next_bracker(s, i) - 1;
            i++;
            string str = s.substr(i, end - i + 1);
            elements.insert(sets(str));
            i = end + 2;
            element = "";
            continue;
        }
        if (s[i] == '<') {
            int end = find_next_bracker(s, i) - 1;
            i++;
            string str = s.substr(i, end - i + 1);
            elements.insert(corteges(str));
            i = end + 2;
            element = "";
            continue;
        }

        if (s[i] != ',') {
            element += s[i];
        }
        else {
            elements.insert(element);
            element = "";
        }
    }

    for (string i : elements) {
        result += i + ", ";
    }
    result.erase(result.size() - 2, 2);
    result = '{' + result + '}';
    return result;
}
//пересечение
multiset<string> intersection(const string& file_path) {
    ifstream file(file_path);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл.\n";
        exit(-1);
    }

    string line;
    multiset<string> result;
    bool firstSet = true;

    while (getline(file, line)) {
        line = trim(line);
        line = line.substr(3, line.length() - 4); // убираем "S1 = {....}"


        multiset<string> currentSet;
        string element;
        line += ',';
        for (int i = 0; i < line.size(); i++) {
            if (line[i] == '{') {
                int end = find_next_bracker(line, i) - 1;
                i++;
                string str = line.substr(i, end - i + 1);
                currentSet.insert(sets(str));
                i = end + 2;
                element = "";
                continue;
            }
            if (line[i] == '<') {
                int end = find_next_bracker(line, i) - 1;
                i++;
                string str = line.substr(i, end - i + 1);
                currentSet.insert(corteges(str));
                i = end + 2;
                element = "";
                continue;
            }

            if (line[i] != ',') {
                element += line[i];
            }
            else {
                currentSet.insert(element);
                element = "";
            }
        }

        if (firstSet) {
            result = currentSet;
            firstSet = false;
        }
        else {
            multiset<string> intersectionSet;
            for (const string& elem : currentSet) {
                auto it = result.find(elem);
                if (it != result.end()) {
                    intersectionSet.insert(elem);
                    result.erase(it); // чтобы не учитывать повторно
                }
            }
            result = intersectionSet;
        }
    }

    file.close();
    return result;
}
void process() {
    setlocale(LC_ALL, "ru");
    string file_path = "C:/Users/Redmi/OneDrive/Рабочий стол/БГУИР/ПиОИвИС/input.txt";

    multiset<string> result = intersection(file_path);

    cout << "Пересечение множеств:\n";
    if (result.empty())
    {
        cout << "Пустое множество"<<endl;
    }
    else
    {
        for (const string& elem : result) {
            cout << elem << endl;
        }
    }
    
}
