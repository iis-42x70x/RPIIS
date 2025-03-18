#include "Tree.h"

Node* createNode(int l, int r) {
    Node* node = new Node();
    node->l = l;
    node->r = r;
    node->max = 0;
    node->add = 0;
    node->left = nullptr;
    node->right = nullptr;
    return node;
}

Node* buildTree(int l, int r, int* initialValues) {
    Node* node = createNode(l, r);
    if (l == r) {
        node->max = initialValues[l];
        return node;
    }
    int mid = (l + r) / 2;
    node->left = buildTree(l, mid, initialValues);
    node->right = buildTree(mid + 1, r, initialValues);

    node->max = max(node->left->max, node->right->max);
    return node;
}

void modify(Node* node, int l, int r, int val) {
    if (node->r < l || node->l > r) {
        return;
    }
    if (l <= node->l && node->r <= r) {
        node->add += val;
        node->max += val;
        return;
    }

    modify(node->left, l, r, val);
    modify(node->right, l, r, val);

    node->max = max(node->left->max, node->right->max) + node->add;
}

int query(Node* node, int l, int r) {
    if (node->r < l || node->l > r) {
        return INT_MIN;
    }
    if (l <= node->l && node->r <= r) {
        return node->max;
    }

    
    return max(query(node->left, l, r), query(node->right, l, r));
}

void collectValues(Node* root, int start, int end, int* output) {
    for (int i = start; i <= end; i++) {
        output[i] = query(root, i, i);
    }
}
