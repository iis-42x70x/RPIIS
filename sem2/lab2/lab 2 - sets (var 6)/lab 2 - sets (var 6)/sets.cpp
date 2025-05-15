// sets.cpp (исправленный парсинг и обработка вложенных структур)
#include "sets.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <stack>
#include <stdexcept>

using namespace std;

#include <stack>
#include <stdexcept>
#include <cctype>

void validateInput(const std::string& input) {
    std::stack<char> brackets;
    bool expectElement = true; // Ожидаем элемент (true) или разделитель (false)
    size_t pos = 0;

    auto throwError = [&](const std::string& msg) {
        throw std::runtime_error("Ошибка в позиции " + std::to_string(pos) + ": " + msg);
        };

    while (pos < input.size()) {
        char c = input[pos];

        // Пропускаем пробелы
        if (std::isspace(c)) {
            pos++;
            continue;
        }

        // Обработка открывающих скобок
        if (c == '{' || c == '<') {
            brackets.push(c);
            expectElement = true; // После скобки может быть элемент или закрывающая скобка
            pos++;
            continue;
        }

        // Обработка закрывающих скобок
        if (c == '}' || c == '>') {
            if (brackets.empty()) throwError("Лишняя закрывающая скобка");
            char expected = (c == '}') ? '{' : '<';
            if (brackets.top() != expected) throwError("Несоответствие скобок");
            brackets.pop();
            expectElement = false; // После скобки может быть запятая или конец
            pos++;
            continue;
        }

        // Обработка запятых
        if (c == ',') {
            if (expectElement) throwError("Запятая не может быть после открывающей скобки");
            expectElement = true; // После запятой ожидается элемент
            pos++;
            continue;
        }

        // Обработка элементов (числа, строки, вложенные структуры)
        if (expectElement) {
            // Пропускаем символы элемента до разделителя
            while (pos < input.size()) {
                c = input[pos];
                if (c == '{' || c == '<') break; // Начало вложенной структуры
                if (std::isspace(c) || c == ',' || c == '>' || c == '}') break;
                pos++;
            }
            expectElement = false; // Элемент обработан
        }
        else {
            throwError("Ожидалась запятая или закрывающая скобка");
        }
    }

    // Проверка незакрытых скобок
    if (!brackets.empty()) throwError("Незакрытая скобка");
}

// Функция для чтения файла
string readFile(const string& path) {
    ifstream file(path);
    if (!file.is_open()) throw runtime_error("Файл не найден!");
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Рекурсивный парсер токенов с учетом вложенности
pair<string, string> parseNextToken(const string& str) {
    stack<char> brackets;
    int pos = 0;
    bool inString = false;

    for (; pos < str.size(); ++pos) {
        char c = str[pos];
        if (c == '"' && (pos == 0 || str[pos - 1] != '\\'))
            inString = !inString;

        if (!inString) {
            if (c == '{' || c == '<') brackets.push(c);
            else if (c == '}' && !brackets.empty() && brackets.top() == '{') brackets.pop();
            else if (c == '>' && !brackets.empty() && brackets.top() == '<') brackets.pop();
        }

        if (brackets.empty() && c == ',' && !inString)
            break;
    }

    string token = str.substr(0, pos);
    string rest = (pos < str.size()) ? str.substr(pos + 1) : "";
    return { token, rest };
}

Set parseSet(const string& str) {
    Set s;
    string content = str.substr(1, str.size() - 2);
    string rest = content;

    while (!rest.empty()) {
        auto [token, remaining] = parseNextToken(rest);
        token.erase(remove_if(token.begin(), token.end(), ::isspace), token.end());
        if (!token.empty())
            s.elements.insert(parseElement(token));
        rest = remaining;
    }
    return s;
}

Tuple parseTuple(const string& str) {
    Tuple t;
    string content = str.substr(1, str.size() - 2);
    string rest = content;

    while (!rest.empty()) {
        auto [token, remaining] = parseNextToken(rest);
        token.erase(remove_if(token.begin(), token.end(), ::isspace), token.end());
        if (!token.empty())
            t.elements.push_back(parseElement(token));
        rest = remaining;
    }
    return t;
}

SetElement parseElement(const string& token) {
    if (token.empty()) throw invalid_argument("Empty token");

    if (token[0] == '{') return make_shared<Set>(parseSet(token));
    if (token[0] == '<') return make_shared<Tuple>(parseTuple(token));
    if (isdigit(token[0])) return stoi(token);
    return token; // Строка
}

vector<Set> ParseFile(const string& path) {
    string data = readFile(path);
    stringstream ss(data);
    string line;
    vector<Set> sets;

    while (getline(ss, line)) {
        validateInput(line); // Проверка ДО удаления пробелов!
        line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
        if (!line.empty()) sets.push_back(parseSet(line));
    }
    return sets;
}

// Генерация декартова произведения
void generateProduct(const vector<Set>& sets, int index, Tuple current, Set& result) {
    if (index == sets.size()) {
        result.elements.insert(make_shared<Tuple>(current));
        return;
    }
    for (const auto& elem : sets[index].elements) {
        Tuple next = current;
        next.elements.push_back(elem);
        generateProduct(sets, index + 1, next, result);
    }
}

Set DecartProduct(const vector<Set>& sets) {
    Set result;
    generateProduct(sets, 0, {}, result);
    return result;
}

void printElement(const SetElement& elem) {
    if (auto* p = get_if<int>(&elem)) {
        cout << *p;
    }
    else if (auto* p = get_if<string>(&elem)) {
        cout << *p;
    }
    else if (auto* p = get_if<shared_ptr<Set>>(&elem)) {
        cout << "{";
        bool first = true;
        for (const auto& e : (*p)->elements) {
            if (!first) cout << ", ";
            printElement(e);
            first = false;
        }
        cout << "}";
    }
    else if (auto* p = get_if<shared_ptr<Tuple>>(&elem)) {
        cout << "<";
        bool first = true;
        for (const auto& e : (*p)->elements) {
            if (!first) cout << ", ";
            printElement(e);
            first = false;
        }
        cout << ">";
    }
}