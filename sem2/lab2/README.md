# Лабораторная работа №2
## Цели:
* Изучить основные понятия, связанные  с множествами
* Научиться правильно выполять операции над множествами
* Уметь использовать основные свойства множеств

## Задачи:
* Выполнить свой вариант лабораторной работы 
* Перенести получившееся решение на язык программирования С++

## Вариант 
Для выполнения лабораторной работы мне был выдан вариант **7**.

**Вариант 7:**\
7. Реализовать программу, формирующую без повторений всевозможные ориентированные
множества из элементов исходного неориентированного множества, количество
элементов в сформированных множествах должно быть равно исходному натуральному n.

Для работы с множествами буду использовать библиотеку  **vector** и **string**

## Теоретические сведения

**Множество** – простейшая информационная конструкция и математическая структура,
позволяющая рассматривать какие-то объекты как целое, связывая их. Объекты, связываемые
некоторым множеством, называются элементами этого множества. Если объект связан
некоторым множеством, то говорят, что существует вхождение объекта в это множество, а
объект принадлежит этому множеству.

**Алгоритм Хипа** - это алгоритм, который генерирует все возможные перестановки n объектов. Впервые он был предложен Б. Р. Хипом в 1963 году. Алгоритм минимизирует перемещения: он генерирует каждую перестановку из предыдущей, меняя местами одну пару элементов; остальные n−2 элемента не затрагиваются. В обзоре алгоритмов генерации перестановок, опубликованном в 1977 году, Роберт Седжвик пришёл к выводу, что на тот момент это был самый эффективный алгоритм для генерации перестановок с помощью компьютера.

## Основные части программы

