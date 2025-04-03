//
//  SegmentTree.cpp
//  Lab1_PIOIVIS_SegTree
//
//  Created by Dmitry Burbas on 03/04/2025.
//
#include "SegmentTree.hpp"

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
std::unordered_map<int, int> merge_maps(const std::unordered_map<int, int>& left, const std::unordered_map<int, int>& right) {
    std::unordered_map<int, int> res = left;
    for (auto &p : right) {
        res[p.first] += p.second;
    }
    return res;
}
//  Конструктор дерева отрезков
SegmentTree::SegmentTree(const std::vector<int>& start_arr){
    if (start_arr.size()==0) {
        std::cerr << "Input array is empty!";
        return;
    }
    if (start_arr.size()==1) {
        seg_tree.resize(1);
        tree_size=1;
        st_arr_size=1;
        seg_tree[0].num_data = start_arr[0];
        seg_tree[0].numb_freq[start_arr[0]] = 1;
        return;
    }
    st_arr_size =static_cast<int>(start_arr.size());
    new_arr_size = next_pow_two(st_arr_size);
    tree_size = 2*new_arr_size;
    seg_tree.resize(tree_size);
    
    for (int i=0; i<st_arr_size; i++) {
        seg_tree[new_arr_size+i-1].num_data = start_arr[i];
        seg_tree[new_arr_size+i-1].left_bord = i;
        seg_tree[new_arr_size+i-1].right_bord = i;
        
        seg_tree[new_arr_size+i-1].numb_freq[start_arr[i]] =1;
    }
    for (int i = st_arr_size; i < new_arr_size; i++) {
        seg_tree[new_arr_size + i-1].left_bord = i;
        seg_tree[new_arr_size + i-1].right_bord = i;
    }
    for (int i=new_arr_size-2; i>=0; i--) {
        seg_tree[i].num_data= seg_tree[2 * i + 1].num_data + seg_tree[2 * i + 2].num_data;
        seg_tree[i].left_bord = seg_tree[2 * i + 1 ].left_bord;
        seg_tree[i].right_bord = seg_tree[2 * i + 2].right_bord;
        seg_tree[i].numb_freq = merge_maps( seg_tree[2 * i + 1].numb_freq, seg_tree[2 * i + 2].numb_freq );
    }
}
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
//  Функция просмотра массива дерева для отладки
void SegmentTree::tree_print() {
    if (tree_size==1) {
        std::cout << seg_tree[0].num_data << " ";
        std::cout << "[" <<seg_tree[0].left_bord << "-"<<seg_tree[0].right_bord << "] ";
        std::cout << seg_tree[0].num_data <<":"<< seg_tree[0].numb_freq[seg_tree[0].num_data];
        std::cout <<" lazy flag = " << seg_tree[0].lazy_flag;
        std::cout <<" lazy value = " << seg_tree[0].lazy_value;
        std::cout <<"\n";
    }
    for (int i=0; i<tree_size-1; i++) {
        std::cout << seg_tree[i].num_data << " ";
        std::cout << "[" <<seg_tree[i].left_bord << "-"<<seg_tree[i].right_bord << "] ";
        for (auto &p : seg_tree[i].numb_freq) {
            std::cout << p.first << ":"<< p.second<< " ";
        }
        std::cout <<" lazy flag = " << seg_tree[i].lazy_flag;
        std::cout <<" lazy value = " << seg_tree[i].lazy_value;
        std::cout <<"\n";
    }
}
//  Функция получения суммы на отрезке
int SegmentTree::sum(int left_limit, int right_limit){
    if (left_limit>st_arr_size || left_limit<0 || right_limit>st_arr_size || right_limit<0 || left_limit>right_limit) {
        std::cerr << "🟥🟥🟥 Wrong input of borders 🟥🟥🟥";
        return 0;
    }
    if (tree_size==1) {
        return seg_tree[0].num_data;
    }
    std::stack<int> stack_to_check;
    int sum;
    int cur_ind,mid;
    sum=0;
    stack_to_check.push(0);
    while (!stack_to_check.empty()) {
        cur_ind=stack_to_check.top();
        stack_to_check.pop();
        mid = (seg_tree[cur_ind].right_bord + seg_tree[cur_ind].left_bord)/2;
        if (seg_tree[cur_ind].left_bord>=left_limit && seg_tree[cur_ind].right_bord<=right_limit) {
            sum+=seg_tree[cur_ind].num_data;
        }else {
            if (seg_tree[cur_ind].lazy_flag!=0) {
                propagate_children(cur_ind,seg_tree[cur_ind].lazy_value);
            }
            if (left_limit <= mid && cur_ind<=tree_size){
                stack_to_check.push(2*cur_ind+1);
            }
            if (right_limit > mid && cur_ind<=tree_size){
                stack_to_check.push(2*cur_ind+2);
            }
        }
    }
    return sum;
}
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
    stack_to_check.push(0);
    while (!stack_to_check.empty()) {
        cur_ind=stack_to_check.top();
        stack_to_check.pop();
        if (seg_tree[cur_ind].left_bord>=left_segm && seg_tree[cur_ind].right_bord<=right_segm) {
            quantity+=seg_tree[cur_ind].numb_freq[numb];
        }else {
            mid = (seg_tree[cur_ind].right_bord + seg_tree[cur_ind].left_bord)/2;
            if (seg_tree[cur_ind].lazy_flag!=0) {
                propagate_children(cur_ind,seg_tree[cur_ind].lazy_value);
            }
            if (left_segm <= mid && cur_ind<=tree_size){
                stack_to_check.push(2*cur_ind+1);
            }
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
    if (tree_size==1) {
        seg_tree[0].numb_freq.clear();
        seg_tree[0].numb_freq[value] = 1;
        seg_tree[0].num_data= value;
        return;
    }
    std::stack<int> stack_to_check;
    int ind,mid;
    stack_to_check.push(0);
    while (!stack_to_check.empty()) {
        ind=stack_to_check.top();
        stack_to_check.pop();
        if(seg_tree[ind].lazy_flag!=0){
            propagate_children(ind, seg_tree[ind].lazy_value);
        }
        if (seg_tree[ind].left_bord>=left_b && seg_tree[ind].right_bord<=right_b) {
            if (seg_tree[ind].left_bord != seg_tree[ind].right_bord) {
                seg_tree[ind].lazy_flag = 1;
                seg_tree[ind].lazy_value = value;
            }
            seg_tree[ind].numb_freq.clear();
            seg_tree[ind].numb_freq[value] = (seg_tree[ind].right_bord - seg_tree[ind].left_bord + 1);
            
            propagate_parents(ind,value);
            
            seg_tree[ind].num_data= seg_tree[ind].numb_freq[value]*value;
        }else {
            mid = (seg_tree[ind].right_bord + seg_tree[ind].left_bord)/2;
            if (left_b <= mid ){
                stack_to_check.push(2*ind+1);
            }
            if (right_b > mid ){
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
