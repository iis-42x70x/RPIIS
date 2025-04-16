# Лабораторная работа №1
## Условие задания (Вариант 8)
Декартово дерево. Вставка. Поиск. Удаление. Построение дерева из массива значений. Объединение двух деревьев. Пересечение двух деревьев.

----

**Цель:** Исследовать свойства структур данных и разработать библиотеку алгоритмов обработки структур данных.

**Задача:** Разработать библиотеку для работы со структурой данных и систему тестов, которые продемонстрировали бы работоспособность реализованной библиотеки.

----

# Список понятий:
`Декартово дерево (Treap)` — структура данных, объединяющая свойства бинарного дерева поиска (BST) и бинарной кучи.

`Приоритет` — случайное или заданное число, определяющее структуру дерева (поддерживает свойство кучи).

`Ключ` — значение, по которому строится бинарное дерево поиска (BST-свойство).

# Алгоритм работы декартового дерева:
## 1. Структура узла

**Каждый узел содержит:**

- Ключ (key) — значение, по которому строится BST.
- Приоритет (priority) — случайное число, определяющее структуру кучи.
- Левый и правый указатели (left, right) — ссылки на поддеревья.
```cpp
struct Node {
    int key;
    int priority;
    Node* left;
    Node* right;

    Node(int k) : key(k), priority(rand()), left(NULL), right(NULL) {}
};
```
## 2. Основные операции
**Вставка (Insert)**
1. Если дерево пустое → создаем новый узел.
2. Если ключ меньше текущего узла → вставляем в левое поддерево.
3. Если приоритет левого потомка больше текущего → делаем правый поворот.
4. Если ключ больше или равен → вставляем в правое поддерево.
5. Если приоритет правого потомка больше → делаем левый поворот.
```cpp
Node* insert(Node* root, int key) {
    if (!root) return new Node(key);

    if (key < root->key) {
        root->left = insert(root->left, key);
        if (root->left->priority > root->priority) {
            Node* temp = root;
            root = root->left;
            temp->left = root->right;
            root->right = temp;
        }
    }
    else {
        root->right = insert(root->right, key);
        if (root->right->priority > root->priority) {
            Node* temp = root;
            root = root->right;
            temp->right = root->left;
            root->left = temp;
        }
    }
    return root;
}
```
**Разделение (Split)**
1. Разделяет дерево на два:
- `left` — все ключи ≤ заданному.
- `right` — все ключи > заданному.
```cpp
void split(Node* root, int key, Node*& left, Node*& right) {
    if (!root) {
        left = right = NULL;
    }
    else if (root->key <= key) {
        split(root->right, key, root->right, right);
        left = root;
    }
    else {
        split(root->left, key, left, root->left);
        right = root;
    }
}
```
**Слияние (Merge)**
1. Сливает два дерева в одно, сохраняя свойства Treap.
2. Работает, только если все ключи `left` < ключей `right`.
```cpp
Node* merge(Node* left, Node* right) {
    if (!left || !right) return left ? left : right;

    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        return left;
    }
    else {
        right->left = merge(left, right->left);
        return right;
    }
}
```
**Удаление (Remove)**
1. Если ключ найден → удаляем узел и сливаем его поддеревья.
2. Иначе рекурсивно идем влево/вправо.
```cpp
Node* remove(Node* root, int key) {
    if (!root) return NULL;

    if (key < root->key) {
        root->left = remove(root->left, key);
    }
    else if (key > root->key) {
        root->right = remove(root->right, key);
    }
    else {
        Node* temp = root;
        root = merge(root->left, root->right);
        delete temp;
    }
    return root;
}
```
**Поиск (Search))**
1. Стандартный BST-поиск.
```cpp
bool search(Node* root, int key) {
    if (!root) return false;

    if (key < root->key) return search(root->left, key);
    else if (key > root->key) return search(root->right, key);
    else return true;
}
```
## 3. Дополнительные операции
**Объединение (Union)**
1. Собираем ключи из второго дерева.
2. Вставляем их в первое, если их там нет.
```cpp
Node* unionTreaps(Node* treap1, Node* treap2) {
    vector<int> keys;
    collectKeys(treap2, keys);

    Node* result = treap1;
    for (int key : keys) {
        if (!search(result, key)) {
            result = insert(result, key);
        }
    }
    return result;
}
```
**Пересечение (Intersection)**
1. Собираем ключи из первого дерева.
2. Вставляем их в результат, если они есть во втором.
```cpp
Node* intersectionTreaps(Node* treap1, Node* treap2) {
    vector<int> keys;
    collectKeys(treap1, keys);

    Node* result = NULL;
    for (int key : keys) {
        if (search(treap2, key)) {
            result = insert(result, key);
        }
    }
    return result;
}
```
**Обход (Inorder Traversal)**
1. Рекурсивный обход: левое поддерево → корень → правое поддерево.
```cpp
void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        cout << "Key: " << root->key << " Priority: " << root->priority << endl;
        inorder(root->right);
    }
}
```
## 4. Пример работы (Main Menu)
```cpp
int main() {
    Node* root = NULL;
    int choice, value;

    while (true) {
        printMenu();
        cin >> choice;

        switch (choice) {
            case 1: // Создать новое дерево
            case 2: // Вставить элемент
            case 3: // Удалить элемент
            case 4: // Поиск элемента
            case 5: // Объединение
            case 6: // Пересечение
            case 7: // Вывод дерева
            case 8: // Выход
            default: // Неверный ввод
        }
    }
    return 0;
}
```
# Пример работы программы:
