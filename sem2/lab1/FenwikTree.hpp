#include <iostream>
#include <vector>
using namespace std;

class FenwickTree {
private:
    vector<long long> mass;
    vector<long long> core;
    int num;

public:
    FenwickTree(int size) : num(size), mass(size + 1, 0), core(size + 1, 0) {}


    long long sum(int count) {
        long long summa = 0;
        for (int i = count; i >= 0; i = (i & (i + 1)) - 1)
            summa += mass[i];
        return summa;
    }


    void update(int position, long long value) {
        for (int j = position; j <= num; j = j | (j + 1))
            mass[j] += value;
    }

    void set(int position, long long value) {
        long long delta = value - core[position];
        update(position, delta);
        core[position] = value;
    }

    long long query(int l, int r) {
        return sum(r) - sum(l - 1);
    }
};