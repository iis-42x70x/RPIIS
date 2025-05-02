#include "Header.h"
#include <iostream>
#include <string>

node::node(int val) : data(val), parent(nullptr), left(nullptr), right(nullptr), color(false) {}

RBTree::RBTree() : root(nullptr) {}

node* RBTree::most_right(node* z) {
    if (!z) return nullptr;

    if (z->right) {
        return minimum(z->right);
    }

    node* parent = z->parent;
    while (parent && z == parent->right) {
        z = parent;
        parent = parent->parent;
    }
    return parent;
}

node* RBTree::most_left(node* z) {
    if (!z) return nullptr;

    if (z->left) {
        return maximum(z->left);
    }

    node* parent = z->parent;
    while (parent && z == parent->left) {
        z = parent;
        parent = parent->parent;
    }
    return parent;
}

node* RBTree::search(int inf) {
    node* current = root;
    while (current && current->data != inf) {
        if (inf < current->data) {
            current = current->left;
        }
        else {
            current = current->right;
        }
    }
    return current;
}

node* RBTree::maximum(node* z) {
    if (!z) {
        std::cout << "Дерево пусто.\n";
        return nullptr;
    }
    while (z->right) {
        z = z->right;
    }
    return z;
}

node* RBTree::minimum(node* z) {
    if (!z) {
        std::cout << "Дерево пусто.\n";
        return nullptr;
    }
    while (z->left) {
        z = z->left;
    }
    return z;
}

