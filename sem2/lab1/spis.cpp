#include "spis.hpp"
#include <iostream>
#include <locale>
using namespace std;
Spis* InSpis(Spis* p, int in) {
	Spis* t = new Spis;
	t->info = in;
	t->next = p;
	return t;
}
void View(Spis* p) {
	Spis* t = p;
	while (t != NULL) {
		cout <<t->info << " ";
		t = t->next;
	}
	cout << endl;
}
void Sort_info(Spis* p) {
	Spis* t = NULL, * t1;
	int r;
	do {
		for (t1 = p; t1->next != t; t1 = t1->next)
			if (t1->info > t1->next->info) {
				r = t1->info;
				t1->info = t1->next->info;
				t1->next->info = r;
			}
		t = t1;
	} while (p->next != t);
}
void Search(Spis* p,int elem) {
	Spis* t = p;
	while (t != NULL) {
		if (t->info == elem) {
			cout << "Элемент найден"<< endl;
			return;
		}
		t = t->next;
	}
	cout << "Элемент не найден" << endl;
}
void Del_Elem(Spis** p,int elem) {
	Spis* t = *p;
	Spis* prev = NULL;
	while (t != NULL) {
		if (t->info == elem) {
			if (prev == NULL) {
				*p = t->next;
				delete t;
				t = *p;
			}
			else {
				prev->next = t->next;
				delete t;
				t = prev->next;
			}
		}
		else {
			prev = t;
			t = t->next;
		}
	}
}
void Del_All(Spis** p) {
	Spis* t;
	while (*p != NULL) {
		t = *p;
		*p = (*p)->next;
		delete t;
	}
}
bool Contains(Spis* p, int elem) {
	Spis* t = p;
	while (t != nullptr) {
		if (t->info == elem) {
			return true;
		}
		t = t->next;
	}
	return false;
}
void Union(Spis* a, Spis* b) {
	Spis* t1 = a;
	Spis* t2 = b;
	Spis* res = NULL;
	while (t1 != NULL) {
		if (!Contains(res,t1->info)) {
			res=InSpis(res, t1->info);
		}
		t1 = t1->next;
	}
	while (t2 != NULL) {
			if (!Contains(res, t2->info)) {
				res = InSpis(res, t2->info);
			}
			t2 = t2->next;
	}
	cout << "Список объединения: ";
	View(res);
	Del_All(&res);
}
void Intersection(Spis* a, Spis* b) {
	Spis* t1 = a;
	Spis* res1 = NULL;
	while (t1 != NULL) {
		Spis* t2 = b;
		while (t2 != NULL) {
			if (t1->info == t2->info && !Contains(res1, t1->info)) {
				res1 = InSpis(res1, t1->info);
				break;
			}
			t2 = t2->next;
		}
		t1 = t1->next;
	}
	cout << "Список пересечения: ";
	View(res1);
	Del_All(&res1);
}