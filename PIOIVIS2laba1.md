# Лабоаторная работа 1
## Цели: 
*Исследовать свойства структур данных и разработать
библиотеку алгоритмов обработки структур данных*

## Задачи:
*1. Разработать библиотеку для работы со структурой данных, указанной в
индивидуальном задании, на любом императивнойм языке
программирования (Pascal, C\C++, Java, C#, Python и др.)*

*2. Разработать тестовую программу, которая демонстрирует
работоспособность реализованной библиотеки работы со структурой
данных.*

*3. По результатам выполнения задания составить отчет.*

## Вариант: 
*9.AVL-дерево. Вставка. Удаление. Поиск. Поиск минимума, максимума,
ближайшего большего и ближайшего меньшего.*

## Основные понятия:
АВЛ-дерево (англ. AVL-Tree) — сбалансированное двоичное дерево поиска, в котором поддерживается следующее свойство: для каждой его вершины высота её двух поддеревьев различается не более чем на 1.
АВЛ-дерево — это прежде всего двоичное дерево поиска, ключи которого удовлетворяют стандартному свойству: ключ любого узла дерева не меньше любого ключа в левом поддереве данного узла и не больше любого ключа в правом поддереве этого узла. 
*![image](https://github.com/user-attachments/assets/503fd034-c9ed-4963-8e4d-b7433db34cba)


## Описание алгоритмов:
Для работы со множествами я использую стандартный шаблон std:: vector.Вектор хранит элементы заданного типа в линейном расположении и обеспечивает быстрый случайный доступ к любому элементу. Для создания множества пользователю необходимо ввести его мощность и значение каждого элемента.В моей программе эта операция реализована следующим образом:
*Вставка элемента в дерево
```
struct node* insert(struct node* r, int data) {
    if (r == NULL) {
        struct node* n = new struct node;
        n->data = data;
        n->left = n->right = NULL;
        n->height = 1;
        return n;
    }
    else {
        if (data < r->data)
            r->left = insert(r->left, data);
        else
            r->right = insert(r->right, data);
    }

    r->height = max(calheight(r->left), calheight(r->right)) + 1;

    if (bf(r) == 2 && bf(r->left) == 1)
        return llrotation(r);
    if (bf(r) == -2 && bf(r->right) == -1)
        return rrrotation(r);
    if (bf(r) == -2 && bf(r->right) == 1)
        return rlrotation(r);
    if (bf(r) == 2 && bf(r->left) == -1)
        return lrrotation(r);

    return r;
}
```
Уровневая обходка AVL-дерева с указанием направлений и значений родителя
```
void levelorder_newline(struct node* v) {
    queue<pair<struct node*, string>> q; // Пара: узел и информация о родителе
    q.push({ v, "Корень (нет родителя)" });
    q.push({ NULL, "" });

    while (!q.empty()) {
        auto cur = q.front();
        q.pop();

        if (cur.first == NULL && q.size() != 0) {
            cout << "\n";
            q.push({ NULL, "" });
            continue;
        }

        if (cur.first != NULL) {
            cout << " " << cur.first->data << " (" << cur.second << ") ";

            if (cur.first->left != NULL)
                q.push({ cur.first->left, "Лево от " + to_string(cur.first->data) });

            if (cur.first->right != NULL)
                q.push({ cur.first->right, "Право от " + to_string(cur.first->data) });
        }
    }
}
```
Удаление элемента из дерева
```
struct node* deleteNode(struct node* r, int data) {
    if (r == NULL) return r;

    if (data < r->data)
        r->left = deleteNode(r->left, data);
    else if (data > r->data)
        r->right = deleteNode(r->right, data);
    else {
        if (r->left == NULL) {
            struct node* temp = r->right;
            delete r;
            return temp;
        }
        else if (r->right == NULL) {
            struct node* temp = r->left;
            delete r;
            return temp;
        }

        struct node* temp = minValueNode(r->right);
        r->data = temp->data;
        r->right = deleteNode(r->right, temp->data);
    }

    r->height = max(calheight(r->left), calheight(r->right)) + 1;

    if (bf(r) == 2 && bf(r->left) >= 0)
        return llrotation(r);
    if (bf(r) == 2 && bf(r->left) == -1)
        return lrrotation(r);
    if (bf(r) == -2 && bf(r->right) <= 0)
        return rrrotation(r);
    if (bf(r) == -2 && bf(r->right) == 1)
        return rlrotation(r);

    return r;
}
```
Нахождение уровня элемента
```
struct node* find(struct node* r, int data, int level) {
    if (r == NULL) return NULL;

    if (data == r->data) {
        cout << "Элемент найден на уровне: " << level << endl;
        return r;
    }
    else if (data < r->data)
        return find(r->left, data, level + 1);
    else
        return find(r->right, data, level + 1);
}
void search(int data) {
    struct node* res = find(root, data, 1);
    if (res == NULL) {
        cout << "Элемент не найден в дереве.\n";
    }
}
```
Нахождение максимального и минимального элементов в дереве
```
struct node* find_min(struct node* r) {
    while (r && r->left != NULL)
        r = r->left;
    return r;
}

struct node* find_max(struct node* r) {
    while (r && r->right != NULL)
        r = r->right;
    return r;
}
void print_min_max() {
    struct node* min = find_min(root);
    struct node* max = find_max(root);
    cout << "Минимальный элемент: " << (min ? min->data : -1) << endl; // NET MAX
    cout << "Максимальный элемент: " << (max ? max->data : -1) << endl;  // NET MIN
}
```
Нахождение максимального и минимального  ближайших к элементу
```
struct node* find_next_bigger(struct node* r, int data) {
    struct node* next = NULL;
    while (r != NULL) {
        if (data < r->data) {
            next = r;
            r = r->left;
        }
        else {
            r = r->right;
        }
    }
    return next;
}

struct node* find_next_smaller(struct node* r, int data) {
    struct node* next = NULL;
    while (r != NULL) {
        if (data > r->data) {
            next = r;
            r = r->right;
        }
        else {
            r = r->left;
        }
    }
    return next;
}
void print_next(int data) {
    struct node* exists = find(root, data, 1); //существует ли 
    if (!exists) {
        cout << "Элемент " << data << " не найден в дереве. Невозможно найти ближайшие значения." << endl;
        return;
    }

    struct node* bigger = find_next_bigger(root, data);
    struct node* smaller = find_next_smaller(root, data);

    cout << "Ближайший больший элемент: " << (bigger ? bigger->data : -1) << endl;
    cout << "Ближайший меньший элемент: " << (smaller ? smaller->data : -1) << endl;
}
```

## Тестовая программа:
```
#include <iostream>
#include <queue>
#include <sstream>

using namespace std;

struct node {
    struct node* left;
    int data;
    int height;
    struct node* right;
};

class AVL {
private:
    struct node* root;

public:
    AVL() {
        this->root = NULL;
    }

    int calheight(struct node* p) {
        if (p == NULL) return 0;
        return p->height;
    }

    int bf(struct node* n) {
        if (n == NULL) return 0;
        return calheight(n->left) - calheight(n->right);
    }

    struct node* llrotation(struct node* n) {
        struct node* tp = n->left;
        n->left = tp->right;
        tp->right = n;
        n->height = max(calheight(n->left), calheight(n->right)) + 1;
        tp->height = max(calheight(tp->left), calheight(tp->right)) + 1;
        return tp;
    }

    struct node* rrrotation(struct node* n) {
        struct node* tp = n->right;
        n->right = tp->left;
        tp->left = n;
        n->height = max(calheight(n->left), calheight(n->right)) + 1;
        tp->height = max(calheight(tp->left), calheight(tp->right)) + 1;
        return tp;
    }

    struct node* rlrotation(struct node* n) {
        n->right = llrotation(n->right);
        return rrrotation(n);
    }

    struct node* lrrotation(struct node* n) {
        n->left = rrrotation(n->left);
        return llrotation(n);
    }

    struct node* insert(struct node* r, int data) {
        if (r == NULL) {
            struct node* n = new struct node;
            n->data = data;
            n->left = n->right = NULL;
            n->height = 1;
            return n;
        }
        else {
            if (data < r->data)
                r->left = insert(r->left, data);
            else
                r->right = insert(r->right, data);
        }

        r->height = max(calheight(r->left), calheight(r->right)) + 1;

        if (bf(r) == 2 && bf(r->left) == 1)
            return llrotation(r);
        if (bf(r) == -2 && bf(r->right) == -1)
            return rrrotation(r);
        if (bf(r) == -2 && bf(r->right) == 1)
            return rlrotation(r);
        if (bf(r) == 2 && bf(r->left) == -1)
            return lrrotation(r);

        return r;
    }

    struct node* minValueNode(struct node* n) {
        struct node* current = n;
        while (current && current->left != NULL)
            current = current->left;
        return current;
    }

    struct node* deleteNode(struct node* r, int data) {
        if (r == NULL) return r;

        if (data < r->data)
            r->left = deleteNode(r->left, data);
        else if (data > r->data)
            r->right = deleteNode(r->right, data);
        else {
            if (r->left == NULL) {
                struct node* temp = r->right;
                delete r;
                return temp;
            }
            else if (r->right == NULL) {
                struct node* temp = r->left;
                delete r;
                return temp;
            }

            struct node* temp = minValueNode(r->right);
            r->data = temp->data;
            r->right = deleteNode(r->right, temp->data);
        }

        r->height = max(calheight(r->left), calheight(r->right)) + 1;

        if (bf(r) == 2 && bf(r->left) >= 0)
            return llrotation(r);
        if (bf(r) == 2 && bf(r->left) == -1)
            return lrrotation(r);
        if (bf(r) == -2 && bf(r->right) <= 0)
            return rrrotation(r);
        if (bf(r) == -2 && bf(r->right) == 1)
            return rlrotation(r);

        return r;
    }

    void levelorder_newline() {
        if (this->root == NULL) {
            cout << "\nПустое дерево\n";
            return;
        }
        levelorder_newline(this->root);
    }



    void levelorder_newline(struct node* v) {
        queue<pair<struct node*, string>> q; // Пара: узел и информация о родителе
        q.push({ v, "Корень (нет родителя)" });
        q.push({ NULL, "" });

        while (!q.empty()) {
            auto cur = q.front();
            q.pop();

            if (cur.first == NULL && q.size() != 0) {
                cout << "\n";
                q.push({ NULL, "" });
                continue;
            }

            if (cur.first != NULL) {
                cout << " " << cur.first->data << " (" << cur.second << ") ";

                if (cur.first->left != NULL)
                    q.push({ cur.first->left, "Лево от " + to_string(cur.first->data) });

                if (cur.first->right != NULL)
                    q.push({ cur.first->right, "Право от " + to_string(cur.first->data) });
            }
        }
    }




    void insert(int data) {
        root = insert(root, data);
    }

    void deleteNode(int data) {
        root = deleteNode(root, data);
    }



    struct node* find(struct node* r, int data, int level) {
        if (r == NULL) return NULL;

        if (data == r->data) {
            cout << "Элемент найден на уровне: " << level << endl;
            return r;
        }
        else if (data < r->data)
            return find(r->left, data, level + 1);
        else
            return find(r->right, data, level + 1);
    }

    struct node* find_min(struct node* r) {
        while (r && r->left != NULL)
            r = r->left;
        return r;
    }

    struct node* find_max(struct node* r) {
        while (r && r->right != NULL)
            r = r->right;
        return r;
    }

    struct node* find_next_bigger(struct node* r, int data) {
        struct node* next = NULL;
        while (r != NULL) {
            if (data < r->data) {
                next = r;
                r = r->left;
            }
            else {
                r = r->right;
            }
        }
        return next;
    }

    struct node* find_next_smaller(struct node* r, int data) {
        struct node* next = NULL;
        while (r != NULL) {
            if (data > r->data) {
                next = r;
                r = r->right;
            }
            else {
                r = r->left;
            }
        }
        return next;
    }

    void search(int data) {
        struct node* res = find(root, data, 1);
        if (res == NULL) {
            cout << "Элемент не найден в дереве.\n";
        }
    }

    void print_min_max() {
        struct node* min = find_min(root);
        struct node* max = find_max(root);
        cout << "Минимальный элемент: " << (min ? min->data : -1) << endl; // NET MAX
        cout << "Максимальный элемент: " << (max ? max->data : -1) << endl;  // NET MIN
    }

    void print_next(int data) {
        struct node* exists = find(root, data, 1); //существует ли 
        if (!exists) {
            cout << "Элемент " << data << " не найден в дереве. Невозможно найти ближайшие значения." << endl;
            return;
        }

        struct node* bigger = find_next_bigger(root, data);
        struct node* smaller = find_next_smaller(root, data);

        cout << "Ближайший больший элемент: " << (bigger ? bigger->data : -1) << endl;
        cout << "Ближайший меньший элемент: " << (smaller ? smaller->data : -1) << endl;
    }


};





int main() {

    setlocale(LC_ALL, "Russian");
    AVL tree;
    int t,a,del;

    cout << "Введите количество узлов:\n";
    if (cin) {
        cin >> t;
    }
    else  return 1;

    cout << endl;

    cout << "Введите значение узлов:\n";

     for (int i = 0; i < t; i++) {
         if (cin)
             cin >> a;
         else return 1;
        // Вставка узлов
        tree.insert(a);
    }



   


    cout << endl;
    cout << "Уровневая обходка AVL-дерева с указанием направлений и значений родителя:\n";
    tree.levelorder_newline();
    cout << endl;



    // Удаление узла
    cout << "Элемент удаления:\n";
    cin >> del;
    tree.deleteNode(del);
    cout << endl;

    cout << endl;
    cout << "Уровневая обходка AVL-дерева с указанием направлений и значений родителя:\n";
    tree.levelorder_newline();
    cout << endl;



    cout << "Введите элемент для поиска уровня:\n";
    int search_data;
    cin >> search_data; cout << endl;
    tree.search(search_data);
    cout << endl;


    cout << "Минимум и максимум дерева:\n";
    tree.print_min_max();
    cout << endl;



    cout << "Введите элемент для поиска ближайших большего и меньшего:\n";
    int next_data;
    cin >> next_data; cout << endl;
    tree.print_next(next_data);
    cout << endl;


    




    return 0;
}
```
## Вывод: 
в ходе лабораторной работы освоили навыки работы со структурами и классами языка программирования C++. Разработали код для создания AVL-деревьев с помощью std::vector, проверки их правильности, вставку и удаление элементов, а также нахождение максимума и минимума в дереве,максимального и минимального блтжнего к элементу.
## Источники:

AVL-дерево:
https://habr.com/en/articles/150732/

AVL-дерево в С++:
https://rsdn.org/article/alg/bintree/avl.xml
