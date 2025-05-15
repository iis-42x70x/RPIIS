#ifndef PCH_H
#define PCH_H

class Set {
private:
    int* data;
    int size;

    bool contains(int value) const;

public:
    Set();
    ~Set();

    void create();
    void add();
    void remove();
    void search();
    void display();
    void unionWith(const Set& other);
    void intersectWith(const Set& other);

    bool isEmpty() const;
    int inputInteger() const;
    int indexOf(int value) const;
};

#endif
