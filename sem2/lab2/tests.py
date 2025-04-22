import unittest
from main import ensure_input_file, parse_set, count_elements, multiset_difference, format_result, save_result
class TestFunctions(unittest.TestCase):
    def test_ensure_input_file(self):
        """Проверка создания файла input.txt"""
        import os
        if os.path.exists("input.txt"):
            os.remove("input.txt")
        self.assertTrue(ensure_input_file())
        self.assertTrue(os.path.exists("input.txt"))

    def test_parse_set(self):
        """Проверка парсинга множества"""
        elements, error = parse_set("{1,2,3,3}")
        self.assertEqual(elements, ['1', '2', '3', '3'])
        self.assertIsNone(error)

    def test_multiset_difference(self):
        """Проверка разности мультимножеств"""
        set1 = ['1', '2', '3', '3']
        set2 = ['2', '3', '4']
        result = multiset_difference(set1, set2)
        self.assertEqual(result, ['1', '3'])

    def test_format_result(self):
        """Проверка форматирования результата"""
        elements = ['1', '3']
        original_set = "{1,2,3,3}"
        result = format_result(elements, original_set)
        self.assertEqual(result, "{1,3}")

    def test_save_result(self):
        """Проверка сохранения результата в файл"""
        result = "{1,3}"
        save_result(result)
        with open("input.txt", "r") as f:
            content = f.read().strip()
        self.assertTrue("Результат: {1,3}" in content)

    def test_count_elements(self):
        """Проверка подсчета количества элементов"""
        elements = ['a', 'b', 'a', 'c', 'b', 'a']
        counts = count_elements(elements)
        self.assertEqual(counts, {'a': 3, 'b': 2, 'c': 1})

if __name__ == "__main__":
    unittest.main()
