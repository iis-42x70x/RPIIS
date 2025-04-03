# Лабораторная 1. Структуры данных
## Цель работы
- Изучить свойства структур данных
- Разработать библиотеку алгоритмов обработки структур данных
## Задачи
- Разработать библиотеку для работы со структурой данных(мой вариант - Дерево отрезков) на языке программирования C++.
- Разработать тестовую программу, которая демонстрирует работоспособность реализованной библиотеки работы со структурой данных.
- Разработать систему тестов, которые продемонстрировали бы работоспособность реализованной библиотеки.
## Вариант
Мой вариант - Дерево отрезков(5-ый вариант методички).

Необходимо реализовать библиотеку для работы с Деревом отрезков(добавить возможность поиска количества вхождений какого-то числа на
отрезке массива и изменения всех чисел на отрезке массива на какое-то
значение).
## Список используемых понятий
- Дерево — это структура данных, которая организует элементы в виде иерархии и обладает древовидной структурой. В дереве есть узлы (элементы), соединенные связями (ребрами). У дерева есть один главный узел (корень), от которого "растут" остальные узлы. Узлы могут иметь потомков (дочерние узлы), но каждый узел, кроме корня, имеет только одного родителя. Дерево это связный граф, который не содержит циклов.

- Узел(дерева) — это элемент дерева, который хранит данные и может быть связан с другими узлами. Узел может:
    - Содержать значение (например, число или строку).
    - Указывать на другие узлы (своих потомков).

- Узел-потомок — это узел, который находится "ниже" другого узла в дереве и связан с ним. Например, если узел A соединен с узлом B, то B — потомок A.

- Узел-родитель — это узел, который находится "выше" другого узла в дереве и связан с ним. Например, если узел A соединен с узлом B, то A — родитель B.

- Корень — это самый верхний узел дерева. У корня нет родителя, но он может иметь потомков. Все остальные узлы дерева связаны с корнем напрямую или через другие узлы.

- Лист — это узел дерева, у которого нет потомков. Он находится на самом нижнем уровне дерева.

- Бинарное дерево — это тип дерева, где каждый узел может иметь не более двух потомков: левого и правого. Это упрощает операции поиска и обработки данных.
- Полное бинарное дерево - бинарное дерево, у которого любой узел имеет либо 2, либо 0 потомков

- Дерево отрезков — это структура данных, которая используется для работы с диапазонами значений (отрезками).Каждый узел дерева отрезков представляет определенный диапазон элементов массива. Оно позволяет быстро выполнять операции, такие как:
    - Нахождение суммы элементов на отрезке.
    - Поиск минимума или максимума на отрезке.
    - Поиск количества вхождений числа на отрезке
    - Изменение числа на отрезке

- Ленивая пропагация — это техника оптимизации для дерева отрезков. Она откладывает выполнение обновлений до тех пор, пока они действительно не понадобятся. Вместо немедленного обновления всех элементов на отрезке изменения сохраняются в специальной метке (lazy-флаг) и применяются позже при необходимости. Это позволяет ускорить операции обновления и запроса данных.

## Реализация
Для реализации практически любого дерева обычно используется нелинейный связный список. Однако дерево отрезков можно реализовать и через массив с целью упрощения логики кода и некоторой оптимизации. Поэтому я выбрал именно реализацию через массив.

### Варианты реализации
Исходя из таблицы ниже, мной был выбран итеративный вариант ключевой особенностью которого является ленивая пропагация.

| Параметр                 | Рекурсивный        | Итеративный                  |
|--------------------------|-------------------|------------------------------|
| Скорость запросов       | O(log n)          | O(log n) (на 20% быстрее)    |
| Память                  | O(4n) + стек      | O(2n)                        |
| Ленивое распространение | Проще реализовать | Сложнее                      |
| Поддержка произвольных N| Да                | Требует дополнения до 2^k    |
| Отладка                 | Наглядный стек вызовов | Требует ручного трекинга |
| Кэш-эффективность       | Низкая            | Высокая                      |

