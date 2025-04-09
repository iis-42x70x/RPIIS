#include "header.h"

using namespace std;


template <typename T>
void Deque<T>::init() {
    front = back = nullptr;
    size = 0;
}

template <typename T>
void Deque<T>::cleanup() {
    while (!isEmpty()) {
        removeFront();
    }
}

template <typename T>
bool Deque<T>::isEmpty() const {
    return size == 0;
}

template <typename T>
size_t Deque<T>::getSize() const {
    return size;
}

template <typename T>
void Deque<T>::addFront(const T& data) {
    Node* newNode = new Node{ data, nullptr, nullptr };

    if (isEmpty()) {
        front = back = newNode;
    }
    else {
        newNode->next = front;
        front->prev = newNode;
        front = newNode;
    }
    size++;
}

template <typename T>
void Deque<T>::addBack(const T& data) {
    Node* newNode = new Node{ data, nullptr, nullptr };

    if (isEmpty()) {
        front = back = newNode;
    }
    else {
        newNode->prev = back;
        back->next = newNode;
        back = newNode;
    }
    size++;
}

template <typename T>
T Deque<T>::removeFront() {
    if (isEmpty()) {
        throw runtime_error("Deque is empty");
    }

    Node* temp = front;
    T data = temp->data;

    if (front == back) {
        front = back = nullptr;
    }
    else {
        front = front->next;
        front->prev = nullptr;
    }

    delete temp;
    size--;
    return data;
}

template <typename T>
T Deque<T>::removeBack() {
    if (isEmpty()) {
        throw runtime_error("Deque is empty");
    }

    Node* temp = back;
    T data = temp->data;

    if (front == back) {
        front = back = nullptr;
    }
    else {
        back = back->prev;
        back->next = nullptr;
    }

    delete temp;
    size--;
    return data;
}

template <typename T>
T Deque<T>::peekFront() const {
    if (isEmpty()) {
        throw runtime_error("Deque is empty");
    }
    return front->data;
}

template <typename T>
T Deque<T>::peekBack() const {
    if (isEmpty()) {
        throw runtime_error("Deque is empty");
    }
    return back->data;
}

template <typename T>
void Deque<T>::display() const {
    Node* current = front;
    cout << "Deque: ";
    while (current != nullptr) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

int main() {
    Deque<int> deque;
    deque.init();

    int choice, value;

    do {
        cout << "\nMenu:\n";
        cout << "1. Add to front\n";
        cout << "2. Add to back\n";
        cout << "3. Remove from front\n";
        cout << "4. Remove from back\n";
        cout << "5. Display deque\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        try {
            switch (choice) {
            case 1:
                cout << "Enter value to add to front: ";
                cin >> value;
                deque.addFront(value);
                break;
            case 2:
                cout << "Enter value to add to back: ";
                cin >> value;
                deque.addBack(value);
                break;
            case 3:
                cout << "Removed from front: " << deque.removeFront() << endl;
                break;
            case 4:
                cout << "Removed from back: " << deque.removeBack() << endl;
                break;
            case 5:
                deque.display();
                break;
            case 6:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
            }
        }
        catch (const runtime_error& e) {
            cout << "Error: " << e.what() << endl;
        }
    } while (choice != 6);

    deque.cleanup();
    return 0;
}
