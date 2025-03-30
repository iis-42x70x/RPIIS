#include "Header.h"
#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

void GetSets(Set MultiSet[], string path) {
    ifstream file;
    file.open(path);

    if (!file.is_open()) {
        throw runtime_error("Ошибка открытия файла!");
    }

    int curr_brackets_count = 0;
    char ch;
    int m = -1;
    MultiSet[0].set_count = m + 1;
    int elem_in_set = 0;

    while (file.get(ch)) {
        if (ch == '{') {
            if (curr_brackets_count > 0) {
                MultiSet[m].Elem[elem_in_set].element.push_back(ch);
                MultiSet[m].Elem[elem_in_set].code_num += ch;
                curr_brackets_count++;
            }
            else {
                m++;
                MultiSet[0].set_count = m + 1;
                elem_in_set = 0;
                curr_brackets_count++;
            }
        }
        else if (ch == ',') {
            if (curr_brackets_count == 1) {
                elem_in_set++;
            }
            else {
                MultiSet[m].Elem[elem_in_set].element.push_back(ch);
                MultiSet[m].Elem[elem_in_set].code_num += ch;
            }
        }
        else if (isdigit(ch)) {
            if (curr_brackets_count == 1) {
                if (MultiSet[m].Elem[elem_in_set].multiplicity == 1 && !MultiSet[m].Elem[elem_in_set].IsAlone) {
                    MultiSet[m].Elem[elem_in_set].multiplicity = (ch - '0');
                    MultiSet[m].Elem[elem_in_set].IsAlone = true;
                }
                else {
                    MultiSet[m].Elem[elem_in_set].multiplicity = MultiSet[m].Elem[elem_in_set].multiplicity * 10 + (ch - '0');
                }
            }
            else {
                MultiSet[m].Elem[elem_in_set].element.push_back(ch);
                MultiSet[m].Elem[elem_in_set].code_num += ch;
            }
        }
        else if (ch == '}') {
            if (curr_brackets_count > 1) {
                MultiSet[m].Elem[elem_in_set].element.push_back(ch);
                MultiSet[m].Elem[elem_in_set].code_num += ch;
                curr_brackets_count--;
            }
            else {
                MultiSet[m].elem_count = elem_in_set + 1;
                curr_brackets_count--;
            }
        }
        else if (ch == ' ' || ch == '\n') {
            // Пропускаем пробелы и переносы строк
        }
        else {
            MultiSet[m].Elem[elem_in_set].element.push_back(ch);
            MultiSet[m].Elem[elem_in_set].code_num += ch;
        }
    }
    MultiSet[0].brackets_count = curr_brackets_count;
    file.close();
}

void SeeSets(Set MultiSet[]) {
    for (int i = 0; i < MultiSet[0].set_count; i++) {
        cout << "МНОЖЕСТВО № " << i + 1 << ": \n\n\t{ ";
        for (int j = 0; j < MultiSet[i].elem_count; j++) {
            if (MultiSet[i].Elem[j].multiplicity == 1) {
                if (j != MultiSet[i].elem_count - 1) {
                    cout << MultiSet[i].Elem[j].element << ", ";
                }
                else {
                    cout << MultiSet[i].Elem[j].element;
                }
            }
            else {
                if (j != MultiSet[i].elem_count - 1) {
                    cout << MultiSet[i].Elem[j].multiplicity << MultiSet[i].Elem[j].element << ", ";
                }
                else {
                    cout << MultiSet[i].Elem[j].multiplicity << MultiSet[i].Elem[j].element;
                }
            }
        }
        cout << "} \n\n\n";
    }
}

void OneType(Set MultiSet[]) {
    for (int i = 0; i < MultiSet[0].set_count; i++) {
        for (int j = 0; j < MultiSet[i].elem_count; j++) {
            for (int k = j + 1; k < MultiSet[i].elem_count; k++) {
                if (((MultiSet[i].Elem[j].element == MultiSet[i].Elem[k].element) &&
                    ((MultiSet[i].Elem[j].multiplicity != MultiSet[i].Elem[k].multiplicity) ||
                        (MultiSet[i].Elem[j].multiplicity == 1 && MultiSet[i].Elem[k].multiplicity == 1))) ||
                    (MultiSet[i].Elem[j].code_num == MultiSet[i].Elem[k].code_num)) {
                    MultiSet[i].Elem[j].multiplicity += MultiSet[i].Elem[k].multiplicity;
                    for (int t = k; t < MultiSet[i].elem_count - 1; t++) {
                        MultiSet[i].Elem[t] = MultiSet[i].Elem[t + 1];
                    }
                    MultiSet[i].elem_count--;
                    k--;
                }
            }
        }
    }
}

