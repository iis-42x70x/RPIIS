# Лабораторная работа №1
**Вариант №2** (Множество. Добавление элемента во множество. Удаление элемента из
множества. Поиск элемента во множестве. Объединение двух
множеств. Пересечение двух множеств).

## Цели лабораторной работы:
1. Разработать библиотеку для работы с множеством на выбранном языке программирования (например, C/C++, Java, Python).
2. Создать тестовую программу для демонстрации функциональности разработанной библиотеки.
3. Обеспечить обработку некорректных данных, предусмотрев корректное завершение программы при возникновении ошибок.
4. Составить отчет по выполнению лабораторной работы.
5. Разработать систему тестов для проверки работоспособности и корректности библиотеки.
## Задачи лабораторной работы
1. Изучить спецификацию задачи по работе с множествами.
2. Выбрать язык программирования для реализации библиотеки (например, C++, Java, Python) в соответствии с индивидуальным заданием.
3. Разработать и реализовать библиотеку для работы с элементами, включая операции вставки и удаления элементов.
4. Написать тестовую программу, которая демонстрирует основные сценарии использования библиотеки.
5. Провести тестирование разработанной библиотеки, убедившись в ее правильной работе на различных входных данных.
6. Составить подробный отчет, включая описание решения задачи, архитектуру библиотеки, результаты тестирования и выводы.
7. Разработать систему тестов, включающую тест-кейсы для проверки различных аспектов работы библиотеки, включая корректность, производительность и обработку ошибок.
## Список используемых понятий:
**Множество** – это структурированный тип данных, представляющий собой набор взаимосвязанных по какому-либо признаку или группе признаков неповторяющихся объектов, которые можно рассматривать как единое целое.

**Рекурсия** - метод программирования, при котором функция вызывает сама себя для решения подзадачи.

**Пересечение** - A ∩ B двух множеств A и B состоит из элементов, которые принадлежат обоим исходным множествам.

**Объединение** - A ∪ B состоит из всех элементов исходных множеств A и B вместе. То есть в объединение попадут вообще все элементы, которые были хотя бы в одном из исходных множеств.

## Описание используемых алгоритмов:
1. **Алгоритм нормализации строки**
   Этот алгоритм выполняет нормализацию строкового представления множества, приводя его к стандартной форме.
   ```cpp
    std::string normalize(const std::string& s) {
        if (s.empty() || s[0] != '{') return s;

        std::vector<std::string> elements;
        int i = 1;

        while (i < s.size() - 1) {
            if (s[i] == '{') {
                int balance = 1;
                int j = i + 1;
                
                while (j < s.size() && balance > 0) {
                    if (s[j] == '{') balance++;
                    else if (s[j] == '}') balance--;
                    j++;
                }
                std::string nested = s.substr(i, j - i);
                elements.push_back(normalize(nested));
                i = j;
            }
            else if (s[i] != ',' && s[i] != ' ') {
                elements.push_back(std::string(1, s[i]));
                i++;
            }
            else {
                i++;
            }
        }

        std::sort(elements.begin(), elements.end());

        std::string result = "{";
        for (size_t k = 0; k < elements.size(); ++k) {
            if (k != 0) result += ",";
            result += elements[k];
        }
        result += "}";

        return result;
    }

2. **Алгоритм проверки наличия элемента**
   Этот алгоритм проверяет наличие элемента в множестве.
      ```cpp
    bool contains(const std::string& element) {
        std::string normElement = normalize(element);
        Node* current = head;
        while (current != nullptr) {
            if (normalize(current->value) == normElement) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
    bool find(const std::string& str) {
        return contains(str);
    }
4. **Алгоритм добавления элементов**
   Этот алгоритм добавляет элементы из строки
   ```cpp
   void push(std::string str) {
        int n = 0;
        std::string s;

        for (int i = 1; i < str.size() - 1; ++i) {
            if (str[i] == ' ') continue;
            if (str[i] == ',' && n == 0) continue;

            if (n == 0 && str[i] != '{' && str[i] != '}') {
                std::string elem(1, str[i]);
                if (!contains(elem)) {
                    Node* new_node = new Node;
                    new_node->value = elem;
                    new_node->next = nullptr;

                    if (head == nullptr) {
                        head = new_node;
                    }
                    else {
                        Node* last = head;
                        while (last->next != nullptr) last = last->next;
                        last->next = new_node;
                    }
                }
            }

            if (str[i] == '{') n++;
            if (n > 0) s += str[i];
            if (str[i] == '}') {
                n--;
               
                if (n == 0) {
                    std::string normalized = normalize(s);
                    if (!contains(normalized)) {
                        Node* new_node = new Node;
                        new_node->value = s;
                        new_node->next = nullptr;

                        if (head == nullptr) {
                            head = new_node;
                        }
                        else {
                            Node* last = head;
                            while (last->next != nullptr) last = last->next;
                            last->next = new_node;
                        }
                    }
                    s = "";
                }
            }
        }
    }
4. **Алгоритм добавления в конец**
   Этот алгоритм добавляет элемент в конец списка.
      ```cpp
   void push_back(std::string str) {
        if (!contains(str)) {
            Node* new_node = new Node;
            new_node->value = str;
            new_node->next = nullptr;

            if (head == nullptr) {
                head = new_node;
            }
            else {
                Node* last = head;
                while (last->next != nullptr) last = last->next;
                last->next = new_node;
            }
        }
    }
5. **Алгоритм удаления**
   Этот алгоритм удаляет элемент из множества.
   ```cpp
       void del(std::string str) {
        if (head == nullptr) {
            std::cout << "Множество пусто." << std::endl;
            return;
        }

        if (normalize(head->value) == normalize(str)) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Node* prev = head;
        Node* current = head->next;
        
        while (current != nullptr) {
            if (normalize(current->value) == normalize(str)) {
                prev->next = current->next;
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

6. **Алгоритм вывода**
   Этот алгоритм выводит множество
   ```cpp
     void print() {
        Node* element = head;
        std::cout << "{";
        bool first = true;
        while (element != nullptr) {
            if (!first) std::cout << ",";
            std::cout << element->value;
            first = false;
            element = element->next;
        }
        std::cout << "}" << std::endl;
    }
7. **Алгоритм объединения**
   Этот алгоритм возвращает объединение двух множеств
   ```cpp
       Set Union(Set other) {
        Set result;
        Node* element = head;
        while (element != nullptr) {
            result.push_back(element->value);
            element = element->next;
        }
        element = other.head;
        while (element != nullptr) {
            result.push_back(element->value);
            element = element->next;
        }
        return result;
    }
8. **Алгоритм пересечения**
   Этот алгоритм возвращает пересечение множеств.
   ```cpp
       Set Intersection(Set other) {
        Set result;
        Node* element = head;
        while (element != nullptr) {
            if (other.contains(element->value)) {
                result.push_back(element->value);
            }
            element = element->next;
        }
        return result;
    }
   ## Вывод:

В результате выполнения данной работы были получены следующие практические навыки:


-изучение структуры множество


-умение работать с header-файлами


-изучение базовых алгоритмов для работы со структурами типа множество

## Используемые источники:
1) **Создание библиотеки** :(https://www.youtube.com/watch?v=pAxEfF2yVlM&t=1s)
2) **Создание гугл-теста** : (https://www.youtube.com/watch?v=NQCGvH-nzjA)
