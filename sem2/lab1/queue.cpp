#include "queue.h"
#include<iostream>
#include<string>

using namespace std;

void dobavqueue(Element*& pervyi, Element*& posled, const string& value) {
    Element* newElement = new Element;
    newElement->data = value;
    newElement->next = nullptr;

    if (posled == nullptr) {
        pervyi = posled = newElement;
    }
    else {
        posled->next = newElement;
        posled = newElement;
    }

    cout << "Элемент '" << value << "' добавлен в очередь." << endl;
}

string vziatqueue(Element*& pervyi, Element*& posled) {
    if (pervyi == nullptr) {
        cout << "Очередь пуста." << endl;
        return "";
    }

    string value = pervyi->data;

    Element* temp = pervyi;
    pervyi = pervyi->next;

    if (pervyi == nullptr) {
        posled = nullptr;
    }

    delete temp;
    return value;
}

bool isEmpty(Element* pervyi) {
    return pervyi == nullptr;
}

void clearqueue(Element*& pervyi, Element*& posled) {
    while (pervyi != nullptr) {
        Element* temp = pervyi;
        pervyi = pervyi->next;
        delete temp;
    }

    posled = nullptr;

    cout << "Очередь очищена." << endl;
}

void viewqueue(Element* pervyi) {
    if (isEmpty(pervyi)) {
        cout << "Очередь пуста." << endl;
        return;
    }

    cout << "Содержимое очереди: ";

    Element* temp = pervyi;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }

    cout << endl;
}
