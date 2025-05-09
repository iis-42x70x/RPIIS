//Поддерживает добавление, вывод, сравнение и копирование.

//для вложенных кортежей

#ifndef TUPLE_HPP
#define TUPLE_HPP

#include <vector>
#include <variant>
#include <iostream>

template <typename T>
struct Set;  // Предварительное объявление для множества

template <typename T>
struct Tuple {
    using TupleElement = std::variant<T, Tuple<T>, Set<T>>;  //TupleElement — это элемент, который может быть одним из трёх типов
    std::vector<TupleElement> items;  //список (vector) таких элементов.

    // Добавление элемента в кортеж
    void append(const TupleElement& newItem) {
        items.push_back(newItem);
    }

    // Получение количества элементов
    const int itemCount() const {
        return this->items.size();
    }

    // Оператор присваивания; Позволяет копировать один кортеж в другой
    Tuple& operator=(const Tuple &otherTuple) {
        if (this != &otherTuple) {
            this->items = otherTuple.items;
        }
        return *this;
    }
};

// Вывод кортежа в поток
template<typename T>
std::ostream& operator<<(std::ostream &outputStream, const Tuple<T> &tupleToPrint) {
    outputStream << "< ";
    for (size_t i = 0; i < tupleToPrint.items.size(); i++) { //Проходит по каждому элементу в items.
        try {
            // Попытка получить простой элемент
            T simpleItem = std::get<T>(tupleToPrint.items[i]); //Сначала пробует напечатать как обычное значение
            outputStream << simpleItem;
        } catch (const std::bad_variant_access &) {
            try {
                // Попытка получить вложенное множество
                Set<T> nestedSet = std::get<Set<T>>(tupleToPrint.items[i]);
                outputStream << nestedSet;
            } catch (const std::bad_variant_access &) {
                // Попытка получить вложенный кортеж
                Tuple<T> nestedTuple = std::get<Tuple<T>>(tupleToPrint.items[i]);
                outputStream << nestedTuple;
            }
        }
        if(i != tupleToPrint.items.size()-1)
            outputStream << ", ";
    }
    outputStream << " >";
    return outputStream;
}

// Сравнение кортежей
template<typename T>
bool operator==(const Tuple<T>& firstTuple, const Tuple<T>& secondTuple) {
    if (firstTuple.items.size() != secondTuple.items.size()) //Сначала проверяет, что у них одинаковый размер 
        return false;
    
    for(size_t i = 0; i < firstTuple.items.size(); i++) { //Потом сравнивает поэлементно
        if(!(firstTuple.items[i] == secondTuple.items[i]))
            return false;
    }
    return true;//Возвращает true, если они полностью идентичны.
}

#endif