#ifndef SPIS_HPP
#define SPIS_HPP

#include <iostream>

struct Spis {
    int info;
    Spis* next;
};

Spis* InSpis(Spis* p, int in);
void View(Spis* p);
void Sort_info(Spis* p);
void Search(Spis* p, int elem);
void Del_Elem(Spis** p, int elem);
void Del_All(Spis** p);
bool Contains(Spis* p, int elem);
void Union(Spis* a, Spis* b);
void Intersection(Spis* a, Spis* b);

#endif