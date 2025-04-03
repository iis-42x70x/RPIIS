//
//  SegmentTree.h
//  Lab1_PIOIVIS_SegTree
//
//  Created by Dmitry Burbas on 25/03/2025.
//
#ifndef SEGMENT_TREE_H // Include guards для защиты от повторного включения
#define SEGMENT_TREE_H

#include <vector>
#include <unordered_map>
#include <stack>
#include <iostream>

//  Функция доведения числа до ближайшей степени 2
int next_pow_two(int n);

//  Функция слияния карт частот
std::unordered_map<int, int> merge_maps(
    const std::unordered_map<int, int>& left,
    const std::unordered_map<int, int>& right
);

class SegmentTree{
private:
//    Узел дерева отрезков
    struct SegmentNode{
        std::unordered_map<int, int> numb_freq;
        int num_data=0;
        int lazy_value=0;
        int lazy_flag=0;
        int left_bord=0;
        int right_bord=0;
    };
    
    std::vector<SegmentNode> seg_tree;
    int tree_size=0;
    int new_arr_size=0;
//    Функция проталкивания к родителям (кроме корня)
    void propagate_parents(int ind_to_propagate, int value_to_propagate);
//    Функция проталкивания к детям
    void propagate_children(int ind_to_propagate, int value_to_propagate);
public:
    int st_arr_size=0;
//      Конструктор дерева
    explicit SegmentTree(const std::vector<int>& start_arr);
//      Вывод массива дерева для отладки
    void tree_print();
//      Вывод суммы на отрезке
    int sum(int left_limit, int right_limit);
//      Вывод количества вхождений числа в отрезок
    int quantity_of_number(int numb, int left_segm, int right_segm);
//      Изменение чисел на отрезке
    void change_segm(int value, int left_b, int right_b);
    
};

#endif