Дерево отрезков в основном это обычное двоичное дерево. Но для простоты мы будем реализовывать его как полное двоичное дерево.
Тут возникает проблема, что если длина исходного массива не является степенью двойки, то тогда дерево будет выглядеть не очень удобно. Поэтому для упрощения мы дополним массив нулями, пока его длина не станет равна степени двойки.
### Вспомогательные функции
```C++
//  Функция доведения числа до ближайшей степени 2
int next_pow_two(int n){
    if (n == 0) return 0;
        n--;
        n |= n >> 1;
        n |= n >> 2;
        n |= n >> 4;
        n |= n >> 8;
        n |= n >> 16;
        return n + 1;
}
//  Функция слияния карт частот
std::unordered_map<int, int> merge_maps(
    const std::unordered_map<int, int>& left, 
    const std::unordered_map<int, int>& right) 
    {
    std::unordered_map<int, int> res = left;
    for (auto &p : right) {
        res[p.first] += p.second;
    }
    return res;
}
```
### Типы данных для представления дерева
Вот так реализуем тип данных вершины дерева для всех ранее перечисленных операций
```C++
struct SegmentNode{
        std::unordered_map<int, int> numb_freq;
        int num_data=0;
        int lazy_value=0;
        int lazy_flag=0;
        int left_bord=0;
        int right_bord=0;
    };
```
Далее реализуем само дерево
```C++
class SegmentTree{
private:
//    Узел дерева отрезков
    struct SegmentNode{
        unordered_map<int, int> numb_freq;
        int num_data=0;
        int lazy_value=0;
        int lazy_flag=0;
        int left_bord=0;
        int right_bord=0;
    };
    vector<SegmentNode> seg_tree;
    int tree_size=0;
    int new_arr_size=0;
//   ...(приватные методы)
public:
    int st_arr_size=0;
//    Конструктор дерева
    SegmentTree(const vector<int>& start_arr){
        // Проверка на пустоту
        if (start_arr.size()==0) {
            cerr << "Input array is empty!\n";
            return;
        }
        // Реализация дерева основанного на одном числе
        if (start_arr.size()==1) {
            seg_tree.resize(1);
            tree_size=1;
            st_arr_size=1;
            seg_tree[0].num_data = start_arr[0];
            seg_tree[0].numb_freq[start_arr[0]] = 1;
            return;
        }
        // Основная реализация
        st_arr_size =static_cast<int>(start_arr.size());
        new_arr_size = next_pow_two(st_arr_size);
        // Вычисление размера дерева
        tree_size = 2*new_arr_size;
        seg_tree.resize(tree_size);
        // Заполнение листьев
        for (int i=0; i<st_arr_size; i++) {
            seg_tree[new_arr_size+i-1].num_data = start_arr[i];
            seg_tree[new_arr_size+i-1].left_bord = i;
            seg_tree[new_arr_size+i-1].right_bord = i;
            
            seg_tree[new_arr_size+i-1].numb_freq[start_arr[i]] =1;
        }
        // Если массив не был размера степени двойки заполняем пустые листья
        for (int i = st_arr_size; i < new_arr_size; i++) {
            seg_tree[new_arr_size + i-1].left_bord = i;
            seg_tree[new_arr_size + i-1].right_bord = i;
        }
        // Заполнение всех родителей, включая корень
        for (int i=new_arr_size-2; i>=0; i--) {
            seg_tree[i].num_data= seg_tree[2 * i + 1].num_data + seg_tree[2 * i + 2].num_data;
            seg_tree[i].left_bord = seg_tree[2 * i + 1 ].left_bord;
            seg_tree[i].right_bord = seg_tree[2 * i + 2].right_bord;
            seg_tree[i].numb_freq = merge_maps( seg_tree[2 * i + 1].numb_freq, seg_tree[2 * i + 2].numb_freq );
        }
    }
   
```
В целом дерево готово

