//
//  set_of_possible_orient_sets.hpp
//  Lab2_PIOIVIS_set
//
//  Created by Dmitry Burbas on 30/04/2025.
//
//  Данная программа реализует функционал генерации всех ориентированных множеств перестановок
//  для исходного неориентированного множества. Сделаны необходимые проверки на некорректный ввод.

//  Генерация перестановок работает так:
//  при вводимом n(размере перестановок) проверяется равен ли n
//  размеру исходного множества, если да то для
//  генерации достаточно только Алгоритма Хипа для перестановок,
//
//  если же n не равен размеру исходного множ-ва,
//  то сначала генерируются неориентированные перестановки,
//  а потом для каждой неориентированной генерируются
//  все ориентированные перестановки с помощью Алгоритма Хипа
//
#ifndef SET_OF_POSSIBLE_ORIENT_SETS_HPP  // Проверка, определён ли макрос
#define SET_OF_POSSIBLE_ORIENT_SETS_HPP

#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <algorithm>    // Для удаления пробелов из строки
#define TEXT_FILENAME "/Users/dmitryburbas/Documents/Education/PIOIVIS/Labs_Code/Lab2_PIOIVIS_set/set_container.txt"

unsigned long long int factorial(unsigned long long int numb_to_fact);

class set_of_possible_orient_sets{
private:
    std::vector<std::string> input_set;
    std::vector<std::vector<std::string>> set_possible_orient_sets;
    int numb_of_elem_in_orient_set=0;
    unsigned long long int size_of_result_set=0;
//    Вспомогательные функции (в основном для is_wrong_input, normalize_elements и has_identical_elements)
    void calc_size_of_result_set();
    bool is_right_punct(const char ch);
    bool is_set(const std::string& str);
    bool is_tuple(const std::string& str);
    void swap_elem(std::vector<std::string> &array, int ind1, int ind2);
    bool is_first_less(const std::string elem1, const std::string elem2 );
    void sort_elements(std::vector<std::string> &elements);
    std::string convert_to_string(std::vector<std::string> arr_to_convert, int flag_tuple=0);
    bool normalize_elements(std::string &str_to_convert);
    bool has_identical_elements(std::vector<std::string> &array_to_check);
//    Функция проверки ввода
    bool is_wrong_input();
//    Функция генерации перестановок при k=n
    std::vector<std::vector<std::string>> heap_permutations(std::vector<std::string> array_to_permute);
//    Функция генерации неориентированных перестановок
    std::vector<std::vector<std::string>> generate_unordered_permutations(std::vector<std::string> array_to_gener, int size_of_permut);
public:
//    Конструктор
    set_of_possible_orient_sets(std::vector<std::string> start_set={}, int size_of_orient_sets=0);
//    Функция вывода результата генерации перестановок
    void print_result_set();
//    Вспомогательные функции ввода исходного множества
    bool read_set_from_file();
    bool read_set_from_keyboard();
//    Отдельная функция ввода для удобства
    bool get_input();
//    Главная функция отвечающая за весь функционал генерации перестановок
    void calculate_possible_sets(bool tested=false);
//    Функция очистки всех полей класса
    void clear_set();
};

#endif
