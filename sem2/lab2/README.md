
# Лабораторная работа №2
---

## Задача	
			
### Вариант 13

 Реализовать программу, формирующую множество равное разности двух исходных множеств с учетом кратных вхождений.

---

## Цель:

 Изучить основы теории множеств.

---

## Список ключевых понятий:

 **Множество** — простейшая информационная конструкция и математическая структура,
позволяющая рассматривать какие-то объекты как целое, связывая их.

 **Разность множеств** - это множество, состоящее из тех и только тех элементов, которые входят в первое множество, но не входят во второе.
 *Разность множеств с учетом кратных вхождений* - мультимножество, в котором кратность каждого элемента x ∈ X определяется следующим образом:
                                                    (A∖B)(x)=max(0,A(x)−B(x))
---

## **Описание используемых алгоритмов:**
1. **Обеспечение наличия файла входных данных (`ensure_input_file`)**
 
  1.1 Проверяется существование файла input.txt. Если файл отсутствует, он создаётся с данными по умолчанию.
  
```py

  def ensure_input_file():
    if not os.path.exists("input.txt"):
        with open("input.txt", "w") as file:
            file.write("A={1,2,3} B={2,3,4}\n")

```

2.  **Считывание данных из файла (`read_input_file`)**
Считываются данные из последней строки файла input.txt.
  
```py
def read_input_file():
    with open("input.txt", "r") as file:
        lines = file.readlines()
    return lines[-1].strip()  # Берём последнюю строку


```
3.  **Перезапись множеств в файл (`overwrite_sets_in_file`)**
Пользователь вводит два множества. Эти множества проверяются на ошибки, и, если ошибок нет, они записываются в файл.
  
```py
def overwrite_sets_in_file():
    user_data = input("Введите два множества: ").strip()
    with open("input.txt", "w") as file:
        file.write(user_data + "\n")



```
4.  **Парсинг множества (`parse_set`)**
Множество из строки преобразуется в список элементов. Также проверяется корректность формата.
```py
def parse_set(set_str):
    elements = []
    current = ""
    for char in set_str[1:-1]:  # Убираем первые и последние символы ({ или < и } или >)
        if char == ",":
            elements.append(current.strip())
            current = ""
        else:
            current += char
    if current.strip():
        elements.append(current.strip())
    return elements, None


```
5.  **Подсчёт количества вхождений элементов (`count_elements`)**
Создаётся словарь, где ключ — элемент множества, а значение — количество его вхождений.
```py
def count_elements(elements):
    counts = {}
    for elem in elements:
        counts[elem] = counts.get(elem, 0) + 1
    return counts



```
6.  **Вычисление разности множеств с учётом кратных вхождений (`set_difference`)**
Для каждого элемента из множества A проверяется его наличие в множестве B. Если элемент есть в B, его кратность уменьшается. Если нет — элемент добавляется в результат.
```py
def set_difference(set1, set2):
    counts2 = count_elements(set2)
    result = []
    for elem in set1:
        if counts2.get(elem, 0) > 0:
            counts2[elem] -= 1
        else:
            result.append(elem)
    return result




```
7.  **Форматирование множества (`format_set`)**
Результат разности преобразуется обратно в строку в зависимости от типа множества (упорядоченное или неупорядоченное).
```py
def format_set(elements, set_type):
    if set_type == "ordered":
        return "<" + ",".join(elements) + ">"
    else:
        return "{" + ",".join(elements) + "}"




```
8.  **Обработка строки с двумя множествами (`process_data`)**
Строка с двумя множествами разделяется, проверяется на ошибки, затем вычисляется разность множеств.
```py
def process_data(line):
    set1, set2 = line.split(maxsplit=1)
    result = set_difference(parse_set(set1.strip())[0], parse_set(set2.strip())[0])
    return result



```
9.  **Сохранение результата в файл (`save_result_to_input`)**
Результат вычисления разности записывается в файл.
```py
def save_result_to_input(result):
    with open("input.txt", "a") as file:
        file.write(f"Результат: {result}\n")



```
---
## Тесты
![image](https://github.com/user-attachments/assets/d5d2e1a0-e350-41a2-9a0b-920fa5168d92)


## Вывод

В ходе выполнения был реализован алгоритм нахождения разности произвольных множеств.
