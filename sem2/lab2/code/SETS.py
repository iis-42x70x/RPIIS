import re

class Diff:
    def find_difference_ruchkami(self, set_a, set_b):
        normalized_a = self.normalize_set(set_a)
        normalized_b = self.normalize_set(set_b)

        difference = []
        for i in normalized_a:
            if i not in normalized_b:
                difference.append(i)
        return difference

    def normalize_set(self, set_data):
        if isinstance(set_data, (list, tuple)):
            normalized_elements = sorted((self.normalize_set(e) for e in set_data), key=str)
            return tuple(normalized_elements)
        else:
            return set_data

    def parse_element(self, element):
        element = element.strip()
        if element.startswith('<') and element.endswith('>'):
            return self.parse_tuple(element)
        elif element.startswith('{') and element.endswith('}'):
            return tuple(self.parse_set(element))
        else:
            if not re.match(r'^[A-Za-z0-9_]+$', element):
                raise ValueError(f"Invalid element format: '{element}'")
            return element

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

    def parse_set(self, set_str):
        set_str = set_str.strip()
        if not set_str.startswith('{') or not set_str.endswith('}'):
            raise ValueError("Invalid set format: missing '{' or '}'")

        set_str = set_str[1:-1].strip()

        if not set_str:
            return []

        elements = []
        buffer = ""
        in_tuple = False
        in_set = 0

        for char in set_str:
            if char == '<':
                in_tuple = True
            elif char == '>':
                in_tuple = False
            elif char == '{':
                in_set += 1
            elif char == '}':
                in_set -= 1
            elif char == ',' and not in_tuple and in_set == 0:
                elements.append(buffer.strip())
                buffer = ""
                continue
            buffer += char

        if buffer:
            elements.append(buffer.strip())

        result = []
        for element in elements:
            try:
                parsed_element = self.parse_element(element)
                result.append(parsed_element)
            except ValueError as e:
                raise ValueError(f"Error in set: {e}")

        if len(result) != len(set(result)):
            raise ValueError("Duplicate elements found in the set")

        return result

    def read_from_file(self, filename):
        try:
            with open(filename, 'r') as file:
                lines = file.readlines()
                if len(lines) < 2:
                    raise ValueError("Not enough strings in the file")

                set_a = self.parse_set(lines[0].strip())
                set_b = self.parse_set(lines[1].strip())

                return set_a, set_b

        except FileNotFoundError:
            raise FileNotFoundError("File is not found")
        except ValueError as e:
            raise ValueError(f"Error in file: {e}")

    def format_element(self, element):
        if isinstance(element, tuple):
            if len(element) == 0:
                return "{}"
            elif len(element) == 2 and all(isinstance(e, str) for e in element):
                return f"<{element[0]}, {element[1]}>"
            else:
                return "{" + ", ".join(self.format_element(e) for e in element) + "}"
        else:
            return str(element)

    def format_set(self, set_data):
        return "{" + ", ".join(self.format_element(e) for e in set_data) + "}"