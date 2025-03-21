#include <iostream>
#include <vector>
#include "SegTree.hpp"

using namespace std;

SegTree::SegTree(vector<int> &arr) {
    n = (int) arr.size();
    t.resize(4 * n);
    lazy.assign(4 *n, -1);
    build(arr, 0, 0, n - 1);
}
void SegTree::update_array (int l, int r, int v) {
    update(l, r, v, 0, 0, n - 1);
}
long long SegTree::get_sum(int l, int r) {
    return sum(l, r, 0, 0, n - 1);
}
vector<int> SegTree::get_final_array() {
    vector<int> result(n);
    collect_values(0, 0, n - 1, result);
    return result;
}
void SegTree::build(vector<int> &arr, int v, int tl, int tr) {
    if (tl == tr) {
        t[v] = arr[tl];
    } else {
        int tm = (tl + tr) / 2;
        build(arr, v * 2 + 1, tl, tm);
        build(arr, v * 2 + 2, tm + 1, tr);
        t[v] = t[v * 2 + 1] + t[v * 2 + 2];
    }
}

void SegTree::push (int v, int tl, int tr) {
    if (lazy[v] != -1) {
        t[v] = (tr - tl + 1)* lazy[v];
        if (tl != tr) {
            lazy [v * 2 + 1] = lazy[v];
            lazy [v * 2 + 2] = lazy[v];
        }
        lazy [v] = -1;
    }
}


void SegTree::update(int l, int r, int v, int x, int xl, int xr) {
    push(x, xl, xr);
    if (r < xl || l > xr) {
        return;
    }
    if (xl >= l && xr <= r) {
        lazy[x] = v;
        push(x, xl, xr);
        return;
    }
    int xm = (xl + xr) / 2;
    update(l, r, v, 2 * x + 1, xl, xm);
    update(l, r, v, 2 * x + 2, xm + 1, xr);
    t[x] = t[2 * x + 1] + t[2 * x + 2];
}

long long SegTree::sum(int l, int r, int x, int xl, int xr) {
    if (r < xl || l > xr) {
        return 0;
    }
    if (xl >= l && xr <= r) {
        return t[x];
    }
    int xm = (xl + xr) / 2;
    return sum(l, r, 2 * x + 1, xl, xm) +
    sum(l, r, 2 * x + 2, xm + 1, xr);
}

void SegTree::collect_values(int x, int xl, int xr, vector<int> &result) {
    push(x, xl, xr);
    if (xl == xr) {
        result[xl] = t[x];
        return;
    }
    int xm = (xl + xr) / 2;
    collect_values(2 * x + 1, xl, xm, result);
    collect_values(2 * x + 2, xm + 1, xr, result);
}
bool SegTree::is_valid_index(int index, int N) {
    return index >= 0 && index < N;
}
void SegTree::array_output(const vector<int> &arr, int N) {
    cout << "Ваш массив :\n";
    for (int i = 0; i < N; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}