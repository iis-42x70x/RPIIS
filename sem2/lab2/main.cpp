#include <iostream>
#include <vector>
#include <string>

struct Elem {
    bool isSet;
    std::vector<Elem> set;  // если isSet==true
    std::string atom;       // если isSet==false

    Elem() : isSet(false), atom("") {}
    Elem(const std::string& s) : isSet(false), atom(s) {}
    Elem(const std::vector<Elem>& v) : isSet(true), set(v) {}

    static int strcmp_custom(const std::string& a, const std::string& b) {
        size_t i = 0;
        while (i < a.size() && i < b.size()) {
            if (a[i] < b[i]) return -1;
            if (a[i] > b[i]) return 1;
            i++;
        }
        if (a.size() < b.size()) return -1;
        if (a.size() > b.size()) return 1;
        return 0;
    }

    bool operator<(const Elem& other) const {
        if (isSet != other.isSet) return isSet < other.isSet;
        if (!isSet) return strcmp_custom(atom, other.atom) < 0;
        size_t len = set.size() < other.set.size() ? set.size() : other.set.size();
        for (size_t i = 0; i < len; ++i) {
            if (set[i] < other.set[i]) return true;
            if (other.set[i] < set[i]) return false;
        }
        return set.size() < other.set.size();
    }

    bool operator==(const Elem& other) const {
        if (isSet != other.isSet) return false;
        if (!isSet) return atom == other.atom;
        if (set.size() != other.set.size()) return false;
        for (size_t i = 0; i < set.size(); ++i)
            if (!(set[i] == other.set[i])) return false;
        return true;
    }

    std::string toString() const {
        if (!isSet) return atom;
        std::string res = "{";
        for (size_t i = 0; i < set.size(); ++i) {
            if (i > 0) res += ",";
            res += set[i].toString();
        }
        res += "}";
        return res;
    }
};

bool is_space(char ch) {
    return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r';
}

void trim(std::string& s) {
    size_t start = 0;
    while (start < s.size() && is_space(s[start])) start++;
    size_t end = s.size();
    while (end > start && is_space(s[end - 1])) end--;
    s = s.substr(start, end - start);
}

void error() {
    std::cout << "Некорректные входные данные\n";
    std::exit(0);
}

void insertionSort(std::vector<Elem>& v) {
    for (size_t i = 1; i < v.size(); ++i) {
        Elem key = v[i];
        size_t j = i;
        while (j > 0 && key < v[j-1]) {
            v[j] = v[j-1];
            j--;
        }
        v[j] = key;
    }
}

Elem parseSet(const std::string& s, size_t& pos) {
    if (pos >= s.size()) error();

    char open = s[pos];
    char close;
    if (open == '{') close = '}';
    else if (open == '<') close = '>';
    else error();

    pos++;

    std::vector<Elem> elems;
    std::string buf;
    int lvl = 0;

    while (pos < s.size()) {
        char ch = s[pos];

        if ((ch == '{' || ch == '<') && lvl == 0) {
            Elem subSet = parseSet(s, pos);
            elems.push_back(subSet);
        }
        else if (ch == ',' && lvl == 0) {
            trim(buf);
            if (!buf.empty()) {
                elems.push_back(Elem(buf));
                buf.clear();
            }
            pos++;
        }
        else if (ch == close && lvl == 0) {
            trim(buf);
            if (!buf.empty()) {
                elems.push_back(Elem(buf));
                buf.clear();
            }
            pos++;
            // Сортируем элементы для нормализации
            insertionSort(elems);
            return Elem(elems);
        }
        else {
            if (ch == '{' || ch == '<') lvl++;
            else if (ch == '}' || ch == '>') lvl--;
            buf += ch;
            pos++;
        }
    }
    error();
    return Elem();
}

Elem parseSetString(const std::string& s) {
    size_t pos = 0;
    std::string copy = s;
    trim(copy);
    Elem res = parseSet(copy, pos);
    if (pos != copy.size()) error();
    return res;
}

// Находит индекс элемента e в векторе v, или -1 если не найден
int findElemIndex(const std::vector<Elem>& v, const Elem& e) {
    for (size_t i = 0; i < v.size(); ++i) {
        if (v[i] == e) return (int)i;
    }
    return -1;
}

void processUnion(int N) {
    std::vector<Elem> gk;  // уникальные элементы глобально
    std::vector<int> gc;   // максимальная кратность каждого элемента
    for (int i = 1; i <= N; ++i) {
        std::cout << "Множество #" << i << ": ";
        std::string line;
        std::getline(std::cin, line);
        trim(line);
        if (line.empty()) { i--; continue; }

        // Если есть '=', берем правую часть
        size_t eqpos = line.find('=');
        std::string setPart = (eqpos == std::string::npos) ? line : line.substr(eqpos + 1);
        trim(setPart);

        Elem E = parseSetString(setPart);

        // Подсчет локальной кратности (учитывая повторения)
        std::vector<Elem> sk;  // локальные ключи
        std::vector<int> sc;   // локальные счетчики

        for (const Elem& el : E.isSet ? E.set : std::vector<Elem>{E}) {
            int idx = findElemIndex(sk, el);
            if (idx >= 0) sc[idx]++;
            else {
                sk.push_back(el);
                sc.push_back(1);
            }
        }
        // Обновление глобальных частот (максимум)
        for (size_t k = 0; k < sk.size(); ++k) {
            int gi = findElemIndex(gk, sk[k]);
            if (gi >= 0) {
                if (gc[gi] < sc[k]) gc[gi] = sc[k];
            } else {
                gk.push_back(sk[k]);
                gc.push_back(sc[k]);
            }
        }
    }

    // Вывод объединения с кратностями
    std::cout << "Объединение: {";
    bool first = true;
    for (size_t i = 0; i < gk.size(); ++i) {
        for (int c = 0; c < gc[i]; ++c) {
            if (!first) std::cout << ",";
            std::cout << gk[i].toString();
            first = false;
        }
    }
    std::cout << "}\n";
}

int main() {
    std::cout << "Сколько множеств? ";
    int N;
    if (!(std::cin >> N) || N <= 0) {
        std::cout << "Некорректные входные данные\n";
        return 0;
    }
    std::cin.ignore();

    processUnion(N);

    return 0;
}
