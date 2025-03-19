#pragma once
#include <iostream>
#include <vector>
#include <locale> 
#include <algorithm>
using namespace std;
void build(int* mas, int v, int tl, int tr, int* t) {
    if (tl == tr)
        t[v] = mas[tl];
    else {
        int tm = (tl + tr) / 2;
        build(mas, v * 2, tl, tm, t);
        build(mas, v * 2 + 1, tm + 1, tr, t);
        t[v] = max(t[v * 2], t[v * 2 + 1]);
    }
}
int Max(int v, int tl, int tr, int l, int r, int* t) {
    if (l > r)
        return 0;
    if (l == tl && r == tr)
        return t[v];
    int tm = (tl + tr) / 2;
    return max(Max(v * 2, tl, tm, l, min(r, tm), t), Max(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r, t));
}
void Mod(int v, int tl, int tr, int pos, int new_val, int* t) {
    if (tl == tr)
        t[v] = new_val;
    else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            Mod(v * 2, tl, tm, pos, new_val, t);
        else
            Mod(v * 2 + 1, tm + 1, tr, pos, new_val, t);
        t[v] = max(t[v * 2], t[v * 2 + 1]);
    }
}
void printTree(int* t, int v, int tl, int tr, int level = 0) {
    if (tl == tr) {
        for (int i = 0; i < level; ++i) cout << "  ";
        cout << t[v] << "\n";
    }
    else {
        int tm = (tl + tr) / 2;
        printTree(t, v * 2 + 1, tm + 1, tr, level + 1);
        for (int i = 0; i < level; ++i) cout << "  ";
        cout << t[v] << "\n";
        printTree(t, v * 2, tl, tm, level + 1);
    }
}