Для реализации всех остальных операций нам понадобятся два метода отвечающих за проталкивание изменений к родителям или детям:
```C++
//  Функция проталкивания обновления к родителям !!! кроме корня !!! (почему так - смотреть в конец функции изменения чисел на отрезке)
void SegmentTree::propagate_parents(int ind_to_propagate, int value_to_propagate){
    int ind_parrent;
    ind_parrent=(ind_to_propagate - 1 )/2;
    while (ind_parrent>0 ) {
        seg_tree[ind_parrent].num_data+= value_to_propagate * (seg_tree[ind_to_propagate].right_bord - seg_tree[ind_to_propagate].left_bord + 1) - seg_tree[ind_to_propagate].num_data;
        seg_tree[ind_parrent].numb_freq = merge_maps(seg_tree[2 * ind_parrent + 1].numb_freq, seg_tree[2 * ind_parrent + 2].numb_freq);
        ind_parrent=(ind_parrent-1)/2;
    }
}
//  Функция проталкивания lazy-метки к детям
void SegmentTree::propagate_children(int ind_to_propagate, int value_to_propagate){
    int left_child,right_child;
//    Оптимизация: если лист то некому проталкивать
    if (seg_tree[ind_to_propagate].left_bord==seg_tree[ind_to_propagate].right_bord) return;
    
    left_child = 2 * ind_to_propagate + 1;
    right_child = 2 * ind_to_propagate + 2;
//        Проталкивание к внукам если у детей есть метка
    if (seg_tree[left_child].lazy_flag!=0) {
        propagate_children(left_child, seg_tree[left_child].lazy_value);
    }
    if(seg_tree[right_child].lazy_flag!=0){
        propagate_children(right_child, seg_tree[right_child].lazy_value);
    }
//        Основное проталкивание к детям
    if (seg_tree[left_child].left_bord!=seg_tree[left_child].right_bord) {
        seg_tree[left_child].lazy_flag = 1;
        seg_tree[left_child].lazy_value = value_to_propagate;
        seg_tree[right_child].lazy_flag = 1;
        seg_tree[right_child].lazy_value = value_to_propagate;
    }
    seg_tree[left_child].num_data = value_to_propagate * (seg_tree[left_child].right_bord - seg_tree[left_child].left_bord + 1);
    seg_tree[left_child].numb_freq.clear();
    seg_tree[left_child].numb_freq[value_to_propagate] = seg_tree[ind_to_propagate].numb_freq[value_to_propagate]/2;
    
    seg_tree[right_child].num_data = value_to_propagate * (seg_tree[right_child].right_bord - seg_tree[right_child].left_bord + 1) ;
    seg_tree[right_child].numb_freq.clear();
    seg_tree[right_child].numb_freq[value_to_propagate] = seg_tree[ind_to_propagate].numb_freq[value_to_propagate]/2;
    
    seg_tree[ind_to_propagate].lazy_flag=0;
    seg_tree[ind_to_propagate].lazy_value=0;
}
```

Наконец функции операций:

