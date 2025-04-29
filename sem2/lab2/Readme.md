# Лабораторная работа №2

- `Цель` - нахождение пересечения множеств(без учета кратных вхождений элементов)
- `Задача` - реализовать алгоритм пересечения исходных множеств
- `Вариант` - $\textcolor{grey}{\textit{2}}$

## Список ключевых понятий (определения)

- `Пересечение множеств` - это множество, которому принадлежат те и только те элементы, которые одновременно принадлежат всем данным множествам.

- `Элментом множества` может являться число, кортеж, отдельное множество, сочетание буквы и числа.

## Алгоритм

В данном коде используется алгоритм пересечения множеств. Он выполняется следующим образом:

-Открывается файл с указанным путем.

-Инициализируются переменные, включая пустое множество result, флаг firstSet для отслеживания первого множества.

-Читается каждая строка из файла.

-Строка подвергается обрезке пробельных символов с помощью функции trim().

-Если строка содержит символ <, то она представляет собой кортеж множества. Внутри цикла происходит сборка элементов кортежа до тех пор, пока не встретится символ >. Затем собранный кортеж добавляется в текущее множество currentSet.

-Если строка не является кортежем, то элементы разделяются по запятой и добавляются в currentSet.

-Если это первое множество, оно становится результатом result.

-Если это не первое множество, происходит пересечение текущего множества currentSet с предыдущим результатом result. Результат пересечения сохраняется в intersectionSet.

-После обработки всех строк в файле, результат пересечения intersectionSet становится новым значением result.

-Файл закрывается, и возвращается итоговое пересечение множеств в виде result.

### Функция trim(const string& str):

```c++
string trim(const string& str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    size_t end = str.find_last_not_of(" \t\n\r");
    if (start == string::npos || end == string::npos) {
        return "";
    }
    return str.substr(start, end - start + 1);
}
```

### Функция itersection(const string& file_path) :

```c++
set<string> intersection(const string& file_path) {
    ifstream file(file_path);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл.";
        exit(-1);
    }

    string line;
    set<string> result;
    bool firstSet = true;

    while (getline(file, line)) {

        line = trim(line);
        line = line.substr(1, line.length() - 2);

        stringstream ss(line);
        set<string> currentSet;
        string element;

        while (getline(ss, element, ',')) {

            element = trim(element);


            if (element.find('<') != string::npos) {
                string tuple;
                while (element.find('>') == string::npos) {

                    tuple += element + ",";
                    getline(ss, element, ',');
                    element = trim(element);
                }
                tuple += element;
                currentSet.insert(tuple);
            }
            else {

                if (!element.empty()) {
                    currentSet.insert(element);
                }
            }
        }

        if (firstSet) {
            result = currentSet;
            firstSet = false;
        }
        else {
            set<string> intersectionSet;
            for (const string& elem : currentSet) {
                if (result.find(elem) != result.end()) {
                    intersectionSet.insert(elem);
                }
            }
            result = intersectionSet;
        }
    }

    file.close();
    return result;
}
```

## Вывод

Реализовала программу, которая выполняет пересечение множеств без учёта кратных вхождений элементов и возвращает итоговое пересечение.
