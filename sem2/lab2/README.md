# Лабораторная работа №2

- `Цель` - Реализовать программу, формирующую множество равное разности двух исходных
  множеств (без учёта кратных вхождений элементов).
- `Задача` - реализовать алгоритм разности

## Список ключевых понятий (определения)
- ` Множество`  - простейшая информационная конструкция и математическая структура, позволяющая рассматривать какие-то объекты как целое, связывая их.
- `Разность множеств A и B без учета кратных вхождений элементов` - это множество S такое что, для любого x истинно S|x| = max{min{A|x|, 1}-min{B|x|, 1}, min{B|x|, 1}-min{A|x|, 1}}.
## Алгоритм

### Создание экземпляра класса множества

``` Python
    def __init__(self, name: str, multitude: str):
        if self._validate_name(name) and self._validate_multitude(multitude):
            self.name = name
            self.multitude = self._split_multitude(multitude)
            Multitude.multitudes[self.multitude] = name
```
Методы `_validate_name` и `_validate_multitude` проверяют на корректность имя множества и запись самого множества.
Метод `_split_multitude` переводит множество из строкового представления в более удобный для реализации(кортеж элементами которого являются строки(элементы множества) или другие кортежи(подмножества исходного множества)):

``` Python
if multitude == "{}":
            return ()
        subset_balance = 0  # баланс фигурных скобок
        tuple_balance = 0  # баланс угловых скобок
        current_item: str = ""  # текущий элемент множества
        multitude_list = []  # массив для хранения элементов множества
        for i in range(1, len(multitude)):
            if multitude[i] == "{":
                subset_balance += 1
                current_item += multitude[i]

            elif multitude[i] == "}":
                subset_balance -= 1
                if subset_balance == -1:
                    multitude_list.append(current_item)
                    current_item = ""
                    return self._update_multitude_tuple(tuple(multitude_list))
                elif not subset_balance:
                    current_item += multitude[i]
                    current_item = self._split_multitude(current_item)
                else:
                    current_item += multitude[i]

            elif multitude[i] == "<":
                tuple_balance += 1
                current_item += multitude[i]

            elif multitude[i] == ">":
                tuple_balance -= 1
                current_item += multitude[i]

            elif multitude[i] == ",":
                if not subset_balance and not tuple_balance:
                    multitude_list.append(current_item)
                    current_item = ""
                else:
                    current_item += multitude[i]
            elif multitude[i] == " ":
                continue
            else:
                current_item += multitude[i]
```



### Функция поиска разности двух множеств

``` Python
    def substraction(self, subtrahend: Self) -> str:
        minuend_dict = self._create_multitude_dict(self.multitude)
        subtrahend_dict = self._create_multitude_dict(subtrahend.multitude)
        answer = []
        for k in minuend_dict.keys():
            if k not in subtrahend_dict.keys():
                for i in range(minuend_dict[k]):
                    answer.append(k)
        return self._from_list_to_str(answer)
```

1. Создает словарь для уменьшаемого и вычитаемого множеств, в котором ключи - элементы множеств, значения - количество вхождений.
   ``` Python
       def _create_multitude_dict(self, multitude_tuple: tuple) -> dict:
        multitude_dict = {}
        for item in multitude_tuple:
            multitude_dict[item] = multitude_dict.get(item, 0) + 1
        return multitude_dict
   ```
2.  Проходит циклом по элементам уменьшаемого множества и, если элемент не принадлежит вычитаемогу множеству, добавляет его к ответу.
3.  Возвращает множество в строковом виде.
   ``` Python
        def _from_list_to_str(self, multitude_list: list) -> str:
        if not multitude_list:
            return "{}"
        elements = []
        for i in multitude_list:
            if isinstance(i, str):
                elements.append(i)
            elif not i:
                elements.append("{}")
            else:
                elements.append(f"{{{self._from_list_to_str(i)}}}")

        return ",".join(elements)
   ```


## Тесты
`Входные данные`:

![image](https://github.com/user-attachments/assets/c336478e-c604-4609-a4a0-9552a3a61974)

`Результат`:

![image](https://github.com/user-attachments/assets/216b5c13-7f18-40a0-9962-03b654df45a1)

## Вывод
Реализовал алгоритм `Разности двух множеств без учета кратных вхождений элементов`