void SymmDiff(Set MultiSet[]) {
    Set A = MultiSet[0];
    if (MultiSet[0].brackets_count == 0) {
        int n = 1;
        while (n < MultiSet[0].set_count) {
            Set A_B, B_A, AB;
            A_B.elem_count = 0;
            B_A.elem_count = 0;
            AB.elem_count = 0;
            int a_b = 0, b_a = 0, ab = 0;

            for (int i = 0; i < A.elem_count; i++) {
                bool the_same = false;
                for (int j = 0; j < MultiSet[n].elem_count; j++) {
                    if ((A.Elem[i].element == MultiSet[n].Elem[j].element) ||
                        (A.Elem[i].code_num == MultiSet[n].Elem[j].code_num)) {
                        int mcy = A.Elem[i].multiplicity - MultiSet[n].Elem[j].multiplicity;
                        if (mcy == 0) {
                            // Элементы полностью совпадают
                        }
                        else if (mcy > 0) {
                            A_B.Elem[a_b] = A.Elem[i];
                            A_B.Elem[a_b].multiplicity = mcy;
                            a_b++;
                            A_B.elem_count++;
                        }
                        else {
                            mcy *= -1;
                            B_A.Elem[b_a] = MultiSet[n].Elem[j];
                            B_A.Elem[b_a].multiplicity = mcy;
                            b_a++;
                            B_A.elem_count++;
                        }
                        the_same = true;
                        break;
                    }
                }
                if (!the_same) {
                    A_B.Elem[a_b] = A.Elem[i];
                    a_b++;
                    A_B.elem_count++;
                }
            }

            for (int i = 0; i < MultiSet[n].elem_count; i++) {
                bool the_same = false;
                for (int j = 0; j < A.elem_count; j++) {
                    if ((A.Elem[j].element == MultiSet[n].Elem[i].element) ||
                        (A.Elem[j].code_num == MultiSet[n].Elem[i].code_num)) {
                        the_same = true;
                        break;
                    }
                }
                if (!the_same) {
                    B_A.Elem[b_a] = MultiSet[n].Elem[i];
                    b_a++;
                    B_A.elem_count++;
                }
            }

            // Объединяем A_B и B_A в AB
            for (int i = 0; i < A_B.elem_count; i++) {
                AB.Elem[ab] = A_B.Elem[i];
                ab++;
                AB.elem_count++;
            }
            for (int i = 0; i < B_A.elem_count; i++) {
                AB.Elem[ab] = B_A.Elem[i];
                ab++;
                AB.elem_count++;
            }

            A = AB;
            n++;
        }

        cout << "\nРЕЗУЛЬТАТ ВЫЧИСЛЕНИЯ СИММЕТРИЧЕСКОЙ РАЗНОСТИ:\n\n\t{ ";
        for (int j = 0; j < A.elem_count; j++) {
            if (A.Elem[j].multiplicity == 1) {
                if (j != A.elem_count - 1) {
                    cout << A.Elem[j].element << ", ";
                }
                else {
                    cout << A.Elem[j].element;
                }
            }
            else {
                if (j != A.elem_count - 1) {
                    cout << A.Elem[j].multiplicity << A.Elem[j].element << ", ";
                }
                else {
                    cout << A.Elem[j].multiplicity << A.Elem[j].element;
                }
            }
        }
        cout << " }\n";
        MultiSet[0] = A;
    }
    else {
        cout << "Некорректный ввод!\n";
    }
}

void Do_Symm_Diff(Set MultiSet[], string path) {
    try {
        GetSets(MultiSet, path);
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
        return;
    }

    OneType(MultiSet);
    SeeSets(MultiSet);
    SymmDiff(MultiSet);
}