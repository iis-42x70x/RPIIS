/*Вставка элемента.
Получение размера.
Вывод на экран.
Сравнение по содержимому.
*/
#ifndef SETS_HPP
#define SETS_HPP

#include <vector> //динамический массив
#include <variant> //позволяет хранить значения разных типов в одном объекте
#include <iostream>
#include <algorithm> //для алгоритмов STL 

template <typename T>
struct Tuple;  //предварительное объявление шаблонной структуры Tuple<T>

//Основная структура — Set<T>
template <typename T>
struct Set {
    using SetElement = std::variant<T, Tuple<T>, Set<T>>; //T — обычный элемент множества. Tuple<T> — кортеж. Set<T> — вложенное множество.
    std::vector<SetElement> members;

    void insert(const SetElement& newElement) {
        members.push_back(newElement);
    } //Добавляет элемент (T, Tuple<T> или Set<T>) во множество.

    const int size() const {
        return this->members.size();
    } //Возвращает количество элементов во множестве.

    Set& operator=(const Set &otherSet) {
        if (this != &otherSet) {
            this->members = otherSet.members;
        }
        return *this;
    } //Позволяет присваивать одно множество другому, копируя его элементы (если объекты разные).
};

//Этот оператор выводит множество в поток (например, на экран)
template<typename T>
std::ostream& operator<<(std::ostream &outputStream, const Set<T> &setToPrint) {
    outputStream << "{ ";
    for (size_t i = 0; i < setToPrint.members.size(); i++) { //Перебирает все элементы members.
        try {
            T basicElement = std::get<T>(setToPrint.members[i]);
            outputStream << basicElement; //Пытается извлечь: Сначала T            
        } catch (const std::bad_variant_access &) {
            try { //Если не получилось (ошибка bad_variant_access), пробует Set<T>
                Set<T> nestedSet = std::get<Set<T>>(setToPrint.members[i]);
                outputStream << nestedSet;
            } catch (const std::bad_variant_access &) { //Если снова ошибка — пробует Tuple<T>
                Tuple<T> nestedTuple = std::get<Tuple<T>>(setToPrint.members[i]);
                outputStream << nestedTuple;
            }
        }
        if(i != setToPrint.members.size()-1) //Выводит элементы через запятую
            outputStream << ", ";
    }
    outputStream << " }";
    return outputStream;
}

//Оператор сравнения ==
template<typename T>
bool operator==(const Set<T>& firstSet, const Set<T>& secondSet) {
    if (firstSet.members.size() != secondSet.members.size()) return false;
    //Сравнивает два множества поэлементно. Они считаются равными, если:
    for(size_t i = 0; i < firstSet.members.size(); i++) { //Они считаются равными, если: 
        bool elementFound = false;
        for(size_t j = 0; j < secondSet.members.size(); j++) {
            if(firstSet.members[i] == secondSet.members[j]) {
                elementFound = true;
                break;
            }
        }
        if(!elementFound)
            return false;
    }
    return true;
}

#endif