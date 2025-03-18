# Лабораторная работа №2
## Цель: 
Разработать программу для нахождения пересечения N множеств(без учета кратности).Написать для нее тесты.

## Определения:
_Объединение_ - это множество A ∪ B состоящее из всех элементов исходных множеств A и B вместе. То есть в объединение попадут вообще все элементы, которые были хотя бы в одном из исходных множеств. В объединение входят все элементы, которые встречались в множествах по отдельности, но только по одному разу.

# Реализация
## Функция сортировки  ```bubbleSort```
```c++
void bubbleSort(vector<string>& items) {
    int count = items.size();
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (items[j] > items[j + 1]) {
                string temp = items[j];
                items[j] = items[j + 1];
                items[j + 1] = temp;
            }
        }
    }
}
```
Сравнивает соседние элементы и меняет их местами, если первый больше второго, повторяет это несколько раз, пока всё не отсортируется.
## Функция ```sortSubset```

```c++
 string sortSubset(const string& subset) {
    if (subset.front() != '{' || subset.back() != '}') {
        return subset;
    }
    string content = subset.substr(1, subset.size() - 2);
    vector<string> elements;
    string currentElement;
    int braceDepth = 0;


    for (char c : content) {
        if (c == '{' && braceDepth == 0) {
            braceDepth++;
            currentElement += c;
        }
        else if (c == '}' && braceDepth > 0) {
            braceDepth--;
            currentElement += c;
            if (braceDepth == 0 && !currentElement.empty()) {
                elements.push_back(sortSubset(currentElement));
                currentElement.clear();
            }
        }
        else if (c == ',' && braceDepth == 0) {
            if (!currentElement.empty()) {
                elements.push_back(sortSubset(currentElement));
                currentElement.clear();
            }
        }
        else {
            currentElement += c;
            if (c == '{') braceDepth++;
            else if (c == '}') braceDepth--;
        }
    }
    if (!currentElement.empty()) {
        elements.push_back(sortSubset(currentElement));
    }


    bubbleSort(elements);


    string sortedSubset = "{";
    for (int i = 0; i < elements.size(); i++) {
        sortedSubset += elements[i];
        if (i < elements.size() - 1) {
            sortedSubset += ",";
        }
    }
    sortedSubset += "}";
    return sortedSubset;
}
```

Сортирует элементы внутри строки, которая представляет множество, включая вложенные множества. Проверяет, есть ли {} в начале и конце строки. Если да, извлекает содержимое, разбивает на элементы (учитывая вложенность), сортирует их и собирает обратно в строку с {}.
## Функция ```extractAndSortElements```
```c++
    vector<string> elements;
    string currentElement;
    int braceDepth = 0;

    for (char c : setString) {
        if (c == '{' && braceDepth == 0) {
            braceDepth++;
            currentElement += c;
        }
        else if (c == '}' && braceDepth > 0) {
            braceDepth--;
            currentElement += c;
            if (braceDepth == 0 && !currentElement.empty()) {
                elements.push_back(sortSubset(currentElement));
                currentElement.clear();
            }
        }
        else if (c == ',' && braceDepth == 0) {
            if (!currentElement.empty()) {
                elements.push_back(sortSubset(currentElement));
                currentElement.clear();
            }
        }
        else {
            currentElement += c;
            if (c == '{') braceDepth++;
            else if (c == '}') braceDepth--;
        }
    }
    if (!currentElement.empty()) {
        elements.push_back(sortSubset(currentElement));
    }
    return elements;
}
```
Извлекает элементы из строки-множества и возвращает их в виде отсортированного вектора. Проходит по символам строки, собирает элементы (учитывая скобки), рекурсивно сортирует их с помощью ```sortSubset``` и возвращает вектор.

## Функция ```unionSets```

```c++
  void unionSets(vector<string>& sets, string& initialResult) {
    if (sets.size() == 0) return;

    vector<string> uniqueElements;


    for (int i = 0; i < sets.size(); i++) {
        vector<string> elements = extractAndSortElements(sets[i]);
        for (const string& element : elements) {
            bool isDuplicate = false;
            for (const string& existingElement : uniqueElements) {
                if (existingElement == element) {
                    isDuplicate = true;
                    break;
                }
            }
            if (!isDuplicate) {
                uniqueElements.push_back(element);
            }
        }
    }


    string finalResult;
    for (int i = 0; i < uniqueElements.size(); i++) {
        finalResult += uniqueElements[i];
        if (i < uniqueElements.size() - 1) {
            finalResult += ",";
        }
    }

    cout << "Результат объединения:" << endl;
    cout << "{" << finalResult << "}" << endl;
    initialResult = "{" + finalResult + "}";
}
```
Объединяет все множества из вектора, убирая дубликаты, и сохраняет результат в строку. Для каждого множества извлекает элементы, проверяет их на уникальность, собирает в одну строку и выводит на экран, а также записывает в ```initialResult```.
## Пример работы программы
![{0701CE8C-0CF8-433E-BA5C-DD653BB62794}](https://github.com/user-attachments/assets/37f84dc9-ac72-43b0-8d44-ac98c9d2e04c)
Вывод: Реализована программа объединения произвольного количества множеств без учета кратного вхождения.
