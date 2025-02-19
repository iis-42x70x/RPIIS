#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <string>

using namespace std;

struct Element {
    string data;
    Element* next;
};

void dobavqueue(Element*& pervyi, Element*& posled, const string& value);
string vziatqueue(Element*& pervyi, Element*& posled);
bool isEmpty(Element* pervyi);
void clearqueue(Element*& pervyi, Element*& posled);
void viewqueue(Element* pervyi);

#endif
