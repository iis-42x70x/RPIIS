# Лабораторная работа №2
## Цель: 
Реализовать программу, формирующую множество равное симметрической разности произвольного количества исходных множеств (с учётом кратных вхождений элементов).

## Определения:
_Симметрическая разность_ - неориентированных множеств A и B с учётом кратных
вхождений элементов будем называть неориентированное множество S тогда и только тогда,
когда для любого x истинно S|x| = max{A|x|-B|x|, B|x|-A|x|}.

# Реализация


## Функция ```readSet```
```c++
Element* readSet(int& count) {
    std::cout << "Введите количество элементов в множестве: ";
    std::cin >> count;
    
    Element* elements = new Element[count];
    for (int i = 0; i < count; i++) {
        std::cout << "Элемент " << i+1 << " - число (1) или множество (2)? ";
        int choice;
        std::cin >> choice;
        
        if (choice == 1) {
            int val;
            std::cout << "Введите значение: ";
            std::cin >> val;
            elements[i] = Element(val);
        } else {
            int subCount;
            Element* subElements = readSet(subCount);
            elements[i] = Element(subElements, subCount);
            delete[] subElements;
        }
    }
    return elements;
}

```
Эта функция рекурсивно считывает множество элементов, где каждый элемент может быть либо числом, либо вложенным множеством. Она создает и возвращает массив элементов Element.

## Функция ```calculateSymmetricDifference```
```c++
Element* calculateSymmetricDifference(Element** sets, int* counts, int setCount, int& resultCount) {
    if (setCount == 0) {
        resultCount = 0;
        return nullptr;
    }

    Element* currentDiff = new Element[counts[0]];
    for (int i = 0; i < counts[0]; i++) {
        currentDiff[i] = sets[0][i];
    }
    int currentCount = counts[0];

    for (int i = 1; i < setCount; i++) {
        Element* temp = new Element[currentCount + counts[i]];
        int tempCount = 0;

        for (int j = 0; j < currentCount; j++) {
            if (!contains(sets[i], counts[i], currentDiff[j])) {
                temp[tempCount++] = currentDiff[j];
            }
        }

        for (int j = 0; j < counts[i]; j++) {
            if (!contains(currentDiff, currentCount, sets[i][j])) {
                temp[tempCount++] = sets[i][j];
            }
        }

        delete[] currentDiff;
        currentDiff = temp;
        currentCount = tempCount;
    }

    Element* result = new Element[currentCount];
    resultCount = 0;
    for (int i = 0; i < currentCount; i++) {
        if (!contains(result, resultCount, currentDiff[i])) {
            result[resultCount++] = currentDiff[i];
        }
    }

    delete[] currentDiff;
    return result;
}

```

Функция ```calculateSymmetricDifference``` объединяет два множества, оставляя только уникальные элементы, которые есть либо в первом, либо во втором, но не в обоих сразу. Результат сохраняется в новое множество и может быть выведен или использован дальше.
## Пример работы программы
![{0701CE8C-0CF8-433E-BA5C-DD653BB62794}](https://github.com/user-attachments/assets/37f84dc9-ac72-43b0-8d44-ac98c9d2e04c)

