//описана сама реализация нахождения симметричной разности 2-х множеств

#ifndef simdiff_HPP
#define simdiff_HPP

//подключаю ранее созданные структуры Set<T> и Tuple<T>.
#include "Sets.hpp" 
#include "Tuple.hpp"

template<typename T>
Set<T> Difference(Set<T> a, Set<T> b) //Возвращает множество Set<T>, состоящее из элементов, которые: есть в a, но нет в b
{
	Set<T> s; //// результат (A\B)
	
    for(size_t i = 0; i < a.size(); i++){ //Проходим по каждому элементу a
        bool foundInB = false;
        for(size_t j = 0; j < b.size(); j++){
            if(a.members[i] == b.members[j]){ //Для каждого элемента ищем — есть ли такой же в b
                foundInB = true;
                break;
            }
        }
        if(!foundInB)
            s.insert(a.members[i]); //Если не нашли (foundInB == false) — добавляем в s
    }
	
	return s; //Возвращаем множество с теми элементами, которые только в a, но не в b.
}

// Симметрическая разность: (A \ B) ∪ (B \ A)
template<typename T>
Set<T> SymmetricDifference(Set<T> a, Set<T> b)
{
    Set<T> diff1 = Difference(a, b);  // элементы только из A
    Set<T> diff2 = Difference(b, a);  // элементы только из B

    Set<T> result;

    // Вставляем все из первого множества
    for (const auto& el : diff1.members) {
        result.insert(el);
    }
    // Вставляем все из второго множества
    for (const auto& el : diff2.members) {
        result.insert(el);
    }

    return result;
}

#endif

