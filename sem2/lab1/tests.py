import unittest
from deque_impl import Deque
class TestDeque(unittest.TestCase):
    def setUp(self):
        """Создание нового дека перед каждым тестом"""
        self.deque = Deque()

    def test_empty_deque(self):
        """Проверка, что новый дек пуст"""
        self.assertTrue(self.deque.is_empty())
        self.assertEqual(str(self.deque), "[]")

    def test_add_left(self):
        """Проверка добавления элементов слева"""
        self.deque.left_add(1)
        self.assertFalse(self.deque.is_empty())
        self.assertEqual(str(self.deque), "[1]")

        self.deque.left_add(2)
        self.assertEqual(str(self.deque), "[2, 1]")

    def test_add_right(self):
        """Проверка добавления элементов справа"""
        self.deque.right_add(1)
        self.assertFalse(self.deque.is_empty())
        self.assertEqual(str(self.deque), "[1]")

        self.deque.right_add(2)
        self.assertEqual(str(self.deque), "[1, 2]")

    def test_del_left(self):
        """Проверка удаления элементов слева"""
        self.deque.left_add(1)
        self.deque.left_add(2)

        self.deque.del_left()
        self.assertEqual(str(self.deque), "[1]")

        self.deque.del_left()
        self.assertTrue(self.deque.is_empty())

    def test_del_right(self):
        """Проверка удаления элементов справа"""
        self.deque.right_add(1)
        self.deque.right_add(2)

        self.deque.del_right()
        self.assertEqual(str(self.deque), "[1]")

        self.deque.del_right()
        self.assertTrue(self.deque.is_empty())

    def test_exceptions(self):
        """Проверка, что удаление из пустого дека вызывает ошибку"""
        with self.assertRaises(IndexError):
            self.deque.del_left()

        with self.assertRaises(IndexError):
            self.deque.del_right()

if __name__ == "__main__":
    unittest.main()
