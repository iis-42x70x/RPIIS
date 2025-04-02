#ifndef ELEMENT_H
#define ELEMENT_H

struct Element {
    enum Type { VALUE, SET } type;
    union {
        int value;
        struct {
            Element* elements;
            int count;
        } set;
    } data;

    Element();
    Element(int val);
    Element(Element* elems, int cnt);
    
    Element(const Element& other);
    
    Element& operator=(const Element& other);
    
    ~Element();
    
    bool operator==(const Element& other) const;
};

Element* readSet(int& count);
bool contains(const Element* arr, int count, const Element& item);
Element* calculateSymmetricDifference(Element** sets, int* counts, int setCount, int& resultCount);
void printElement(const Element& e);

#endif
