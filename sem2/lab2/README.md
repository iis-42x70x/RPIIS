# Лабораторная работа №2
## Цель: 
Реализовать программу, формирующую множество равное симметрической разности произвольного количества исходных множеств (с учётом кратных вхождений элементов).

## Определения:
_Симметрическая разность_ - неориентированных множеств A и B с учётом кратных
вхождений элементов будем называть неориентированное множество S тогда и только тогда,
когда для любого x истинно S|x| = max{A|x|-B|x|, B|x|-A|x|}.

# Реализация

## Функция ```extractAndSortElements```
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
