# Лабораторная работа №2. Множества
## Цель работы
- Научиться работать с множествами.
- Научиться разрабатывать алгоритмы выполнения операций над множествами.
## Задачи
- Разработать алгоритм одной из операций над множествами.
- Разработать систему тестов, которые продемонстрировали бы работоспособность реализованного алгоритма.
## Вариант
12 вариант. Нужно реализовать алгоритм вычисления симметрической разности N множеств.
## Список используемых при решении задачи понятий
- Множество – одно из ключевых понятий математики, представляющее собой набор, совокупность объектов любой природы.
- Элементы множества – объекты, составляющие множество.
- Объект принадлежит множеству тогда и только тогда, когда он является его элементом.
- Говорят, что если объект принадлежит множеству, то существует вхождение этого элемента в множество. Допускается неограниченное количество вхождений
одного объекта в какое-либо множество.
- Например, есть множество _S = {a, b, a, a, c}_. В нём элементы _a_, _b_ и _c_ принадлежат множеству _S_, причём множество _S_ имеет три вхождения элемента _a_ (_S|a|_ = 3) и по одному вхождению элементов _b_ и _c_ (_S|b|_ = _S|c|_ = 1).
- Множеством с кратными вхождениями элементов называют множество _S_ тогда и только тогда, когда существует _x_ такой, что истинно _S|x|_ > 1.
- __Симметрической разностью__ множеств _A_ и _B_ с учётом кратных вхождений элементов будем называть множество _S_ тогда и только тогда, когда для любого _x_ истинно _S|x| = max{A|x|-B|x|, B|x|-A|x|}_. Выражение можно упростить: для любого _x_ истинно _S|x| = |A|x|-B|x||_ (модуль разности кратностей _x_ в множествах A и B).
## Реализация
Заголовочные файлы и константы:
- Подключены необходимые библиотеки для работы с файлами, памятью и алгоритмами
- Определены константы для имен входного и выходного файлов
```C++
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>

using namespace std;

const char* input_filename = "input.txt";
const char* output_filename = "output.txt";
```
Структура данных:
- Структура __IntSet__ представляет множество целых чисел: __elements__ - динамический массив элементов множества; __size__ - количество элементов в множестве
```C++
struct IntSet {
    int* elements;
    int size;
};
```
Чтение данных из файла:
- Открывает файл и читает количество множеств
- Выделяет память под массив структур __IntSet__
- Для каждого множества считывает количество элементов и сами элементы
- В случае ошибки освобождает выделенную память и возвращает __false__
- При успешном чтении возвращает __true__
```C++
bool readSetsFromFile(const char* filename, IntSet** sets, int* setCount) {
    ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    if (!(file >> *setCount) || *setCount <= 0) {
        file.close();
        return false;
    }

    *sets = (IntSet*)malloc(*setCount * sizeof(IntSet));
    if (*sets == nullptr) {
        file.close();
        return false;
    }

    for (int i = 0; i < *setCount; i++) {
        int k;
        if (!(file >> k) || k < 0) {
            for (int j = 0; j < i; j++) {
                free((*sets)[j].elements);
            }
            free(*sets);
            file.close();
            return false;
        }

        (*sets)[i].size = k;
        (*sets)[i].elements = (int*)malloc(k * sizeof(int));
        if (k > 0 && (*sets)[i].elements == nullptr) {
            for (int j = 0; j < i; j++) {
                free((*sets)[j].elements);
            }
            free(*sets);
            file.close();
            return false;
        }

        for (int j = 0; j < k; j++) {
            if (!(file >> (*sets)[i].elements[j])) {
                free((*sets)[i].elements);
                for (int m = 0; m < i; m++) {
                    free((*sets)[m].elements);
                }
                free(*sets);
                file.close();
                return false;
            }
        }
    }

    file.close();
    return true;
}
```
Вычисление симметрической разности:
- Объединяет все элементы из всех множеств в один массив
- Сортирует объединенный массив для последующей обработки
- Подсчитывает количество вхождений каждого уникального элемента
- Формирует результат, включая только элементы с нечетным количеством вхождений
- Сохраняет результат в структуру __result__
```C++
void symmetricDifference(IntSet* sets, int setCount, IntSet* result) {
    int totalElements = 0;
    for (int i = 0; i < setCount; i++) {
        totalElements += sets[i].size;
    }

    if (totalElements == 0) {
        result->size = 0;
        result->elements = nullptr;
        return;
    }

    int* allElements = (int*)malloc(totalElements * sizeof(int));
    if (allElements == nullptr) {
        result->size = 0;
        result->elements = nullptr;
        return;
    }

    int pos = 0;
    for (int i = 0; i < setCount; i++) {
        for (int j = 0; j < sets[i].size; j++) {
            allElements[pos++] = sets[i].elements[j];
        }
    }

    sort(allElements, allElements + totalElements);

    int* uniqueElements = (int*)malloc(totalElements * sizeof(int));
    int* counts = (int*)malloc(totalElements * sizeof(int));
    if (uniqueElements == nullptr || counts == nullptr) {
        free(allElements);
        free(uniqueElements);
        free(counts);
        result->size = 0;
        result->elements = nullptr;
        return;
    }

    int uniqueCount = 0;
    if (totalElements > 0) {
        uniqueElements[0] = allElements[0];
        counts[0] = 1;
        uniqueCount = 1;
    }

    for (int i = 1; i < totalElements; i++) {
        if (allElements[i] == allElements[i - 1]) {
            counts[uniqueCount - 1]++;
        }
        else {
            uniqueElements[uniqueCount] = allElements[i];
            counts[uniqueCount] = 1;
            uniqueCount++;
        }
    }

    int resultSize = 0;
    for (int i = 0; i < uniqueCount; i++) {
        if (counts[i] % 2 != 0) {
            resultSize++;
        }
    }

    result->size = resultSize;
    result->elements = (int*)malloc(resultSize * sizeof(int));
    if (result->elements == nullptr && resultSize > 0) {
        free(allElements);
        free(uniqueElements);
        free(counts);
        result->size = 0;
        return;
    }

    int resultPos = 0;
    for (int i = 0; i < uniqueCount; i++) {
        if (counts[i] % 2 != 0) {
            result->elements[resultPos++] = uniqueElements[i];
        }
    }

    free(allElements);
    free(uniqueElements);
    free(counts);
}
```
Запись результата в файл:
- Открывает выходной файл
- Записывает элементы результирующего множества через пробел
- Если множество пустое, записывает "Empty set"
- Возвращает __false__ при ошибке открытия файла, иначе __true__
```C++
bool writeResultToFile(const char* filename, const IntSet* result) {
    ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    if (result->size == 0) {
        file << "Empty set";
    }
    else {
        for (int i = 0; i < result->size; i++) {
            if (i > 0) file << " ";
            file << result->elements[i];
        }
    }

    file.close();
    return true;
}
```
Главная функция:
- Объявляет необходимые переменные
- Вызывает функции чтения, обработки и записи данных
- Обрабатывает ошибки ввода/вывода
- Освобождает выделенную память перед завершением программы
```C++
int main() {
    IntSet* sets = nullptr;
    int setCount = 0;
    IntSet result;

    if (!readSetsFromFile(input_filename, &sets, &setCount)) {
        ofstream out(output_filename);
        out << "Invalid input";
        out.close();
        return 1;
    }

    symmetricDifference(sets, setCount, &result);

    if (!writeResultToFile(output_filename, &result)) {
        for (int i = 0; i < setCount; i++) {
            free(sets[i].elements);
        }
        free(sets);
        free(result.elements);
        return 1;
    }

    for (int i = 0; i < setCount; i++) {
        free(sets[i].elements);
    }
    free(sets);
    free(result.elements);

    return 0;
}
```
Так же я протестировал программу на 10 тестовых примерах:
```
Тестовый пример №1:
Входные данные:
2
3 { 1, 2, 3 }
3 { 2, 3, 4 }
Выходные данные:
{ 1, 4 }

Тестовый пример №2:
Входные данные:
3
0 { }
0 { }
0 { }
Выходные данные:
Empty set

Тестовый пример №3:
Входные данные:
3
2 { 10, 20 }
3 { 20, 30, 40 }
2 { 30, 10 }
Выходные данные:
{ 40 }

Тестовый пример №4:
Входные данные:
4
2 { 5, 10 }
1 { 5 }
3 { 5, 7, 8 }
2 { 5, 9 }
Выходные данные:
{ 7, 8, 9, 10 }

Тестовый пример №5:
Входные данные:
2
3 { a, b, c }
5 { c, a, b, e, e }
Выходные данные:
{ e, e }

Тестовый пример №6:
Входные данные:
1
1 { { 1, 2 } }
Выходные данные:
{ { 1, 2 } }

Тестовый пример №7:
Входные данные:
1
2 { 1, 2 }
Выходные данные:
{ 1, 2 }

Тестовый пример №8:
Входные данные:
2
2 { 1, { 1, 2 } }
2 { { 1, 2 }, 1 }
Выходные данные:
{ }

Тестовый пример №9:
Входные данные:
3
7 { 1, 1, 2, 5, 5, 5, 6 }
9 { 2, 2, 2, 4, 4, 5, 5, 6, 7 }
5 { 3, 4, 7, 9, 15 }
Выходные данные:
{ 1, 1, 2, 2, 3, 4, 5, 9, 15 }

Тестовый пример №10:
Входные данные:
2
1 { < 1, 2 > }
1 { < 2, 1 > }
Выходные данные:
{ < 1, 2 >, < 2, 1 > }

Тестовый пример №11:
Входные данные:
2
2 { { 1, { 2, 3 } }, { 4, { 5, 6 } } }
3 { { 4, { 5, 6 } }, { 7, { 8 } }, { 1, { 2, 3 } } }
Выходные данные:
{ { 7, { 8 } } }

Тестовый пример №12:
Входные данные:
2
1 { { { 1, 2 }, { 3, 4 } } }
1 { { { 3, 4 }, { 5, 6 } } }
Выходные данные:
{ { { 1, 2 }, { 3, 4 } }, { { 3, 4 }, { 5, 6 } } }

Тестовый пример №13:
Входные данные:
1
3 { 1, 2, 3
Выходные данные:
Invalid input

Тестовый пример №14:
Входные данные:
1
3 { 1,, 2, 3 }
Выходные данные:
Invalid input

Тестовый пример №15(Некорректный ввод — несоответствие размеров):
Входные данные:
2
3 { 1, 2, 3 }
5 { 1, 2, 3, 4 }
Выходные данные:
Invalid input
```
Все тесты были успешно пройдены
## Вывод
В ходе данной лабораторной работы я:
- Научился работать с множествами
- Научиться разрабатывать алгоритмы выполнения операций над множествами.
