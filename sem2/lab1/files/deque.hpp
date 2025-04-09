#ifndef DEQUE_H
#define DEQUE_H

#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
class Deque {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
    };

    Node* front;
    Node* back;
    size_t size;

public:
    // Инициализация дека
    void init();

    // Очистка дека
    void cleanup();

    // Проверка на пустоту
    bool isEmpty() const;

    // Получение размера дека
    size_t getSize() const;

    // Добавление элемента в начало
    void addFront(const T& data);

    // Добавление элемента в конец
    void addBack(const T& data);

    // Удаление элемента из начала
    T removeFront();

    // Удаление элемента из конца
    T removeBack();

    // Получение первого элемента (без удаления)
    T peekFront() const;

    // Получение последнего элемента (без удаления)
    T peekBack() const;

    // Вывод содержимого дека
    void display() const;
};

#endif // DEQUE_H
