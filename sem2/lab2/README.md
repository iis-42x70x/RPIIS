<h1>Лабараторная работа #2</h1>

## Цели работы:

* Изучить базовые понятия теории множеств
* Научиться реализовывать основные алгоритмы при работе со множествами

## Задачи:

* Разработать библиотеку для работы со множествами на любом императивном языке программирования
* Разработать тесты, которые демонстрирует работоспособность реализованной библиотеки

## Вариант:

3. Реализовать программу, формирующую множество равное симметрической разности произвольного количества исходных множеств (без учёта кратных вхождений элементов).

## Понятия:

<h4>Множество – простейшая информационная конструкция и математическая структура,позволяющая рассматривать какие-то объекты как целое, связывая их.</h4>
<h4>Элементы множества – объекты, связываемые некоторым множеством.</h4>
<h4>Множества бывают:</h4>

* Ориентированными (важен порядок элементов во множестве)
* Неориентированными (порядок элементов во множестве не важен)

<h4>Множество может быть задано с помощью:</h4>

* Механизма
* Процедуры
   * Разрешающая процедура - процедура, которая даёт ответ для любого объекта: является он или нет элементом некоторого множества
   * Порождающей процедура - процелура, которая позволяет получить любой новый элемент некоторого множества, отличный от известных или выданных ранее элементов этого множества.

<h4>Определение симметрической разности (для обычных множеств)</h4>

Симметрической разностью множеств $A$ и $B$ называется множество $S$, содержащее элементы, которые принадлежат ровно одному из исходных множеств:

$$
A \triangle B = (A \setminus B) \cup (B \setminus A)
$$

**Пример:**
```math
\begin{aligned}
A &= \{a, b, c, d\} \\
B &= \{b, c, e, f\} \\
A \triangle B &= \{a, d, e, f\}
\end{aligned}
```

## Структура программы:

<p align="center">
   <img alt="Пример B-дерева" src="https://github.com/iis-42x70x/RPIIS/blob/Говор_Г/sem2/lab1/img/2.png">
</p>