```C++
//  Функция получения количества вхождений числа на отрезке
int SegmentTree::quantity_of_number(int numb, int left_segm, int right_segm){
    if (left_segm>st_arr_size || left_segm<0 || right_segm>st_arr_size || right_segm<0 || left_segm>right_segm) {
        std::cerr << "🟥🟥🟥 Wrong input of borders 🟥🟥🟥";
        return 0;
    }
    
    std::stack<int> stack_to_check;
    int quantity;
    int cur_ind,mid;
    quantity=0;
    // Используем стек для эффективного прохода по нужным узлам
    stack_to_check.push(0);
    while (!stack_to_check.empty()) {
        cur_ind=stack_to_check.top();
        stack_to_check.pop();
        // Если текущий отрезок полностью входит в заданный отрезок то добавляем значение частоты числа в общее количество
        if (seg_tree[cur_ind].left_bord>=left_segm && seg_tree[cur_ind].right_bord<=right_segm) {
            quantity+=seg_tree[cur_ind].numb_freq[numb];
        }else {
            mid = (seg_tree[cur_ind].right_bord + seg_tree[cur_ind].left_bord)/2;
            // Если текущий отрезок имеет lazy-метку то проталкиваем ее к детям
            if (seg_tree[cur_ind].lazy_flag!=0) {
                propagate_children(cur_ind,seg_tree[cur_ind].lazy_value);
            }
            // Если текущий отрезок слева от середины текущего отрезка то добавляем левого ребенка в стек
            if (left_segm <= mid && cur_ind<=tree_size){
                stack_to_check.push(2*cur_ind+1);
            }
            // Если текущий отрезок справа от середины текущего отрезка то добавляем правого ребенка в стек
            if (right_segm > mid && cur_ind<=tree_size){
                stack_to_check.push(2*cur_ind+2);
            }
        }
    }
    return quantity;
}
//  Функция изменения чисел на отрезке на заданное число
void SegmentTree::change_segm(int value, int left_b, int right_b){
    if (left_b>st_arr_size || left_b<0 || right_b>st_arr_size || right_b<0 || left_b>right_b) {
        std::cerr << "🟥🟥🟥 Wrong input of borders 🟥🟥🟥";
        return;
    }
    // Изменение для дерева из одного элемента
    if (tree_size==1) {
        seg_tree[0].numb_freq.clear();
        seg_tree[0].numb_freq[value] = 1;
        seg_tree[0].num_data= value;
        return;
    }
    std::stack<int> stack_to_check;
    int ind,mid;
    stack_to_check.push(0);
    // Используем стек для эффективного прохода по нужным узлам
    while (!stack_to_check.empty()) {
        ind=stack_to_check.top();
        stack_to_check.pop();
        // Если текущий отрезок имеет lazy-метку то проталкиваем ее к детям
        if(seg_tree[ind].lazy_flag!=0){
            propagate_children(ind, seg_tree[ind].lazy_value);
        }
        // Если текущий отрезок полностью входит в заданный отрезок то обновляем значение на отрезке
        if (seg_tree[ind].left_bord>=left_b && seg_tree[ind].right_bord<=right_b) {
            if (seg_tree[ind].left_bord != seg_tree[ind].right_bord) {
                seg_tree[ind].lazy_flag = 1;
                seg_tree[ind].lazy_value = value;
            }
            seg_tree[ind].numb_freq.clear();
            seg_tree[ind].numb_freq[value] = (seg_tree[ind].right_bord - seg_tree[ind].left_bord + 1);
            // Продвигаем изменение к родителям
            propagate_parents(ind,value);
            
            seg_tree[ind].num_data= seg_tree[ind].numb_freq[value]*value;
        }else {
            mid = (seg_tree[ind].right_bord + seg_tree[ind].left_bord)/2;
            // Если текущий отрезок слева от середины текущего отрезка то добавляем левого ребенка в стек
            if (left_b <= mid && ind<=tree_size){
                stack_to_check.push(2*ind+1);
            }
            // Если текущий отрезок справа от середины текущего отрезка то добавляем правого ребенка в стек
            if (right_b > mid && ind<=tree_size){
                stack_to_check.push(2*ind+2);
            }
        }
    }
//        Если на корне нет ленивой метки то обновляем корень на основе его детей (в целях оптимизации вынесено за цикл)
    if (seg_tree[0].lazy_flag==0) {
        seg_tree[0].num_data = seg_tree[1].num_data + seg_tree[2].num_data;
        seg_tree[0].numb_freq = merge_maps(seg_tree[1].numb_freq, seg_tree[2].numb_freq);
    }
    std::cout << "✅ Segment was succesfully changed.";
}
```
## Пример работы с библиотекой
Следующий код для теста(для демонстрации возьмем массив с размером не являющейся степенью 2-ки)