### Ввод множества
```cpp
bool set_of_possible_orient_sets::read_set_from_keyboard(){
    int size_of_input;
    do{
        std::cout << "Input number of elements of your set:";
        std::cin >> size_of_input;
        if (size_of_input>12) {
            std::cerr << "🟥 Too many elements, don't input > 12 🟥\n";
            std::cin.clear();
            std::cin.ignore(100,'\n');
            size_of_input =0;
        }
        if (std::cin.fail() || size_of_input < 0) {
            std::cerr << "🟥 WRONG INPUT 🟥\n";
            std::cin.clear();
            std::cin.ignore(100,'\n');
            size_of_input =0;
        }
    }while(std::cin.fail() || size_of_input <= 0);
    input_set.resize(size_of_input);
    std::cin.ignore();
    for (int i = 0; i<size_of_input; i++) {
        std::cout << "Input " << i+1 << " element of the set: ";
        do{
            getline(std::cin, input_set[i]);
            if (input_set[i].empty()) {
                std::cout << "\nYou made input an empty string.\nInput again: ";
            }
        }while(input_set[i].empty());
    }
    if(is_wrong_input()){
        clear_set();
        std::cerr << "\n🟥 WRONG INPUT OF ELEMENTS 🟥\n";
        return false;
    }
    if (input_set.size() == 0) {
        return true;
    }else if(input_set.size() == 1){
        numb_of_elem_in_orient_set=1;
        return true;
    }
        
    do {
        std::cout << "Input number of elements in oriental sets(don't input bigger than 9): ";
        std::cin >> numb_of_elem_in_orient_set;
        if (std::cin.fail() || numb_of_elem_in_orient_set > input_set.size() || numb_of_elem_in_orient_set>9) {
            std::cin.clear();
            std::cin.ignore(100,'\n');
            std::cerr << "🟥 WRONG INPUT! Number of elements may be bigger than size of input set or bigger than 9 🟥\nInput number of elements in oriental set again: ";
        }
    } while (std::cin.fail() || numb_of_elem_in_orient_set > input_set.size() || numb_of_elem_in_orient_set>9);
    return true;
}
```
### Проверка ввода
```cpp
bool set_of_possible_orient_sets::is_wrong_input(){
    int size_of_input = static_cast<int>(input_set.size());
    for (int i=0; i<size_of_input; i++) {
        input_set[i].erase(std::remove(input_set[i].begin(), input_set[i].end(), ' '), input_set[i].end());
        std::stack<char> stack_of_brackets;
        for (int j=0; j<input_set[i].size(); j++) {
            char cur_symb = input_set[i][j];
            if (cur_symb == '{' || cur_symb == '<') {
                stack_of_brackets.push(cur_symb);
            }else if (cur_symb == '>' || cur_symb == '}'){
                if (stack_of_brackets.empty()) {
                    return true;
                }
                if (j+1!= input_set[i].size() && (input_set[i][j+1] == '{' || input_set[i][j+1] == '<' || isalpha(input_set[i][j+1]))) {
                    return true;
                }
                char open_symb = stack_of_brackets.top();
                if ((open_symb == '{' && cur_symb == '>')||(open_symb == '<' && cur_symb == '}')){
                    return true;
                }
                stack_of_brackets.pop();
            }else if (is_right_punct(cur_symb)) {
                if(stack_of_brackets.empty()){
                    std::cerr << "🟥 WRONG: more than one element in one element\n";
                    return true;
                }else if(j+1==input_set[i].size() || input_set[i][j+1] == '}'|| input_set[i][j+1] == '>'){
                    return true;
                }
            }else if(j+1 !=input_set[i].size() && isalpha(cur_symb) && (isalnum(input_set[i][j+1]))){
                return true;
            }else if(ispunct(cur_symb) && !is_right_punct(cur_symb)){
                std::cerr << "🟥 WRONG: there are wrong symbols\n";
                return true;
            }
        }
        if (!stack_of_brackets.empty()) {
            return true;
        }
    }
    sort_elements(input_set);
    if (has_identical_elements(input_set)) {
        std::cerr << "🟥 WRONG: there are identical items\n";
        return true;
    }
    return false;
}
```
### Генерация перестановок
```cpp
std::vector<std::vector<std::string>> set_of_possible_orient_sets::heap_permutations(std::vector<std::string> array_to_permute){
    int size_of_input = static_cast<int>(array_to_permute.size());
    std::vector<int> counter(size_of_input,0);
    std::vector<std::vector<std::string>> result;
    int index = 0;
    
    result.push_back(array_to_permute);
    
    while (index < size_of_input) {
        if (counter[index] < index) {
            if (index % 2 == 0) {
                swap_elem(array_to_permute, 0, index);
            }else swap_elem(array_to_permute, counter[index], index);
            
            result.push_back(array_to_permute);
            counter[index]++;
            index=0;
        }else {
            counter[index] = 0;
            index++;
        }
        
    }
    return result;
}

std::vector<std::vector<std::string>> set_of_possible_orient_sets::generate_unordered_permutations(std::vector<std::string> array_to_gener, int size_of_permut){
    std::vector<std::vector<std::string>> result;
    std::vector<std::string> temp_permutation(size_of_permut);
    std::vector<int> index_arr(size_of_permut);
    int size_of_input = static_cast<int>(array_to_gener.size());
    
    for (int i=0; i<size_of_permut; i++) {
        index_arr[i] = i;
        temp_permutation[i] = array_to_gener[i];
    }
    result.push_back(temp_permutation);
    while (true) {
        int chang_index = size_of_permut-1;
        
        while (chang_index>=0 && index_arr[chang_index] == size_of_input - size_of_permut + chang_index) {
            chang_index--;
        }
            
        if (chang_index<0) break;
            
        index_arr[chang_index]++;
        for (int k=chang_index+1; k<size_of_permut; k++) {
            index_arr[k] = index_arr[k-1] + 1;
        }
            
        for (int i=0; i<size_of_permut; i++) {
            temp_permutation[i] = array_to_gener[index_arr[i]];
        }
        result.push_back(temp_permutation);
    }
    return result;
}
```
## Пример работы программы
**Файл для считывания:**

![Исходное множество в файле](/images/file_container_for_input_set.png)

**Работа программы при считывании исходного множества из файла:**

![Пример работы программы начало вывода](/images/examp_program1.png)

**И так далее...**

![Пример работы программы конец вывода](/images/examp_program2.png)

## Тестирование
Я использовал Unit-test bundle в Xcode для тестирования

![Пример Unit-test1](/images/unit_test_examp1.png)

![Пример Unit-test2](/images/unit_test_examp2.png)
## Вывод
В ходе выполнения данной лабораторной работы я:
- Изучил принцип работы с множествами.
- Приобрёл навыки разработки операций над множествами в C++.
- Разработал библиотеку алгоритмов генерации всех ориентированных перестановок 

## Список используемых источников
- Свободная энциклопедия "Википедия" Статья "Множество" [Электронный ресурс]-Режим доступа
    - https://ru.wikipedia.org/wiki/Множество
- Свободная энциклопедия "Википедия" Статья "Алгоритм перестановок Хипа" [Электронный ресурс]-Режим доступа
    - https://en.wikipedia.org/wiki/Heap's_algorithm
- Сайт "Geeks for geeks" Статья "Алгоритм перестановок Хипа" [Электронный ресурс]-Режим доступа
    - https://www.geeksforgeeks.org/heaps-algorithm-for-generating-permutations/
- Сайт Google disk" [Электронный ресурс]-Режим доступа
    - https://drive.google.com/drive/folders/1_xy849HXgTDetxSMlFd0KikTBo8-xalN