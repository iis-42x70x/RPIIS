#include "pch.h"

bool letter(char k) {
    return (k >= 'а' && k <= 'я') || (k >= 'А' && k <= 'Я') ||
        (k >= 'a' && k <= 'z') || (k >= 'A' && k <= 'Z');
}

bool digit(char f) {
    return f >= '0' && f <= '9';
}

bool space(char ch) {
    return ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r';
}

bool ElementCompare(const element el1, const element el2) {
    if (el1.type != el2.type) return false;

    if (el1.type == STRING) {
        if (el1.value == el2.value) return true;
        else return false;
    }

    else if (el1.type == ORSET) {
        if (el1.setik.size() != el2.setik.size()) return false;
        for (int i = 0; i < el1.setik.size(); i++) {
            if (!ElementCompare(el1.setik[i], el2.setik[i])) return false;
        }
    }

    else if (el1.type == SET) {
        if (el1.setik.size() != el2.setik.size()) return false;
        for (int i = 0; i < el1.setik.size(); i++) {
            bool find = false;
            for (int j = 0; j < el2.setik.size(); j++) {
                if (ElementCompare(el1.setik[i], el2.setik[j])) {
                    find = true;
                    break;
                }
            }
            if (!find) return false;
        }
    }
    return true;
}

element intersection(const element el1, const element el2) {
    element result;
    if (el1.type == SET && el2.type == SET) {
        result.type = SET;
        for (element c1 : el1.setik) {
            for (element c2 : el2.setik) {
                if (ElementCompare(c1, c2)) {
                    result.setik.push_back(c1);
                    break;
                }
            }
        }
    }

    else if (el1.type == ORSET && el2.type == ORSET) {
        result.type = ORSET;
        int size =( el1.setik.size() > el2.setik.size()) ? el2.setik.size() : el1.setik.size();
        for (int i = 0; i < size; i++) {
            if (ElementCompare(el1.setik[i], el2.setik[i]))result.setik.push_back(el1.setik[i]);
        }
    }
    return result;
}

void ElementCout(const element el) {
    if (el.type == STRING) cout << el.value;
    else if (el.type == SET) {
        cout << "{";
        for (int i = 0; i < el.setik.size(); i++) {
            ElementCout(el.setik[i]);
            if (i < el.setik.size() - 1) cout << ", ";
        }
        cout << "}";
    }
    else if (el.type == ORSET) {
        cout << "<";
        for (int i = 0; i < el.setik.size(); i++) {
            ElementCout(el.setik[i]);
            if (i < el.setik.size() - 1) cout << ", ";
        }
        cout << ">";
    }
}

void StringToElement(element& el, string s, int start, int end) {
    int k, skobka;
    string val;
    int count = 0;
    if (s[start] == '<') el.type = ORSET;
    else el.type = SET;
    if (end - start == 1) {
        el.setik.resize(el.setik.size() + 1);
        el.setik[0].value = "";
        el.setik[0].type = STRING;
        return;
    }
    for (int i = start + 1; i <= end - 1; i++) {
        if (letter(s[i])) {
            val = "";
            while ((letter(s[i]) || digit(s[i]) || s[i] == '_') && i <= end - 1) {
                val += s[i];
                i++;
            }
            i--;
            el.setik.resize(el.setik.size() + 1);
            el.setik[count].value = val;
            el.setik[count].type = STRING;
            count++;
        }

        else if (digit(s[i]) || s[i] == '-') {
            val = "";
            if (s[i] == '-') {
                val += s[i];
                i++;
            }
            while (digit(s[i]) && i <= end - 1) {
                val += s[i];
                i++;
            }
            i--;
            el.setik.resize(el.setik.size() + 1);
            el.setik[count].value = val;
            el.setik[count].type = STRING;
            count++;
        }

        else if (s[i] == '{') {
            skobka = 1;
            k = i + 1;
            while (k <= end && skobka != 0) {
                if (s[k] == '{') skobka++;
                else if (s[k] == '}') skobka--;
                k++;
            }
            el.setik.resize(el.setik.size() + 1);
            StringToElement(el.setik[count], s, i, k--);
            count++;
            i = k--;
        }

        else if (s[i] == '<') {
            skobka = 1;
            k = i + 1;

            while (k <= end && skobka != 0) {
                if (s[k] == '<') skobka++;
                else if (s[k] == '>') skobka--;
                k++;
            }
            el.setik.resize(el.setik.size() + 1);
            StringToElement(el.setik[count], s, i, k--);
            count++;
            i = k--;
        }
    }
}

bool SetUniqueCheck(element el) {
    if (el.type == SET) {
        for (int i = 0; i < el.setik.size() - 1; i++) {
            for (int j = i + 1; j < el.setik.size(); j++) {
                if (ElementCompare(el.setik[i], el.setik[j])) return false;
            }
        }
    }

    else if (el.type == ORSET) {
        for (int i = 0; i < el.setik.size(); i++) {
            if (el.setik[i].type == SET && !SetUniqueCheck(el.setik[i])) return false;
            else if (el.setik[i].type == ORSET) SetUniqueCheck(el.setik[i]);
        }
    }

    else exit(-3);

    return true;
}

bool StringCheck(string& str) {
    if (str.empty() || (str[0] != '{' && str[0] != '<')) return false;
    if ((str[0] == '{' && str[str.size() - 1] != '}') || (str[0] == '<' && str[str.size() - 1] != '>')) return false;


    for (int i = 0; i < str.size(); i++) {
        if (letter(str[i])) {
            i++;
            while ((letter(str[i]) || digit(str[i]) || str[i] == '_') && i < str.size()) i++;
            int j = i;
            i--;
            while (space(str[j]) && j < str.size()) j++;
            if (j == str.size()) return false;
            else if (str[j] != '}' && str[j] != '>' && str[j] != ',') return false;
        }
        else if (space(str[i])) {
            for (int j = i + 1; j < str.size(); j++)str[j - 1] = str[j];
            str.pop_back();
            i--;
        }
    }

    stack <char> bra;
    int count = 0;
    int count1 = 0;
    bool var = false;
    for (int j = 0; j < str.size(); j++) {
        if (j + 1 < str.size() && ((str[j] == '{' && str[j + 1] == ',') || (str[j] == '<' && str[j + 1] == ',') ||
            (str[j] == ',' && (str[j + 1] == '}' || str[j + 1] == '>')) || (str[j] == ',' && str[j + 1] == ',') ||
            (str[j] == '}' && str[j + 1] == '{') || (str[j] == '>' && str[j + 1] == '<'))) {
            return false;
        }

        if (letter(str[j])) {
            j++;
            if (!var) {
                while ((letter(str[j]) || digit(str[j]) || str[j] == '_') && j < str.size()) j++;
                j--;
                var = true;
            }
            else return false;


        }

        else if (digit(str[j]) || str[j] == '-') {
            j++;
            if (!var) {
                while ((letter(str[j]) || digit(str[j]) || str[j] == '_') && j < str.size()) j++;
                j--;
                var = true;
            }
            else return false;
        }
        else var = false;

        if (str[j] == '{' || str[j] == '<' || str[j] == '}' || str[j] == '>') {
            bra.push(str[j]);
            if (bra.top() == '}') {
                bra.pop();
                if (bra.empty() || bra.top() != '{') return false;
                bra.pop();
            }

            else  if (bra.top() == '>') {
                bra.pop();
                if (bra.empty() || bra.top() != '<') return false;
                bra.pop();
            }

            if (j > 0 && j < str.size() - 1 && bra.empty()) return false;
        }
    }
    if (!bra.empty()) return false;
    return true;
}
