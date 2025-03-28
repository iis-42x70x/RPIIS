from typing import Self
import re


class Multitude:
    multitudes: dict[tuple:str] = {}

    def __init__(self, name: str, multitude: str):
        if self._validate_name(name) and self._validate_multitude(multitude):
            self.name = name
            self.multitude = self._split_multitude(multitude)
            Multitude.multitudes[self.multitude] = name

    def _validate_name(self, name: str) -> bool:
        if re.fullmatch(r"^[a-zA-Z][a-zA-Z0-9]*_?[a-zA-Z0-9]*$", name):
            return True
        else:
            raise ValueError("Недопустимый формат имени множества")

    def _validate_multitude(self, multitude: str) -> bool:
        mapping = {"}": "{", ">": "<"}
        prev_is_item = True
        stack = []
        if multitude[0] != "{" or multitude[-1] != "}":
            return False
        for i in multitude:
            if i in mapping.values():
                stack.append(i)
            elif i in mapping.keys():
                if not stack or mapping[i] != stack.pop():
                    raise ValueError("Недопустимый формат множества")
            elif i == ',':
                if not prev_is_item:
                    raise ValueError("Недопустимый формат множества")
                else:
                    prev_is_item = False
                    continue
            if i:
                prev_is_item = True
        if stack:
            raise ValueError("Недопустимый формат множества")
        return True

    def _split_multitude(self, multitude: str) -> tuple:
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

    def _update_multitude_tuple(self, multitude_tuple: tuple) -> tuple:
        transformed_tuple = []

        for item in multitude_tuple:
            if isinstance(item, tuple) and item in Multitude.multitudes:
                transformed_tuple.append(Multitude.multitudes[item])

            elif isinstance(item, tuple):
                transformed_tuple.append(self._update_multitude_tuple(item))

            else:
                transformed_tuple.append(item)

        new_tuple = tuple(transformed_tuple)
        if new_tuple == multitude_tuple:
            return new_tuple
        else:
            return self._update_multitude_tuple(new_tuple)

    def _create_multitude_dict(self, multitude_tuple: tuple) -> dict:
        multitude_dict = {}
        for item in multitude_tuple:
            multitude_dict[item] = multitude_dict.get(item, 0) + 1
        return multitude_dict

    def _from_tuple_to_str(self, multitude_tuple: tuple) -> str:
        if not multitude_tuple:
            return "{}"
        elements = []
        for i in multitude_tuple:
            if isinstance(i, str):  
                elements.append(i)
            elif not i:
                elements.append('{}')
            else:
                elements.append(f"{{{self._from_tuple_to_str(i)}}}")  

        return ",".join(elements)  

    def substraction(self, subtrahend: Self) -> str:
        minuend_dict = self._create_multitude_dict(self.multitude)
        subtrahend_dict = self._create_multitude_dict(subtrahend.multitude)
        answer = []
        for k in minuend_dict.keys():
            if k not in subtrahend_dict.keys():
                for i in range(minuend_dict[k]):
                    answer.append(k)
        return self._from_tuple_to_str(tuple(answer))


