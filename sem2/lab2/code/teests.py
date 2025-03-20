import unittest
from SETS import Diff
import os

class TestDiff(unittest.TestCase):
    def setUp(self):
        self.diff = Diff()

    def test_find_difference_basic(self):
        set_a = ["A", "B", "C", "D"]
        set_b = ["C", "D", "E", "F"]
        result = self.diff.find_difference_ruchkami(set_a, set_b)
        self.assertEqual(result, ["A", "B"])



    def test_find_difference_no_difference(self):
        set_a = ["A", "B"]
        set_b = ["A", "B", "C"]
        result = self.diff.find_difference_ruchkami(set_a, set_b)
        self.assertEqual(result, [])

    def test_read_from_file_valid_data(self):
        with open("test_input.txt", "w") as file:
            file.write("{A, B, C, D}\n")
            file.write("{C, D, E, F}\n")

        set_a, set_b = self.diff.read_from_file("test_input.txt")
        self.assertEqual(set_a, ["A", "B", "C", "D"])
        self.assertEqual(set_b, ["C", "D", "E", "F"])

        os.remove("test_input.txt")

    def test_read_from_file_file_not_found(self):
        with self.assertRaises(FileNotFoundError) as context:
            self.diff.read_from_file("nonexistent_file.txt")
        self.assertTrue("File is not found" in str(context.exception))

    def test_read_from_file_invalid_format_missing_brace(self):
        with open("test_input.txt", "w") as file:
            file.write("{A, B, C\n")  # Пропущена закрывающая скобка
            file.write("{C, D, E, F}\n")

        with self.assertRaises(ValueError) as context:
            self.diff.read_from_file("test_input.txt")
        self.assertTrue("Invalid set format: missing '{' or '}'" in str(context.exception))

        os.remove("test_input.txt")

    def test_read_from_file_invalid_format_empty_element(self):
        with open("test_input.txt", "w") as file:
            file.write("{A, , C}\n")  # Пустой элемент
            file.write("{C, D, E, F}\n")

        with self.assertRaises(ValueError) as context:
            self.diff.read_from_file("test_input.txt")
        self.assertFalse("Invalid set format: empty element" in str(context.exception))

        os.remove("test_input.txt")

    def test_read_from_file_invalid_format_invalid_element(self):
        with open("test_input.txt", "w") as file:
            file.write("{A, B@, C}\n")  # Недопустимый символ '@'
            file.write("{C, D, E, F}\n")

        with self.assertRaises(ValueError) as context:
            self.diff.read_from_file("test_input.txt")
        self.assertFalse("Invalid set format: invalid element" in str(context.exception))

        os.remove("test_input.txt")

    def test_read_from_file_not_enough_strings(self):
        with open("test_input.txt", "w") as file:
            file.write("{A, B, C}\n")  # Только одна строка

        with self.assertRaises(ValueError) as context:
            self.diff.read_from_file("test_input.txt")
        self.assertTrue("Not enough strings in the file" in str(context.exception))

        os.remove("test_input.txt")

    # Тесты для кортежей
    def test_parse_tuple_valid(self):
        tuple_str = "<A, B>"
        result = self.diff.parse_tuple(tuple_str)
        self.assertEqual(result, ("A", "B"))

    def test_parse_tuple_invalid_format(self):
        tuple_str = "<A, B"  # Пропущена закрывающая скобка
        with self.assertRaises(ValueError) as context:
            self.diff.parse_tuple(tuple_str)
        self.assertTrue("Invalid tuple format" in str(context.exception))

    def test_parse_tuple_invalid_element(self):
        tuple_str = "<A, B@>"  # Недопустимый символ '@'
        with self.assertRaises(ValueError) as context:
            self.diff.parse_tuple(tuple_str)
        self.assertFalse("Invalid tuple element" in str(context.exception))

    def test_parse_tuple_not_enough_elements(self):
        tuple_str = "<A>"  # Только один элемент
        with self.assertRaises(ValueError) as context:
            self.diff.parse_tuple(tuple_str)
        self.assertTrue("must have exactly 2 elements" in str(context.exception))

    def test_find_difference_with_tuples(self):
        set_a = ["A", ("B", "C"), "D"]
        set_b = [("B", "C"), "D", "E"]
        result = self.diff.find_difference_ruchkami(set_a, set_b)
        self.assertEqual(result, ["A"])

    def test_read_from_file_with_tuples(self):
        with open("test_input.txt", "w") as file:
            file.write("{A, <B, C>, D}\n")
            file.write("{<B, C>, D, E}\n")

        set_a, set_b = self.diff.read_from_file("test_input.txt")
        self.assertEqual(set_a, ["A", ("B", "C"), "D"])
        self.assertEqual(set_b, [("B", "C"), "D", "E"])

        os.remove("test_input.txt")

    # Тесты для проверки дубликатов
    def test_parse_set_with_duplicates(self):
        set_str = "{A, B, B, C}"
        with self.assertRaises(ValueError) as context:
            self.diff.parse_set(set_str)
        self.assertTrue("Duplicate elements found in the set" in str(context.exception))

    def test_parse_set_with_tuple_duplicates(self):
        set_str = "{A, <B, C>, <B, C>}"
        with self.assertRaises(ValueError) as context:
            self.diff.parse_set(set_str)
        self.assertTrue("Duplicate elements found in the set" in str(context.exception))

    # Тесты для ранней обработки ошибок
    def test_early_error_handling_set_a(self):
        set_a_str = "{A, B, <C, D}"  # Пропущена закрывающая скобка
        with self.assertRaises(ValueError) as context:
            self.diff.parse_set(set_a_str)
        self.assertFalse("Invalid tuple format" in str(context.exception))

    def test_early_error_handling_set_b(self):
        set_a_str = "{A, B, <C, D>}"  # Корректный ввод
        set_b_str = "{A, B, <C, D}"  # Пропущена закрывающая скобка
        with self.assertRaises(ValueError) as context:
            set_a = self.diff.parse_set(set_a_str)
            set_b = self.diff.parse_set(set_b_str)
        self.assertFalse("Invalid tuple format" in str(context.exception))
    def test_nested_sets(self):
        diff = Diff()
        set_a = diff.parse_set("{a, {b, {c}}}")
        set_b = diff.parse_set("{{{c}, b}, a}")
        result = diff.find_difference_ruchkami(set_a, set_b)
        self.assertEqual(result, [])  # Ожидаем пустую разность

if __name__ == "__main__":
    unittest.main()