```C++
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "SegmentTree.hpp"

using namespace std;

void SegmentTree_menu(SegmentTree& seg, int input_size){
    int left_border,right_border,operation_value;
    char choice;
    if (input_size==0) {
        return;
    }
    while (1) {
        cout << "\n----------------- Menu -----------------"
        <<"\n*  Change segment on value - 1"
        <<"\n*  Quantity of number on segment - 2"
        <<"\n*  Sum on segment - 3"
        <<"\n*  Print tree to test - 4"
        <<"\n*  Exit program - 5"
        <<"\n----------------------------------------\n";
        cout << "Choose operation: ";
        cin >> choice;
        cin.ignore(20,'\n');
        switch (choice) {
            case '1':
                cout << "Input left border of segment (from "<< 0 << " to " << input_size-1<< "):";
                cin >> left_border;
                cout << "Input right border of segment(from "<< 0 << " to " << input_size-1<< "):";
                cin >> right_border;
                cout << "Input value to change segment:";
                cin >> operation_value;
                seg.change_segm(operation_value, left_border, right_border);
                break;
            case '2':
                cout << "Input left border of segment (from "<< 0 << " to " << input_size-1<< "):";
                cin >> left_border;
                cout << "Input right border of segment(from "<< 0 << " to " << input_size-1<< "):";
                cin >> right_border;
                cout << "Input value to check quantity:";
                cin >> operation_value;
                cout <<"Quantity of "<< operation_value << " = " << seg.quantity_of_number(operation_value, left_border, right_border);
                break;
            case '3':
                cout << "Input left border of segment (from "<< 0 << " to " << input_size-1<< "):";
                cin >> left_border;
                cout << "Input right border of segment(from "<< 0 << " to " << input_size-1<< "):";
                cin >> right_border;
                cout <<"Sum on segment"<< " = " << seg.sum(left_border, right_border);
                break;
            case '4':
                cout << "Tree:\n";
                seg.tree_print();
                break;
            case '5':
                cout << "Exit...\n";
                return;
                break;
            default:
                cout << "🟥 !!!Wrong choice!!! 🟥\n";
                break;
        }
    }
}
int main() {
    vector<int> array_to_test={1,2,3,4,5,6};
    int input_size = static_cast<int>(array_to_test.size());

    SegmentTree seg_tree(array_to_test);
    
    SegmentTree_menu(seg_tree, input_size);
    
    return 0;
}
```
После формирования дерева, его графическое изображения будет выглядеть так(красным обозначены индексы начального массива, а синим массива дерева):

![Построенное дерево отрезков](https://github.com/iis-42x70x/RPIIS/blob/Бурбас_Д/sem2/lab1/images/Segment_tree_example.png)

Если мы запросим количество чисел 2 например на отрезке [0-5], то сначала алгоритм пойдет в индекс 0 массива дерева, потом добавит индекс 1[0-3] в стек, потом добавит индекс 2[4-7] в стек - добавит информационную часть индекса 1 к общему количеству, и потом добавит индекс 5 в стек и обработав его добавит его информационную часть к общему количеству и вернет результат.(примерно также будет работать функция суммы)

Если же мы хотим изменить значение на отрезке [0-3] на допустим 8, то мы сначала дойдем до [0-3] обновим его, установим метку lazy, далее обновим его родителей и закончим на этом. Но при этом дети и внуки [0-3] останутся неизмененными - в этом заключается главная суть **ленивой пропагации**
Тогда при запросе количества 8-ок на отрезке [0-1] мы дойдем до [0-3] а затем будем проталкивать lazy-метку к детям пока не найдем нужный отрезок или не дойдем до конца дерева

## Вывод
В ходе выполнения данной лабораторной работы я:
- Изучил принцип работы дерева отрезков.
- Приобрёл навыки разработки библиотек в C++.
- Разработал библиотеку алгоритмов обработки структуры данных дерева отрезков.

## Список используемых источников
- Свободная энциклопедия "Википедия" [Электронный ресурс]-Режим доступа
    - https://ru.wikipedia.org/wiki/Дерево_отрезков
- Сайт "Algorithms for competitive programming" [Электронный ресурс]-Режим доступа
    - https://cp-algorithms.com/data_structures/segment_tree.html
- Сайт "Алгоритмика" [Электронный ресурс]-Режим доступа
    - https://ru.algorithmica.org/cs/segment-tree/
- Видео "Лекция 2 Дерево отрезков" [Электронный ресурс]-Режим доступа
    - https://www.youtube.com/watch?v=bp9D72E55eI&t=2065s