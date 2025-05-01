#include <iostream>
#include <cstring>
#include <cctype>
#include "header.h"

using namespace std;

static const int MAX_TOTAL = MAX_SETS * MAX_ELEMENTS;
static char freqElems[MAX_TOTAL][MAX_ELEMENT_LENGTH];
static int  freqCounts[MAX_TOTAL];
static int  freqTotal = 0;

void trim_whitespace(char* str) {
    int len = strlen(str), start = 0;
    while (start < len && isspace(str[start])) start++;
    int end = len - 1;
    while (end >= 0 && isspace(str[end])) end--;
    if (end < start) {
        str[0] = '\0';
        return;
    }
    memmove(str, &str[start], end - start + 1);
    str[end - start + 1] = '\0';
}

void remove_all_spaces(char* str) {
    int i = 0, j = 0;
    while (str[i]) {
        if (!isspace(str[i])) {
            str[j++] = str[i];
        }
        i++;
    }
    str[j] = '\0';
}

int parse_elements_recursive(const char* set_str, char elements[MAX_ELEMENTS][MAX_ELEMENT_LENGTH], int depth) {
    int count = 0;
    int start = 1;
    int len = strlen(set_str);
    int current_depth = 0;

    for (int i = start; i < len - 1; i++) {
        if (set_str[i] == '<') current_depth++;
        if (set_str[i] == '>') current_depth--;

        if (current_depth == depth && set_str[i] == ',') {
            int elem_len = i - start;
            strncpy(elements[count], &set_str[start], elem_len);
            elements[count][elem_len] = '\0';
            trim_whitespace(elements[count]);
            remove_all_spaces(elements[count]);
            count++;
            start = i + 1;
        }
    }

    if (start < len - 1) {
        int elem_len = len - 1 - start;
        strncpy(elements[count], &set_str[start], elem_len);
        elements[count][elem_len] = '\0';
        trim_whitespace(elements[count]);
        remove_all_spaces(elements[count]);
        count++;
    }

    return count;
}

int parse_sets_from_line(const char* line, char sets[MAX_SETS][MAX_ELEMENTS][MAX_ELEMENT_LENGTH], int set_counts[MAX_SETS]) {
    int set_index = 0;
    const char* p = line;

    while (*p) {
        while (*p && (isalpha(*p) || isspace(*p))) p++;
        if (*p == '=') p++;
        while (*p && isspace(*p)) p++;

        if (*p != '{') break;

        const char* start = p;
        int braces = 0;
        do {
            if (*p == '{') braces++;
            else if (*p == '}') braces--;
            p++;
        } while (*p && braces > 0);

        int len = p - start;
        if (len >= MAX_LINE_LENGTH) return -1;

        char buffer[MAX_LINE_LENGTH];
        strncpy(buffer, start, len);
        buffer[len] = '\0';
        int count = parse_elements_recursive(buffer, sets[set_index], 0);
        if (count < 0) return -1;
        set_counts[set_index] = count;
        set_index++;

        while (*p && (*p == ',' || isspace(*p))) p++;

        if (set_index >= MAX_SETS) break;
    }

    return set_index;
}


bool is_equal(const char* a, const char* b) {
    return strcmp(a, b) == 0;
}

bool exists_in(const char* elem, char set[][MAX_ELEMENT_LENGTH], int count) {
    for (int i = 0; i < count; i++) {
        if (is_equal(elem, set[i])) return true;
    }
    return false;
}

void countFreqRec(int idx,
    char sets[MAX_SETS][MAX_ELEMENTS][MAX_ELEMENT_LENGTH],
    int set_counts[MAX_SETS],
    int set_count)
{
    if (idx == set_count) return;

    for (int j = 0; j < set_counts[idx]; ++j) {
        char* elem = sets[idx][j];
        int k = 0;
        for (; k < freqTotal; ++k) {
            if (strcmp(freqElems[k], elem) == 0) {
                freqCounts[k]++;
                break;
            }
        }
        if (k == freqTotal) {
            strncpy(freqElems[freqTotal], elem, MAX_ELEMENT_LENGTH - 1);
            freqElems[freqTotal][MAX_ELEMENT_LENGTH - 1] = '\0';
            freqCounts[freqTotal] = 1;
            freqTotal++;
        }
    }

    countFreqRec(idx + 1, sets, set_counts, set_count);
}

int symmetric_difference_all(
    char sets[MAX_SETS][MAX_ELEMENTS][MAX_ELEMENT_LENGTH],
    int set_counts[MAX_SETS],
    int set_count,
    char result[MAX_ELEMENTS][MAX_ELEMENT_LENGTH]
) {
    freqTotal = 0;
    countFreqRec(0, sets, set_counts, set_count);

    int res_cnt = 0;
    for (int i = 0; i < freqTotal; ++i) {
        if (freqCounts[i] == 1) {
            strncpy(result[res_cnt], freqElems[i], MAX_ELEMENT_LENGTH - 1);
            result[res_cnt][MAX_ELEMENT_LENGTH - 1] = '\0';
            res_cnt++;
        }
    }
    return res_cnt;
}


void print_set(char elements[][MAX_ELEMENT_LENGTH], int count) {
    cout << "{";
    for (int i = 0; i < count; i++) {
        if (i > 0) cout << ",";
        cout << elements[i];
    }
    cout << "}";
}

int main() {
    char sets[MAX_SETS][MAX_ELEMENTS][MAX_ELEMENT_LENGTH];
    int set_counts[MAX_SETS];
    int set_count = 0;

    while (true) {
        cout << "\nМеню:\n1. Ввод множеств\n2. Просмотр\n3. Симметрическая разность\n4. Выход\nВыбор: ";
        int choice;
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            cout << "Введите строку вида A = {1,2}, B = {2,3}, ...\n> ";
            char line[MAX_LINE_LENGTH];
            cin.getline(line, MAX_LINE_LENGTH);
            set_count = parse_sets_from_line(line, sets, set_counts);
            if (set_count <= 0) {
                cout << "Ошибка ввода." << endl;
            } else {
                cout << "Считано множеств: " << set_count << endl;
            }
        }
        else if (choice == 2) {
            for (int i = 0; i < set_count; i++) {
                cout << "Множество " << (i + 1) << ": ";
                print_set(sets[i], set_counts[i]);
                cout << endl;
            }
        }
        else if (choice == 3) {
            if (set_count < 2) {
                cout << "Нужно минимум два множества!" << endl;
                continue;
            }
            char result[MAX_ELEMENTS][MAX_ELEMENT_LENGTH];
            int count = symmetric_difference_all(sets, set_counts, set_count, result);
            cout << "Симметрическая разность всех множеств: ";
            print_set(result, count);
            cout << endl;
        }
        else if (choice == 4) {
            break;
        }
        else {
            cout << "Неверный выбор!" << endl;
        }
    }

    return 0;
}
