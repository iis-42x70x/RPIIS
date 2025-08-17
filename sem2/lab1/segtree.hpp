#include <vector>
using namespace std;

class SegmentTree {
public:
    SegmentTree(vector<int>& array) {
        n = (int)array.size();
        arr = array;
        key = 0;
        tree.resize(4 * n, 0);
        buildTree(arr, 0, 0, n);
    }

    void buildTree(vector<int>&, int, int, int);
    void rebuildTree(int);
    void rebuildTree(vector<int>&);
    int findCount(int, int, int, int, int);

    int findCount(int left, int right) {
        return findCount(0, left, right + 1, 0, n);
    }
private:
    vector<int> tree, arr;
    int n, key;
};
