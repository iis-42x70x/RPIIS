#include "Set.h"

void CustomSet::addElement(const SetElement& element) {
    elements.push_back(element);
}

bool CustomSet::contains(const SetElement& element) const {
    return find(elements.begin(), elements.end(), element) != elements.end();
}

size_t CustomSet::size() const {
    return elements.size();
}

CustomSet CustomSet::difference(const CustomSet& other) const {
    CustomSet result;
    unordered_map<string, int> countMap;

    for (const auto& elem : elements) {
        countMap[elementToString(elem)]++;
    }

    for (const auto& elem : other.elements) {
        string key = elementToString(elem);
        if (countMap.find(key) != countMap.end()) {
            countMap[key]--;
            if (countMap[key] == 0) {
                countMap.erase(key);
            }
        }
    }

    for (const auto& elem : elements) {
        string key = elementToString(elem);
        if (countMap.find(key) != countMap.end() && countMap[key] > 0) {
            result.addElement(elem);
            countMap[key]--;
        }
    }

    return result;
}

string CustomSet::elementToString(const SetElement& element) {
    return std::visit([](auto&& arg) -> std::string {
        using T = decay_t<decltype(arg)>;
        if constexpr (is_same_v<T, int>) {
            return to_string(arg);
        }
        else if constexpr (is_same_v<T, string>) {
            return arg;
        }
        else if constexpr (is_same_v<T, vector<int>>) {
            stringstream ss;
            ss << "<";
            for (size_t i = 0; i < arg.size(); ++i) {
                ss << arg[i];
                if (i != arg.size() - 1) ss << ", ";
            }
            ss << ">";
            return ss.str();
        }
        else if constexpr (is_same_v<T, unordered_set<string>>) {
            vector<string> sorted(arg.begin(), arg.end());
            sort(sorted.begin(), sorted.end());
            stringstream ss;
            ss << "{";
            for (size_t i = 0; i < sorted.size(); ++i) {
                ss << sorted[i];
                if (i != sorted.size() - 1) ss << ", ";
            }
            ss << "}";
            return ss.str();
        }
        return "";
        }, element);
}

SetElement CustomSet::parseToken(const string& token) {
    if (token.empty()) throw std::invalid_argument("Пустой элемент");

    if (token.front() == '<' && token.back() == '>') {
        vector<int> tuple;
        string inner = token.substr(1, token.size() - 2);
        stringstream ss(inner);
        string num;
        while (getline(ss, num, ',')) {
            num = trim(num);
            if (!num.empty()) {
                tuple.push_back(stoi(num));
            }
        }
        return tuple;
    }

    if (token.front() == '{' && token.back() == '}') {
        unordered_set<string> innerSet;
        string inner = token.substr(1, token.size() - 2);
        stringstream ss(inner);
        string word;
        while (getline(ss, word, ',')) {
            word = trim(word);
            if (!word.empty()) {
                innerSet.insert(word);
            }
        }
        return innerSet;
    }

    try {
        return stoi(token);
    }
    catch (...) {
        return token;
    }
}


CustomSet CustomSet::parseFromString(const string& str) {
    CustomSet result;
    if (str.empty() || str.front() != '{' || str.back() != '}')
        throw std::invalid_argument("Множество должно начинаться и заканчиваться фигурными скобками");

    size_t i = 1;  // пропускаем первую {
    string token;
    stack<char> brackets;

    while (i < str.size() - 1) {  // игнорируем последнюю }
        char ch = str[i];

        if (isspace(ch)) {
            ++i;
            continue;
        }

        if (ch == '{' || ch == '<') {
            token += ch;
            brackets.push(ch);
            ++i;
            continue;
        }

        if ((ch == '}' && !brackets.empty() && brackets.top() == '{') ||
            (ch == '>' && !brackets.empty() && brackets.top() == '<')) {
            token += ch;
            brackets.pop();
            ++i;
            continue;
        }

        if (ch == ',' && brackets.empty()) {
            if (!token.empty()) {
                result.addElement(parseToken(trim(token)));
                token.clear();
            }
            ++i;
            continue;
        }

        token += ch;
        ++i;
    }

    if (!token.empty()) {
        result.addElement(parseToken(trim(token)));
    }

    return result;
}


