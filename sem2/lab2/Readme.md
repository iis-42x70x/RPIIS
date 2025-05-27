# Лабораторная работа №2
## Вариант №5
Написать код, формирующий все возможные подмножества данного множества (его булеан).
## Цели:
- Изучить теоретические основы работы с множествами, включая операцию построения булеана.
- Разработать и реализовать алгоритм генерации булеана для заданного множества.
- Протестировать программу на различных входных данных для проверки корректности работы.
- Проанализировать результаты, сопоставив их с ожидаемыми значениями.
- Создать модульные тесты (GoogleTests) для проверки функциональности программы.
## Основные понятия:
1. Множество — одно из ключевых понятий математики, представляющее собой набор, совокупность каких-либо объектов — элементов этого множества.
2. Подмножество — это множество, все элементы которого принадлежат другому множеству (называемому надмножеством).
3. Булеан данного множества — это множество всех возможных подмножеств , включая само множество и пустое множество.
   - Мощность булеана — это количество всех возможных подмножеств данного множества.

## Описание кода:
#### Parentheses
Проверяет баланс скобок {}, <>, () в строке. Возвращает true, если все скобки правильно закрыты, иначе false.
```
bool Parentheses(const string& input) {
    vector<char> stack;
    for (char c : input) {
        if (c == '{' || c == '<' || c == '(') stack.push_back(c);
        else if (c == '}' || c == '>' || c == ')') {
            if (stack.empty()) return false;
            char openBracket = stack.back();
            stack.pop_back();
            if ((c == '}' && openBracket != '{') ||
                (c == '>' && openBracket != '<') ||
                (c == ')' && openBracket != '(')) return false;
        }
    }
    return stack.empty();
```
#### Check_symbols
Проверяет, является ли символ допустимым (буквы, цифры, скобки, запятые, пробелы). Возвращает true, если символ разрешён.
```
bool Check_symbols(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
        (c >= '0' && c <= '9') || c == '{' || c == '}' ||
        c == '<' || c == '>' || c == '(' || c == ')' ||
        c == ',' || c == ' ';
}
```
#### check
Проверяет строку на корректность: все символы допустимы (Check_symbols) и скобки сбалансированы (Parentheses).
```
bool check(const string& input) {
    for (char c : input) {
        if (!Check_symbols(c)) {
            cerr << "Error: invalid character \"" << c << "\"" << endl;
            return false;
        }
    }
    return Parentheses(input);
}

```
#### Add
Разбивает строку input_str на элементы по запятым (учитывая вложенность скобок) и добавляет их в вектор Set. Возвращает 0 при успехе или 1 при ошибке (несбалансированные скобки).
```
int Add(vector<string>& Set, const string& input_str) {
    string currentElement;
    int braceCount = 0, angleCount = 0, roundCount = 0;

    for (char s : input_str) {
        if (s == '{') braceCount++;
        else if (s == '}') braceCount--;
        else if (s == '<') angleCount++;
        else if (s == '>') angleCount--;
        else if (s == '(') roundCount++;
        else if (s == ')') roundCount--;

        if (s == ',' && braceCount == 0 && angleCount == 0 && roundCount == 0) {
            if (!currentElement.empty()) {
                Set.push_back(currentElement);
                currentElement.clear();
            }
        }
        else {
            currentElement.push_back(s);
        }
    }

    if (!currentElement.empty()) Set.push_back(currentElement);
    return (braceCount == 0 && angleCount == 0 && roundCount == 0) ? 0 : 1;
}

```
#### Duplicate
Проверяет вектор на дубликаты. Возвращает 1, если найдены дубликаты, иначе 0.
```
int Duplicate(const vector<string>& set) {
    for (size_t i = 0; i < set.size(); i++) {
        for (size_t j = i + 1; j < set.size(); j++) {
            if (set[i] == set[j]) {
                cerr << "Error: duplicate element \"" << set[i] << "\"" << endl;
                return 1;
            }
        }
    }
    return 0;
}

```
#### Generate_Boolean
Рекурсивно генерирует все подмножества (булеан) исходного множества set и сохраняет их в boolean.
```
void Generate_Boolean(const vector<string>& set, vector<vector<string>>& boolean,
    vector<string>& el_of_boolean, int index) {
    boolean.push_back(el_of_boolean);
    for (size_t i = index; i < set.size(); i++) {
        el_of_boolean.push_back(set[i]);
        Generate_Boolean(set, boolean, el_of_boolean, i + 1);
        el_of_boolean.pop_back();
    }
}

```
#### RemoveOuterBraces
Удаляет внешние парные скобки {} или <> из строки, если они есть.
```
void RemoveOuterBraces(string& line) {
    if ((line.front() == '{' && line.back() == '}') ||
        (line.front() == '<' && line.back() == '>')) {
        line = line.substr(1, line.size() - 2);
    }
}

```
#### ProcessSetFromString
Обрабатывает строку с множеством.
```
void ProcessSetFromString(const string& input, vector<vector<string>>& result) {
    string noSpaces;
    for (char c : input) if (c != ' ') noSpaces += c;

    size_t equalPos = noSpaces.find('=');
    string line = (equalPos != string::npos) ? noSpaces.substr(equalPos + 1) : noSpaces;

    if (!check(line)) {
        cerr << "Structure error: " << line << endl;
        return;
    }

    RemoveOuterBraces(line);
    vector<string> set;
    vector<string> el_of_boolean;

    if (Add(set, line) || Duplicate(set)) return;
    Generate_Boolean(set, result, el_of_boolean, 0);
}

```

## Тесты:
#### Тест 1
Проверяет корректность валидации структуры множества функцией check().
##### Пример:
- `{a,b}` → валидная строка (ожидается true).
- `{a,!b}` → невалидная строка из-за символа ! (ожидается false).
#####  Цель:
Убедиться, что функция правильно определяет допустимые символы и структуру множества.

#### Тест 2
Проверяет корректность обработки множества и генерации булеана функцией ProcessSetFromString().
##### Пример:
1. Обрабатывает строку `{a,b}`.

2. Сортирует полученные подмножества и ожидаемый результат для сравнения.

- Количество подмножеств (должно быть 4).

- Совпадение с ожидаемым булеаном: `[], ["a"], ["b"], ["a", "b"] `

#####  Цель:
Проверить, что функция корректно разбирает множество и строит все возможные подмножества.

#### Тест 3
Проверяет обработку пустого множества {}.
##### Пример:
- Булеан пустого множества содержит только одно подмножество — пустое (размер result = 1).
#####  Цель:
Убедиться, что крайний случай с пустым множеством обрабатывается корректно.
1[{6641D2A6-B4C1-487B-ABF5-3683D72AB062}.png](https://github.com/iis-42x70x/RPIIS/blob/%D0%92%D0%B5%D0%B3%D0%B5%D1%80%D0%B0_%D0%9C/sem2/lab2/%7B6641D2A6-B4C1-487B-ABF5-3683D72AB062%7D.png)
## Источники: 
- [Google Tests](https://www.youtube.com/watch?v=bfCYGmWoIgQ&ab_channel=Learn2Code)
- [Булеан](https://www.youtube.com/watch?v=JJOydDeP5Ms&ab_channel=%D0%94%D0%B0%D0%BD%D0%B8%D0%BB%D0%9B%D0%B5%D0%B1%D0%B5%D0%B4%D0%B5%D0%B2)



