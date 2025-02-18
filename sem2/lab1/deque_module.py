

class NodeInterface:
    """Узел двусвязного списка"""

    def __init__(self, value):
        """
        Инициализация узла.
        :param value: Значение, хранящееся в узле.
        """
        pass


class DequeInterface:
    """Класс двусторонней очереди"""

    def __init__(self):
        """Инициализация пустого дека."""
        pass

    def is_empty(self):
        """Проверяет, пуст ли дек."""
        pass

    def left_add(self, value):
        """Добавляет элемент в начало дека."""
        pass

    def right_add(self, value):
        """Добавляет элемент в конец дека."""
        pass

    def del_left(self):
        """Удаляет элемент из начала дека."""
        pass

    def del_right(self):
        """Удаляет элемент из конца дека."""
        pass

    def __str__(self):
        """Возвращает строковое представление дека."""
        pass