string CustomSet::toString() const {
    stringstream ss;
    ss << "{";
    for (size_t i = 0; i < elements.size(); ++i) {
        ss << elementToString(elements[i]);
        if (i != elements.size() - 1) ss << ", ";
    }
    ss << "}";
    return ss.str();
}

string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    size_t end = s.find_last_not_of(" \t\r\n");
    return (start == string::npos) ? "" : s.substr(start, end - start + 1);
}


bool isValid(const std::string& str) {
    if (str.empty()) return false;

    std::stack<char> bracketStack;
    bool lastWasComma = false;
    bool expectElement = true;
    int balance = 0;

    for (size_t i = 0; i < str.size(); ++i) {
        char ch = str[i];

        if (ch == '{' || ch == '<') {
            bracketStack.push(ch);
            expectElement = true;
            lastWasComma = false;
        }
        else if (ch == '}' || ch == '>') {
            if (bracketStack.empty()) return false;
            char open = bracketStack.top();
            if ((ch == '}' && open != '{') || (ch == '>' && open != '<'))
                return false;
            bracketStack.pop();
            expectElement = false;
        }
        else if (ch == ',') {
            if (lastWasComma || expectElement) return false;
            lastWasComma = true;
            expectElement = true;
        }
        else if (!isspace(ch)) {
            lastWasComma = false;
            expectElement = false;
        }
    }

    return bracketStack.empty() && !expectElement;
}

void solution(const std::string& filepath, bool isConst) {
    ifstream input(filepath);
    if (!input) {
        cerr << "Не удалось открыть файл: " << filepath << endl;
        return;
    }

    vector<string> lines;
    string line;

    while (getline(input, line)) {
        if (line.find_first_not_of(" \t\r\n") != string::npos) {
            lines.push_back(line);
        }
    }

    if (isConst) {
        if (lines.size() < 2) {
            cerr << "Недостаточно строк в файле для выбора двух разных множеств." << endl;
            return;
        }

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, static_cast<int>(lines.size() - 1));

        int idx1 = dis(gen);
        int idx2;
        do {
            idx2 = dis(gen);
        } while (idx2 == idx1);

        try {
            CustomSet set1 = CustomSet::parseFromString(lines[idx1]);
            CustomSet set2 = CustomSet::parseFromString(lines[idx2]);

            cout << "Выбранные множества из файла:\n\n";
            cout << "\tПервое множество (строка " << idx1 + 1 << "): " << set1.toString() << endl;
            cout << "\tВторое множество (строка " << idx2 + 1 << "): " << set2.toString() << endl;

            CustomSet diff = set1.difference(set2);
            cout << "\tРазность множеств: " << diff.toString() << endl;
        }
        catch (const std::exception& e) {
            cerr << "Ошибка при разборе множеств: " << e.what() << endl;
        }

    }
    else {
        if (lines.size() < 2) {
            cerr << "Файл должен содержать как минимум две непустые строки." << endl;
            return;
        }

        const std::string& line1 = lines[0];
        const std::string& line2 = lines[1];

        if (!isValid(line1) || !isValid(line2)) {
            cerr << "Ошибка: один или оба множества содержат недопустимые элементы.\n";
            cerr << "Формат должен быть: {числа, <1, 2>, {1, 2}}, без вложенных структур.\n\n";
            return;
        }

        try {
            CustomSet set1 = CustomSet::parseFromString(line1);
            CustomSet set2 = CustomSet::parseFromString(line2);

            cout << "Множества, указанные пользователем:\n\n";
            cout << "\tПервое множество: " << set1.toString() << endl;
            cout << "\tВторое множество: " << set2.toString() << endl;

            CustomSet diff = set1.difference(set2);
            cout << "\tРазность множеств: " << diff.toString() << endl;
        }
        catch (const std::exception& e) {
            cerr << "Ошибка при разборе множеств: " << e.what() << endl;
        }
    }
}