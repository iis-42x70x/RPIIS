import unittest
from main import parse_set, set_difference, count_elements, format_set, process_data, read_input_file

class TestYourProgram(unittest.TestCase):

    def test_parse_set_valid(self):
        """Тест: корректный парсинг множества с правильным форматом."""
        result, err = parse_set("{1,2,3}")
        self.assertIsNone(err, "Парсинг корректного множества должен завершиться успешно")
        self.assertEqual(result, ["1", "2", "3"], "Результат парсинга множества неверный")

    def test_parse_set_invalid(self):
        """Тест: некорректный формат множества."""
        result, err = parse_set("[1,2,3]")
        self.assertIsNotNone(err, "Некорректный формат множества должен вызывать ошибку")
        self.assertIsNone(result, "Результат парсинга множества с некорректным форматом должен быть пустым")

    def test_parse_set_nested(self):
        """Тест: корректный парсинг вложенного множества."""
        result, err = parse_set("<1,{2,3},4>")
        self.assertIsNone(err, "Парсинг вложенного множества должен завершиться успешно")
        self.assertEqual(result, ["1", "{2,3}", "4"], "Результат парсинга вложенного множества неверный")

    def test_count_elements(self):
        """Тест: подсчет количества вхождений элементов."""
        elements = ["a", "b", "a", "c", "b", "a"]
        counts = count_elements(elements)
        self.assertEqual(counts, {"a": 3, "b": 2, "c": 1}, "Подсчет количества элементов выполнен неверно")

    def test_set_difference(self):
        """Тест: корректное вычисление разности множеств."""
        set1 = ["1", "2", "2", "3"]
        set2 = ["2", "3"]
        result = set_difference(set1, set2)
        self.assertEqual(result, ["1", "2"], "Разность множеств вычислена неверно")

    def test_format_set(self):
        """Тест: корректное форматирование множества."""
        elements = ["1", "2", "3"]
        formatted_unordered = format_set(elements, "unordered")
        self.assertEqual(formatted_unordered, "{1,2,3}", "Неверное форматирование неупорядоченного множества")
        formatted_ordered = format_set(elements, "ordered")
        self.assertEqual(formatted_ordered, "<1,2,3>", "Неверное форматирование упорядоченного множества")




if __name__ == "__main__":
    unittest.main()
