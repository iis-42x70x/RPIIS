#pragma once
#include <string>
#include <fstream>
#include <set>

struct superset
{
	std::set<std::string> elem;
	std::set<superset> mnoj;
	bool posled;
    bool operator<(const superset& other) const { //перегрузка оператора <
        // Сначала сравниваем элементы
        if (posled != other.posled) {
            return posled < other.posled;  // {..} < <..> (если posled=false для {..})
        }
        if (elem != other.elem) {
            return elem < other.elem;
        }
        // Если элементы равны, сравниваем подмножества
        return mnoj < other.mnoj;
    }
   /* bool operator==(const superset& other) const {
        if (!posled == other.posled) {
            if (!(elem == other.elem)) {
                if (!mnoj.empty() && !other.mnoj.empty()) {
                    return mnoj == other.mnoj;
                }
                else if (mnoj.empty() && other.mnoj.empty()) {
                    return true;
                }
                else return false;
            }
            else return false; /// гойда
        }
        else return false;
    }*/

    bool operator==(const superset& other) const {// перегрузка оператора ==
       /* std::cout << "Comparing: " << this << " with " << &other << "\n";*/
        // 1. Сравниваем тип множества
        if (posled != other.posled) {
            return false;
        }

        // 2. Сравниваем простые элементы
        if (elem != other.elem) {
            return false;
        }

        // 3. Сравниваем вложенные множества
        if (mnoj.size() != other.mnoj.size()) {
            return false;
        }
        else return mnoj == other.mnoj;

        return true;
    }
   /* bool operator!=(const superset& other) const {
        if (!posled == other.posled) {
            if (!(elem == other.elem)) {
                if (!mnoj.empty() && !other.mnoj.empty()) {
                    return mnoj == other.mnoj;
                }
                else if (mnoj.empty() && other.mnoj.empty()) {
                    return false;
                }
                else return true;
            }
            else return true; /// гойда
        }
        else return true;
    }*/
};
void custom_set_difference(const std::set<std::string>& a,
    const std::set<std::string>& b,
    std::set<std::string>& result);
int poisknachala(std::string stroka);//принимает строку и ищет первую { или <
void pereborSET(std::string stroka, int& kolvo);//принимает строку множества и 0 в виде переменной
std::string convertsettostring(const superset& sett);//принимает структуру superset и преобразует обратно в string
void insertmnoj(superset& sett, const std::string& stroka, int& pos);// принимает структуру superset и строку в виде множества (+ позиция первой { или <) , вставляет строку в структуру superset
superset raznost(const superset& a, const superset& b);// рекурсивно ищет разность двух множеств в виде стркутуры superset
superset raznost2(const superset& a, const superset& b);//ищет разность двух множеств в виде структуры superset