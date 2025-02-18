from deque_module import DequeInterface,NodeInterface


class Node(NodeInterface):
    """Узел двусвязного списка"""

    def __init__(self, value):
        """
        Инициализация узла.
        :param value: Значение, которое храниться в узле в узле
        """
        super().__init__(value)
        self.value = value
        self.next = None
        self.prev = None


class Deque(DequeInterface):
    """Класс двусторонней LIFO"""

    def __init__(self):
        """Инициализация пустого дека."""
        super().__init__()
        self._start = None
        self._end = None
        self._size = 0

    def is_empty(self):
        """"Проверка пуст ли дек
        :return: True если дек не пуст, иначе False"""
        return self._size == 0

    def left_add(self, value):
        """
        Добавляет элемент в начало дека.
        :param value: Значение, которое нужно добавить.
        """
        new_node = Node(value)
        if self.is_empty():
            self._start = self._end = new_node
        else:
            new_node.next = self._start
            self._start.prev = new_node
            self._start = new_node
        self._size += 1

    def right_add(self, value):
        """
        Добавляет элемент в начало дека.
        :param value: Значение, которое нужно добавить.
        """
        new_node = Node(value)
        if self.is_empty():
            self._start = self._end = new_node
        else:
            self._end.next = new_node
            new_node.prev = self._end
            self._end = new_node
        self._size += 1

    def del_left(self):
        """Удаляет элемент с начала дека."""
        if self.is_empty():
            raise IndexError("Дек пуст,удаление невозможно")
        if self._start == self._end:
            self._start = self._end = None
        else:
            self._start = self._start.next
            self._start.prev = None
        self._size -= 1

    def del_right(self):
        """Удаляет элемент с конца дека."""
        if self.is_empty():
            raise IndexError("Дек пуст,удаление невозможно")
        if self._start == self._end:
            self._start = self._end = None
        else:
            self._end = self._end.prev
            self._end.next = None
        self._size -= 1

    def __str__(self):
        """
        Возвращает строковое представление дека.
        :return: Строка, представляющая элементы дека.
        """
        result = []
        current = self._start
        while current:
            result.append(str(current.value))
            current = current.next
        return "[" + ", ".join(result) + "]"
