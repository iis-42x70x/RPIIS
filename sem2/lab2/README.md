# Лабораторная работа №2
## Цель: 
Разработать программу для нахождения пересечения N множеств(без учета кратности).Написать для нее тесты.

## Определения:
_Объединение_ - это множество A ∪ B состоящее из всех элементов исходных множеств A и B вместе. То есть в объединение попадут вообще все элементы, которые были хотя бы в одном из исходных множеств. В объединение входят все элементы, которые встречались в множествах по отдельности, но только по одному разу.

# Реализация

## Функция ```extractAndSortElements```
```c++
    vector<string> extractAndSortElements(const string& setString) {
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
                elements.push_back(currentElement);
                currentElement.clear();
            }
        }
        else if (c == ',' && braceDepth == 0) {
            if (!currentElement.empty()) {
                elements.push_back(currentElement);
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
        elements.push_back(currentElement);
    }
    return elements;
}
```
Функция ```extractAndSortElements``` принимает строку ```setString``` и извлекает из нее элементы, разделенные запятыми, учитывая вложенные фигурные скобки {}. Извлеченные элементы возвращаются в виде вектора строк (```vector<string>```) в порядке их появления в строке.

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
