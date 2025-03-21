#include <iostream>
#include <vector>

using namespace std;

class SegTree {

    public:
        vector<int> t, lazy;
        int n;
        SegTree(vector<int> &arr);
        void update_array (int l, int r, int v);
        long long get_sum(int l, int r);
        vector<int> get_final_array();
        bool is_valid_index(int index, int N);
        void array_output(const vector<int> &arr, int N);
    private :
        void build(vector<int> &arr, int v, int tl, int tr);
        void push (int v, int tl, int tr);
        void update(int l, int r, int v, int x, int xl, int xr);
        long long sum(int l, int r, int x, int xl, int xr);
        void collect_values(int x, int xl, int xr, vector<int> &result);

};