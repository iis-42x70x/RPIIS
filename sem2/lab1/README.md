<h1 align="center">Лабораторная работа 1 </h1>

## Цель работы 
Исследовать свойства структуры данных и разработать библиотеку алгоритмов обработки структуры данных

## Постановка задачи

1. Разработать библиотеку для работы со структурой данных, указанной в
индивидуальном задании, на языке программирования C++
2. Разработать тестовую программу, которая демонстрирует
работоспособность реализованной библиотеки работы со структурой
данных.
3. По результатам выполнения задания составить отчет.

## Вариант 
Мой вариант - 13. Структура данных - красно-черное дерево. Необходимо разработать функции вставки, удаления, поиска; поиска минимума, максимума, ближайшего большего и ближайшего меньшего элемента.

## Список используемых понятий

## Красно-черное дерево
Красно-чёрные деревья - это деревья поиска, которые используются для автоматического балансирования данных в многих приложениях. Они часто используются в стандартной библиотеке C++, включая контейнеры set и map, а также в языке Java в классе TreeMap.

Пример красно-черного дерева:

<img src="pics\p1.svg" width="600" alt="1">

Красно-чёрные деревья более популярны, чем идеально сбалансированные деревья, поскольку они более эффективны при операциях удаления и вставки элементов. Вставка и удаление в красно-чёрных деревьях требует операций перекраски, которые в большинстве случаев занимают O(log n) или O(1) времени и не более чем трёх поворотов дерева. Хотя вставка и удаление могут быть сложными, их трудоёмкость остаётся O(log n).

Красно-чёрное дерево - это двоичное дерево поиска, в котором каждый узел имеет атрибут цвета.

Свойства красно-черного дерева:
1) Узел может быть либо красным, либо чёрным и имеет двух потомков;
2) Корень, как правило, чёрный. Это правило слабо влияет на работоспособность модели, так как цвет корня всегда можно изменить с красного на чёрный;
3) Все листья, не содержащие данных, чёрные;
4) Оба потомка каждого красного узла — чёрные;
5) Любой простой путь от узла-предка до листового узла-потомка содержит одинаковое число чёрных узлов.

Благодаря этим ограничениям путь от корня до самого дальнего листа не более чем вдвое длиннее, чем до самого ближнего, и дерево примерно сбалансировано. Операции вставки, удаления и поиска требуют в худшем случае времени, пропорционального длине дерева, что позволяет красно-чёрным деревьям быть более эффективными в худшем случае, чем обычные двоичные деревья поиска.

## Реализация

В реализации дерева следует использовать структуру, где каждый узел является самостоятельным объектом. Узел дерева содержит поля color, data, указатели на дочерние узлы left и right, и указатель на узел-родитель parent.

### Правый и левый повороты
 Операции над деревом поиска INSERT и DELETE изменяют дерево, и в результате их работы могут нарушаться красно-черные свойства. Для восстановления этих свойств мы должны изменить цвета некоторых узлов дерева, а также структуру его указателей. Изменения в структуре указателей будут выполняться при помощи поворотов (rotate), которые представляют собой локальные операции в дереве поиска, сохраняющие свойство бинарного дерева поиска.

Левый поворот: 
```C++
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
```

Правый поворот:
```C++
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
```
```C++
```

### Вставка элемента

 Для вставки узла в дерево мы используем процедуру RB_INSERT, которая вставляет узел в дерево, как если бы это было обычное бинарное дерево поиска, а затем окрашивает его в красный цвет.

Краткое описание алгоритма данной функции:
1. Создание нового узла (z) с заданным значением inf.
2. Поиск места для вставки (как в обычном BST):
     - Проход от корня (root) влево (если inf < текущего узла) или вправо (если inf > текущего узла).
     - Если узел с таким значением уже есть — выводится сообщение, и вставка отменяется.
3. Привязка нового узла к родителю (y) — он становится левым/правым потомком в зависимости от значения.
4. Если дерево пустое, новый узел становится корнем (root = z).
5. Балансировка (RB_INSERT_FIXUP) — исправление возможных нарушений свойств RB-Tree (например, два красных узла подряд).

Код функции:

```C++
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

```

Для того чтобы вставка сохраняла красно-черные свойства дерева, после нее вызывается вспомогательная процедура RB_INSERT_FIXUP, которая перекрашивает узлы и выполняет повороты. 

Краткое описание алгоритма:

1. Цикл while:
    - Выполняется пока родитель z существует и является красным (нарушение свойства красно-черного дерева)
2. Два симметричных случая:
    - Родитель z является левым потомком (первая ветка if)
    - Родитель z является правым потомком (ветка else)
3. Три подслучая в каждой ветке:
    - Случай 1: Дядя z (y) красный → перекрашивание
    - Случай 2: Дядя z черный и z - правый потомок → левый поворот
    - Случай 3: Дядя z черный и z - левый потомок → перекрашивание + правый поворот
4. Финализация:
    - Гарантирует, что корень всегда черный (root->color = true)

Код:
```C++
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

```

### Удаление элемента
Для удаления узла используем процедуру RB_DELETE.

Краткое описание алгоритма:

1. Поиск узла:

Находим узел z с заданным значением inf с помощью функции search()

Если узел не найден, выводим сообщение и завершаем работу

2. Подготовка к удалению:

Сохраняем исходный цвет удаляемого узла y_original_color

Определяем узел y, который фактически будет удален (изначально равен z)

Определяем узел x, который займет место y

3. Три случая удаления:
    a. Нет левого потомка:

Заменяем z на его правого потомка (RB_TRANSPLANT)

x становится правым потомком z

b. Нет правого потомка:

Заменяем z на его левого потомка (RB_TRANSPLANT)

x становится левым потомком z

c. Есть оба потомка:
Находим преемника y (минимальный в правом поддереве)

Сохраняем цвет преемника y_original_color

x становится правым потомком y

Если y не является непосредственным потомком z, выполняем дополнительные манипуляции

Заменяем z на y и сохраняем связи

4. Освобождение памяти
5. Балансировка:
    - Если исходный цвет удаленного узла y был черным, вызываем RB_DELETE_FIXUP(x) для восстановления свойств дерева

```C++
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

```
После удаления узла в ней вызывается вспомогательная процедура RB_DELETE_FIXUP,которая изменяет цвета и выполняет повороты для восстановления красно-черных свойств дерева:
```C++
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
```
Также при удалении используется функция RB_TRANSPLANT:

```C++
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
```
Это вспомогательная функция, которая упрощает процесс удаления узла, обеспечивая корректную замену поддеревьев без нарушения структуры дерева. Основная логика балансировки выполняется в RB_DELETE_FIXUP.

### Поиск элемента

```C++
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

```
### Поиск максимального и минимального элемента

```C++
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

```

### Поиск ближайшего большего и ближайшего меньшего элемента

```C++
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

```

## Вывод
- В ходе лабораторной работы я познакомилась с системой верстки текстов TeX, языком верстки ТеХ.
