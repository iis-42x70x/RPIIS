# Лабораторная работа №2

##  Цель
- Исследовать свойства структуры данных "множество" и разработать библиотеку для выполнения операции над множеством.
- Изучить основы теории множеств и операций над ними.
  
##  Задача
`Вариант 8. Реализовать программу, формирующую без повторений всевозможные
неориентированные множества из элементов исходного неориентированного множества,
количество элементов в сформированных множествах должно быть равно исходному
натуральному n.`

##  Список ключевых понятий
---
- **Множество**– простейшая информационная конструкция и математическая структура,
позволяющая рассматривать какие-то объекты как целое, связывая их. Объекты, связываемые
некоторым множеством, называются элементами этого множества.


- **Неориентированное множество** — множество, порядок следования элементов которого не имеет значения.
Например, неориентированное множество, имеющее малое количество вхождений, может быть представлено в тексте в следующем виде:

`S = {a, b, a, a, c}.`

Элементы a, b и c принадлежат множеству с именем S, причём множество S имеет три вхождения элемента *a* и по одному вхождению элементов *b* и *c*

##  Описание алгоритма
1. Создание класса CombinationGenerator, который будет использоваться для генерации комбинаций.
2. Запрос у пользователя количества элементов в множестве.
3. Ввод элементов множества:
  - Запрос у пользователя ввода элементов множества;
   - Вводимые элементы добавляются в вектор elements.

4. Генерация перестановок:
Метод generatePermutations инициализирует вектор currentPermutation, который будет хранить текущую перестановку, и вектор used, который отслеживает, какие элементы уже были использованы.
Затем вызывается рекурсивный метод generatePermutationsRecursive.
Рекурсивная генерация перестановок:
В методе generatePermutationsRecursive проверяется, достигнута ли длина текущей перестановки (currentPermutation) равная количеству элементов (elementsCount).
Если да, то текущая перестановка выводится на экран.
Если нет, то продолжается процесс генерации.
Цикл по элементам:
Для каждого элемента в векторе elements проверяется, был ли он использован (согласно вектору used).
Если элемент не использован:
Он добавляется в текущую перестановку (currentPermutation).
Элемент помечается как использованный (used[i] = true).
Рекурсивно вызывается метод для продолжения генерации с обновленным состоянием.
После возвращения из рекурсии последний добавленный элемент удаляется из текущей перестановки (pop_back()), и его статус использования сбрасывается (used[i] = false).
Завершение:

Процесс продолжается до тех пор, пока не будут сгенерированы все возможные перестановки.
В коде реализация этого алгоритма выглядит так:

**Header.h**
```C++
#ifndef HEADER_H
#define HEADER_H

#include <vector>
#include <string>

class PermutationGenerator {
public:
    PermutationGenerator(int count);
    void readElements();
    void generatePermutations();

private:
    void generatePermutationsRecursive(std::vector<std::string>& currentPermutation, std::vector<bool>& used);

    int elementsCount;
    std::vector<std::string> elements; // Вектор для хранения элементов
};

#endif // HEADER_H
```
**CombinationGenerator.сpp**
```C++
#include "Header.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

PermutationGenerator::PermutationGenerator(int count) : elementsCount(count) {}

void PermutationGenerator::readElements() {
    for (int i = 0; i < elementsCount; ++i) {
        cout << "Введите элемент (буква или множество символов): ";
        string input;
        cin >> input;

        // Добавляем элемент в вектор
        elements.push_back(input);
    }
}

void PermutationGenerator::generatePermutations() {
    vector<string> currentPermutation;
    vector<bool> used(elementsCount, false); // Вектор для отслеживания использованных элементов
    generatePermutationsRecursive(currentPermutation, used);
}

void PermutationGenerator::generatePermutationsRecursive(vector<string>& currentPermutation, vector<bool>& used) {
    // Если текущая перестановка имеет нужный размер, выводим её
    if (currentPermutation.size() == elementsCount) {
        cout << "{ ";
        for (size_t i = 0; i < currentPermutation.size(); ++i) {
            cout << currentPermutation[i];
            if (i < currentPermutation.size() - 1) {
                cout << ", "; // Добавляем запятую между элементами
            }
        }
       
        cout << "}";
        cout << endl;
        return; // Возвращаемся, чтобы не продолжать генерировать дальше
    }

    // Генерируем новые перестановки
    for (int i = 0; i < elements.size(); ++i) {
        if (!used[i]) { // Если элемент еще не использован
            currentPermutation.push_back(elements[i]); // Добавляем элемент в текущую перестановку
            used[i] = true; // Отмечаем элемент как использованный

            generatePermutationsRecursive(currentPermutation, used); // Рекурсивный вызов

            currentPermutation.pop_back(); // Убираем последний элемент для следующей итерации
            used[i] = false; // Сбрасываем отметку о использовании элемента
        }
    }
}
```
##  Вывод
В ходе лабораторной работы была реализована программа, формирующая без повторений всевозможные неориентированные множества из элементов исходного неориентированного множества, количество элементов в сформированных множествах которого должно быть равно исходному натуральному n, а также был реализован алгоритм формирования неповторяющихся перестановок исходного множества.
##  Источники
https://ejudge.179.ru/tasks/cpp/total/241.html

[drive.google](https://drive.google.com/drive/folders/1SLcF9njDTaNUacXMA9Nrqm7FUS7MnNsI)
[github.com](https://github.com/iis-32170x/RPIIS/tree/main/sem2)
