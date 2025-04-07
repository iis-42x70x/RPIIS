# Лабораторная работа №2

## Цели:
* Выполнить свой вариант работы;
* Реализовать решение варианта на высокоуровневом ЯП
## Вариант:
Для выполнения работы был выдан вариант 4: разность множеств.
## Реализация:
**Данная программа написана на Python.**

Для начала нужно определить способ задания множества. Оно задавалось в виде {A, B, {C, <D, E>, F}} (пример).

Для начала был создан файл SETS.py, в котором был написан класс Diff, в котором были реализованы следующие функции для работы со множествами:
### 1. Нормализация множества
Данная функция нормализует множество, приводя его в каноническую форму:
```
def normalize_set(self, set_data):
    if isinstance(set_data, (list, tuple)):
        normalized_elements = sorted((self.normalize_set(e) for e in set_data), key=str)
        return tuple(normalized_elements)
    else:
        return set_data
```
### 2. Нахождение разности
Данная функция, по сути, делает почти всю работу программы:
```
def find_difference_ruchkami(self, set_a, set_b):
    normalized_a = self.normalize_set(set_a)
    normalized_b = self.normalize_set(set_b)

    difference = []
    for i in normalized_a:
        if i not in normalized_b:
            difference.append(i)
    return difference

```
### 3. Функция для правильной обработки множества
Данная функция очень важна при считывании сложных множеств типа {a, {b, {c}}} или {{{{{}}}}}. Инициализируется счетчик вложенности множества и список для хранения элементов в правильном порядке:
```
    def parse_tuple(self, tuple_str):
        tuple_str = tuple_str.strip()
        if not tuple_str.startswith('<') or not tuple_str.endswith('>'):
            raise ValueError(f"Invalid tuple format: '{tuple_str}'")

        tuple_str = tuple_str[1:-1].strip()
        elements = tuple_str.split(',')
        if len(elements) != 2:
            raise ValueError(f"Invalid tuple format: '{tuple_str}' (must have exactly 2 elements)")

        parsed_elements = []
        for element in elements:
            element = element.strip()
            parsed_elements.append(self.parse_element(element))

        return tuple(parsed_elements)
```
Примечание: функция, описанная выше, используется для обработки непосредственно кортежа из 2 элементов, для множеств функцию можно найти в основном коде.

## Unit-тесты

Для данной программы были написаны 19 тестов, которые были реализованы в файле **teests.py** и импортированы из библиотки ***unittest***. Ниже приведены некоторые тесты из данной программы:
### 1. Тест для проверки дубликатов:
```
def test_parse_set_with_duplicates(self):
    set_str = "{A, B, B, C}"
    with self.assertRaises(ValueError) as context:
        self.diff.parse_set(set_str)
    self.assertTrue("Duplicate elements found in the set" in str(context.exception))
```
### 2. Тест для правильного чтения множества с кортежами из файла:
``` 
def test_read_from_file_with_tuples(self):
    with open("test_input.txt", "w") as file:
        file.write("{A, <B, C>, D}\n")
        file.write("{<B, C>, D, E}\n")

    set_a, set_b = self.diff.read_from_file("test_input.txt")
    self.assertEqual(set_a, ["A", ("B", "C"), "D"])
    self.assertEqual(set_b, [("B", "C"), "D", "E"])
```
### 3. Тест для проверки на корректность скобок:
```
def test_read_from_file_invalid_format_missing_brace(self):
    with open("test_input.txt", "w") as file:
        file.write("{A, B, C\n")  # Пропущена закрывающая скобка
        file.write("{C, D, E, F}\n")

    with self.assertRaises(ValueError) as context:
        self.diff.read_from_file("test_input.txt")
    self.assertTrue("Invalid set format: missing '{' or '}'" in str(context.exception))

    os.remove("test_input.txt")
```

При успешном выполнении всех тестов мы увидим следующее сообщение:

```
...................
----------------------------------------------------------------------
Ran 19 tests in 0.013s

OK
```

## Вывод
В ходе данной лабораторной работы была реализована библиотека для работы со множествами и находжения разности между ними и перенесена на ЯП Python. 