### Прилагаемые файлы:
* [main.cpp](https://github.com/iis-42x70x/RPIIS/blob/Говор_Г/sem2/lab1/code/main.cpp) - тесты
* [BTree.cpp](https://github.com/iis-42x70x/RPIIS/blob/Говор_Г/sem2/lab1/code/BTree.cpp) - реализация
* [BTree.hpp](https://github.com/iis-42x70x/RPIIS/blob/Говор_Г/sem2/lab1/code/BTree.hpp) - декларация

## Тесты:
* Тест 1
  
<p align="center">
   <img width = "700px" alt="Пример B-дерева" src="https://github.com/iis-42x70x/RPIIS/blob/Говор_Г/sem2/lab1/img/4.1.png">
</p>

* Тест 2
  
<p align="center">
   <img width = "700px" alt="Пример B-дерева" src="https://github.com/iis-42x70x/RPIIS/blob/Говор_Г/sem2/lab1/img/4.2.png">
</p>

* Тест 3
  
<p align="center">
   <img width = "700px" alt="Пример B-дерева" src="https://github.com/iis-42x70x/RPIIS/blob/Говор_Г/sem2/lab1/img/4.3.png">
</p>

* Тест 4
  
<p align="center">
   <img width = "700px" alt="Пример B-дерева" src="https://github.com/iis-42x70x/RPIIS/blob/Говор_Г/sem2/lab1/img/4.4.png">
</p>

* Тест 5
  
<p align="center">
   <img width = "700px" alt="Пример B-дерева" src="https://github.com/iis-42x70x/RPIIS/blob/Говор_Г/sem2/lab1/img/4.5.png">
</p>

## Алгоритмы работы с B-деревьями(BTree.cpp): 

### Обход дерева
  
```C++
void BTreeNode::traverse() {
    int i;
    for (i = 0; i < n; i++) {
        if (!leaf) children[i]->traverse();
        std::cout << keys[i] << " ";
    }
    if (!leaf) children[i]->traverse();
}

void BTree::traverse() {
    if (root) root->traverse();
}
```

* Обходит узел в порядке in-order (сначала дети, затем ключи).
* Рекурсивно вызывает traverse() для всех дочерних узлов.

### Поиск ключа в дереве
  
```C++
BTreeNode* BTreeNode::search(int k) {
    int i = 0;
    while (i < n && k > keys[i]) i++;
    if (keys[i] == k) return this;
    if (leaf) return nullptr;
    return children[i]->search(k);
}

BTreeNode* BTree::search(int k) {
    return root ? root->search(k) : nullptr;
}

```

* Выполняет линейный поиск в массиве ключей текущего узла.
* Если ключ найден в текущем узле — возвращает указатель на этот узел.
* Если узел является листом и ключ не найден — возвращает nullptr.
* Иначе рекурсивно ищет ключ в нужном дочернем узле.

### Вставка ключа
  
```C++
bool BTree::insert(int k) {
    if (BTree::search(k) != nullptr) {
        return false;
    }
    if (!root) {
        root = new BTreeNode(t, true);
        root->keys[0] = k;
        root->n = 1;
    }
    else {
        if (root->n == 2 * t - 1) {
            BTreeNode* s = new BTreeNode(t, false);
            s->children[0] = root;
            s->splitChild(0, root);
            int i = (s->keys[0] < k) ? 1 : 0;
            s->children[i]->insertNonFull(k);
            root = s;
        }
        else {
            root->insertNonFull(k);
        }
    }
}
```

* Проверяет, существует ли ключ (search(k)).
* Если дерево пустое, создаёт корень.
* Если корень полон, создаёт новый узел, делает старый корнем его дочерним узлом и разбивает старый корень.
* Вставляет ключ в неполный узел.

### Вставка ключа, если нода заполнена не до конца(<2t-1)

```C++
void BTreeNode::insertNonFull(int k) {
    int i = n - 1;
    if (leaf) {
        while (i >= 0 && keys[i] > k) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = k;
        n++;
    }
    else {
        while (i >= 0 && keys[i] > k) i--;
        if (children[i + 1]->n == 2 * t - 1) {
            splitChild(i + 1, children[i + 1]);
            if (keys[i + 1] < k) i++;
        }
        children[i + 1]->insertNonFull(k);
    }
}
```

* Если узел лист, вставляет ключ в правильное место, сдвигая элементы вправо.
* Если узел не лист, рекурсивно спускается в нужного потомка.
* Если у потомка уже 2*t - 1 ключей, разбивает его перед вставкой.

### Разбиение дочерних нод(Если это требуется)
  
```C++
void BTreeNode::splitChild(int i, BTreeNode* y) {
    BTreeNode* z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;
    for (int j = 0; j < t - 1; j++) z->keys[j] = y->keys[j + t];
    if (!y->leaf) {
        for (int j = 0; j < t; j++) z->children[j] = y->children[j + t];
    }
    y->n = t - 1;
    for (int j = n; j >= i + 1; j--) children[j + 1] = children[j];
    children[i + 1] = z;
    for (int j = n - 1; j >= i; j--) keys[j + 1] = keys[j];
    keys[i] = y->keys[t - 1];
    n++;
}
```

* Разбивает узел y, у которого 2*t - 1 ключей.
* Создаёт новый узел z и переносит в него вторую половину ключей из y.
* Средний ключ перемещается в родительский узел.
* Обновляет массив children[] у родителя.

### Удаление ключа

```C++
void BTree::remove(int k) {
    if (!root) return;
    root->remove(k);
    if (root->n == 0) {
        BTreeNode* tmp = root;
        root = root->leaf ? nullptr : root->children[0];
        delete tmp;
    }
}

void BTreeNode::remove(int k) {
    int idx = findKey(k);
    if (idx < n && keys[idx] == k) {
        if (leaf) removeFromLeaf(idx);
        else removeFromNonLeaf(idx);
    }
    else {
        if (leaf) return;
        bool lastChild = (idx == n);
        if (children[idx]->n < t) fill(idx);
        if (lastChild && idx > n) children[idx - 1]->remove(k);
        else children[idx]->remove(k);
    }
}

int BTreeNode::findKey(int k) {
    int idx = 0;
    while (idx < n && keys[idx] < k) ++idx;
    return idx;
}
```

* Ищет ключ в узле:
* * Если ключ в листе → удаляет его (removeFromLeaf).
* * Если ключ внутренний → заменяет его преемником (removeFromNonLeaf).
* Если ключа нет, рекурсивно удаляет его из нужного дочернего узла.
* Если у узла перед удалением меньше t ключей, выполняет балансировку (fill).

### Удаление ключа из листа

```C++
void BTreeNode::removeFromLeaf(int idx) {
    for (int i = idx + 1; i < n; i++) keys[i - 1] = keys[i];
    n--;
}
```

* Просто сдвигает ключи влево и уменьшает n

### Удаление ключа не из листа

```C++
void BTreeNode::removeFromNonLeaf(int idx) {
    int k = keys[idx];
    if (children[idx]->n >= t) {
        int pred = getPred(idx);
        keys[idx] = pred;
        children[idx]->remove(pred);
    }
    else if (children[idx + 1]->n >= t) {
        int succ = getSucc(idx);
        keys[idx] = succ;
        children[idx + 1]->remove(succ);
    }
    else {
        merge(idx);
        children[idx]->remove(k);
    }
}
```

* Ключ заменяется предшественником или преемником:
* * Если children[idx] содержит >= t ключей → заменяет предшественником.
* * Иначе, если children[idx+1] содержит >= t ключей → заменяет преемником.
* * Если оба узла имеют менее t ключей, объединяет их и удаляет ключ из объединённого узла.

### Нахождение предшествующего ключа

```C++
int BTreeNode::getPred(int idx) {
    BTreeNode* cur = children[idx];
    while (!cur->leaf) cur = cur->children[cur->n];
    return cur->keys[cur->n - 1];
}
```

* Спускается вправо по левому поддереву, пока не дойдёт до листа.

### Нахождение преемника ключа

```C++
int BTreeNode::getSucc(int idx) {
    BTreeNode* cur = children[idx + 1];
    while (!cur->leaf) cur = cur->children[0];
    return cur->keys[0];
}
```

* Спускается влево по правому поддереву, пока не дойдёт до листа.

### Балансировка узла

```C++
void BTreeNode::fill(int idx) {
    if (idx != 0 && children[idx - 1]->n >= t) borrowFromPrev(idx);
    else if (idx != n && children[idx + 1]->n >= t) borrowFromNext(idx);
    else {
        if (idx != n) merge(idx);
        else merge(idx - 1);
    }
}
```

* Если children[idx] имеет менее t ключей:
* * Если children[idx-1] имеет >= t ключей → заимствует ключ из него (borrowFromPrev).
* * Иначе, если children[idx+1] имеет >= t ключей → заимствует ключ (borrowFromNext).
* * Если у обоих соседей менее t ключей → объединяет с соседом (merge).


### Заимствование ключа у левого и правого соседов

```C++
void BTreeNode::borrowFromPrev(int idx) {
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx - 1];
    for (int i = child->n - 1; i >= 0; i--) child->keys[i + 1] = child->keys[i];
    if (!child->leaf) {
        for (int i = child->n; i >= 0; i--) child->children[i + 1] = child->children[i];
    }
    child->keys[0] = keys[idx - 1];
    if (!child->leaf) child->children[0] = sibling->children[sibling->n];
    keys[idx - 1] = sibling->keys[sibling->n - 1];
    child->n++;
    sibling->n--;
}

void BTreeNode::borrowFromNext(int idx) {
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx + 1];
    child->keys[child->n] = keys[idx];
    keys[idx] = sibling->keys[0];
    if (!child->leaf) {
        child->children[child->n + 1] = sibling->children[0];
    }
    for (int i = 1; i < sibling->n; i++) {
        sibling->keys[i - 1] = sibling->keys[i];
    }
    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->n; i++) {
            sibling->children[i - 1] = sibling->children[i];
        }
    }
    child->n++;
    sibling->n--;
}
```

### Объединение с соседним узлом

```C++
void BTreeNode::merge(int idx) {
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx + 1];
    child->keys[t - 1] = keys[idx];
    for (int i = 0; i < sibling->n; i++) {
        child->keys[i + t] = sibling->keys[i];
    }
    if (!child->leaf) {
        for (int i = 0; i <= sibling->n; i++) {
            child->children[i + t] = sibling->children[i];
        }
    }
    for (int i = idx + 1; i < n; i++) {
        keys[i - 1] = keys[i];
    }
    for (int i = idx + 2; i <= n; i++) {
        children[i - 1] = children[i];
    }
    child->n += sibling->n + 1;
    n--;
    delete sibling;
}
```

* Объединяет children[idx] и children[idx+1], перемещая ключ из родителя вниз.
* Удаляет children[idx+1] и уменьшает количество ключей в родителе.

## Вывод:
* Мной была разработана библиотека по работе с B-деревьями. В ней я реализовал основные операции над B-деревом: вставка ключа, удаление ключа, поиск ключа, обход дерева.

## Материалы и источники:

* [YouTube](https://www.youtube.com/watch?v=WXXetwePSRk) - подробное объяснение принципа работы с B-деревьями от Volodya Mozhenkov с помощью видиоматериалы
* [Викиконспекты](https://neerc.ifmo.ru/wiki/index.php?title=B-дерево) - особенности реализации B-деревьев на C++
* [Draw.io](draw.io) - платформа для составление схем, блок-схем