void RBTree::LEFT_ROTATE(node* x) {
    node* y = x->right;
    x->right = y->left;
    if (y->left) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (!x->parent) {
        root = y;
    }
    else if (x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void RBTree::RIGHT_ROTATE(node* x) {
    node* y = x->left;
    x->left = y->right;
    if (y->right) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (!x->parent) {
        root = y;
    }
    else if (x == x->parent->right) {
        x->parent->right = y;
    }
    else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

void RBTree::RB_INSERT(int inf) {
    node* z = new node(inf);
    node* y = nullptr;
    node* x = root;

    while (x) {
        y = x;
        if (z->data < x->data) {
            x = x->left;
        }
        else if (z->data > x->data) {
            x = x->right;
        }
        else {
            std::cout << "Узел уже существует.\n";
            delete z;
            return;
        }
    }

    z->parent = y;
    if (!y) {
        root = z;
    }
    else if (z->data < y->data) {
        y->left = z;
    }
    else {
        y->right = z;
    }

    RB_INSERT_FIXUP(z);
    std::cout << "Узел успешно создан.\n";
}

void RBTree::RB_INSERT_FIXUP(node* z) {
    while (z->parent && !z->parent->color) {
        if (z->parent == z->parent->parent->left) {
            node* y = z->parent->parent->right;
            if (y && !y->color) {
                z->parent->color = true;
                y->color = true;
                z->parent->parent->color = false;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->right) {
                    z = z->parent;
                    LEFT_ROTATE(z);
                }
                z->parent->color = true;
                z->parent->parent->color = false;
                RIGHT_ROTATE(z->parent->parent);
            }
        }
        else {
            node* y = z->parent->parent->left;
            if (y && !y->color) {
                z->parent->color = true;
                y->color = true;
                z->parent->parent->color = false;
                z = z->parent->parent;
            }
            else {
                if (z == z->parent->left) {
                    z = z->parent;
                    RIGHT_ROTATE(z);
                }
                z->parent->color = true;
                z->parent->parent->color = false;
                LEFT_ROTATE(z->parent->parent);
            }
        }
    }
    root->color = true;
}

void RBTree::RB_TRANSPLANT(node* u, node* v) {
    if (!u->parent) {
        root = v;
    }
    else if (u == u->parent->left) {
        u->parent->left = v;
    }
    else {
        u->parent->right = v;
    }
    if (v) {
        v->parent = u->parent;
    }
}

void RBTree::RB_DELETE(int inf) {
    node* z = search(inf);
    if (!z) {
        std::cout << "Узел для удаления не найден.\n";
        return;
    }

    node* y = z;
    node* x;
    bool y_original_color = y->color;

    if (!z->left) {
        x = z->right;
        RB_TRANSPLANT(z, z->right);
    }
    else if (!z->right) {
        x = z->left;
        RB_TRANSPLANT(z, z->left);
    }
    else {
        y = minimum(z->right);
        y_original_color = y->color;
        x = y->right;

        if (y->parent == z) {
            if (x) x->parent = y;
        }
        else {
            RB_TRANSPLANT(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        RB_TRANSPLANT(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    delete z;

    if (y_original_color) {
        RB_DELETE_FIXUP(x);
    }
    std::cout << "Узел успешно удалён.\n";
}

void RBTree::RB_DELETE_FIXUP(node* x) {
    while (x && x != root && x->color) {
        if (x == x->parent->left) {
            node* w = x->parent->right;
            if (w && !w->color) {
                w->color = true;
                x->parent->color = false;
                LEFT_ROTATE(x->parent);
                w = x->parent->right;
            }
            if ((!w->left || w->left->color) && (!w->right || w->right->color)) {
                if (w) w->color = false;
                x = x->parent;
            }
            else {
                if (!w->right || w->right->color) {
                    if (w->left) w->left->color = true;
                    if (w) w->color = false;
                    RIGHT_ROTATE(w);
                    w = x->parent->right;
                }
                if (w) {
                    w->color = x->parent->color;
                    if (w->right) w->right->color = true;
                }
                x->parent->color = true;
                LEFT_ROTATE(x->parent);
                x = root;
            }
        }
        else {
            node* w = x->parent->left;
            if (w && !w->color) {
                w->color = true;
                x->parent->color = false;
                RIGHT_ROTATE(x->parent);
                w = x->parent->left;
            }
            if ((!w->right || w->right->color) && (!w->left || w->left->color)) {
                if (w) w->color = false;
                x = x->parent;
            }
            else {
                if (!w->left || w->left->color) {
                    if (w->right) w->right->color = true;
                    if (w) w->color = false;
                    LEFT_ROTATE(w);
                    w = x->parent->left;
                }
                if (w) {
                    w->color = x->parent->color;
                    if (w->left) w->left->color = true;
                }
                x->parent->color = true;
                RIGHT_ROTATE(x->parent);
                x = root;
            }
        }
    }
    if (x) x->color = true;
}

void RBTree::printTree(node* r, int space, int height) {
    if (!r) return;

    space += height;
    printTree(r->right, space);

    std::cout << std::endl;
    for (int i = height; i < space; i++) std::cout << " ";
    std::cout << r->data << (r->color ? "(B)" : "(R)") << "\n";

    printTree(r->left, space);
}

void RBTree::print_2(node* r, std::string indent, bool last) {
    if (r) {
        std::cout << indent;
        if (last) {
            std::cout << "R----";
            indent += "     ";
        }
        else {
            std::cout << "L----";
            indent += "|    ";
        }

        std::string sColor = r->color ? "BLACK" : "RED";
        std::cout << r->data << "(" << sColor << ")" << std::endl;

        if (r->left || r->right) {
            print_2(r->left, indent, false);
            print_2(r->right, indent, true);
        }
    }
}

void RBTree::test_f() {
    std::cout << "Введите значения: ";
    int a[9];
    for (int i = 0; i < 9; i++) {
        std::cin >> a[i];
        RB_INSERT(a[i]);
    }
    std::cout << "Добавление в дерево элементов";
    for (int i = 0; i < 9; i++) {
        std::cout << " " << a[i];
    }
    print_2(getRoot(), "", true);
    std::cout << "Удаление элемента со значением" << a[5] << "\n";
    RB_DELETE(a[5]);
    print_2(getRoot(), "", true);
    minimum(getRoot());
    maximum(getRoot());
    node* found = search(a[4]);
    node* least = most_left(found);
    std::cout << "Ближайший меньший элемент к элементу " << a[4] << ": " << least->data << std::endl;
    node* least1 = most_right(found);
    std::cout << "Ближайший больший элемент к элементу " << a[4] << ": " << least1->data << std::endl;
}//
// Created by aleks on 02.05.2025.
//
