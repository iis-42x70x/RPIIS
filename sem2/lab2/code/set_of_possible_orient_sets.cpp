//
//  set_of_possible_orient_sets.cpp
//  Lab2_PIOIVIS_set
//
//  Created by Dmitry Burbas on 30/04/2025.
//
#include "set_of_possible_orient_sets.hpp"

unsigned long long int factorial(unsigned long long int numb_to_fact){
    int result=1;
    for (int i=2; i<=numb_to_fact; i++) {
        result*= i;
    }
    return result;
}

set_of_possible_orient_sets::set_of_possible_orient_sets(std::vector<std::string> start_set, int size_of_orient_sets) : input_set(start_set), numb_of_elem_in_orient_set(size_of_orient_sets){}

void set_of_possible_orient_sets::calc_size_of_result_set(){
    if (input_set.size()==0 || input_set.size()==1) {
        return;
    }
    if (numb_of_elem_in_orient_set==1) {
        size_of_result_set = input_set.size();
        set_possible_orient_sets.resize(size_of_result_set);
        return;
    }
    size_of_result_set = factorial(input_set.size())/(factorial(input_set.size()-numb_of_elem_in_orient_set));
    set_possible_orient_sets.reserve(size_of_result_set);
}

bool set_of_possible_orient_sets::is_right_punct(const char ch){
    if (ispunct(ch) && (ch==',' || ch==';')) {
        return true;
    }else return false;
}

bool set_of_possible_orient_sets::is_set(const std::string& str) {
    return str.size() >= 2 && str.front() == '{' && str.back() == '}';
}

bool set_of_possible_orient_sets::is_tuple(const std::string& str) {
    return str.size() >= 2 && str.front() == '<' && str.back() == '>';
}
void set_of_possible_orient_sets::swap_elem(std::vector<std::string> &array, int ind1, int ind2){
    std::string temp;
    temp = array[ind1];
    array[ind1] = array[ind2];
    array[ind2] = temp;
}

bool set_of_possible_orient_sets::is_first_less(const std::string elem1, const std::string elem2 ){
    if (elem1.size() != elem2.size()) {
            return elem1.size() < elem2.size();
        }
    return elem1 < elem2;
}

void set_of_possible_orient_sets::sort_elements(std::vector<std::string> &elements){
    int numb_of_elem = static_cast<int>(elements.size());
    std::string temp;
    for (int i = 1; i<numb_of_elem; i++) {
        int j = i;
        while (j>0 && is_first_less(elements[j], elements[j-1])) {
            swap_elem(elements, j, j-1);
            j--;
        }
    }
}

std::string set_of_possible_orient_sets::convert_to_string(std::vector<std::string> arr_to_convert, int flag_tuple){
    std::string result;
    if (flag_tuple) {
        result="<";
    }else result="{";
    for (int i=0; i<arr_to_convert.size(); i++) {
        result += arr_to_convert[i];
        if (i<arr_to_convert.size()-1) {
            result+=",";
        }
    }
    if (flag_tuple) {
        result+=">";
    }else result+="}";
    return result;
}

bool set_of_possible_orient_sets::normalize_elements(std::string &str_to_convert){
    std::vector<std::string> array_elements;
    std::string temp;
    int count_of_brackets=0;
        
    int length_of_input = static_cast<int>(str_to_convert.length());
    if (is_set(str_to_convert) || is_tuple(str_to_convert)){
        for (int i=1; i<length_of_input-1; i++) {
            if (str_to_convert[i]=='}' || str_to_convert[i]=='>') {
                temp.push_back(str_to_convert[i]);
                if (count_of_brackets==1) {
                    count_of_brackets = 0;
                    array_elements.push_back(temp);
                    temp.clear();
                }else count_of_brackets--;
                
            }else if (str_to_convert[i]=='{' || str_to_convert[i]=='<') {
                count_of_brackets++;
                temp.push_back(str_to_convert[i]);
            }else if (isalnum(str_to_convert[i])) {
                temp.push_back(str_to_convert[i]);
                if (count_of_brackets==0) {
                    array_elements.push_back(temp);
                    temp.clear();
                }
            }else if(is_right_punct(str_to_convert[i]) && count_of_brackets!=0){
                temp.push_back(str_to_convert[i]);
            }
        }
    }else{
        return true;
    }
    if (is_set(str_to_convert)) {
        sort_elements(array_elements);
    }
    for (int i=0; i<array_elements.size(); i++) {
        if (is_set(array_elements[i]) || is_tuple(array_elements[i])) {
            normalize_elements(array_elements[i]);
        }
    }
    if(has_identical_elements(array_elements)) return false;
    str_to_convert = convert_to_string(array_elements);
    return true;
}

bool set_of_possible_orient_sets::has_identical_elements(std::vector<std::string> &array_to_check){
    int size_of_arr = static_cast<int>(array_to_check.size());
    for (int i=0; i<size_of_arr; i++) {
        if(!normalize_elements(array_to_check[i]))return true;
    }
    for (int i=0; i<size_of_arr; i++) {
        std::string temp = array_to_check[i];
        for (int j=i+1; j<size_of_arr; j++) {
            if (temp.size() != array_to_check[j].size()) {
                continue;
            }
            if (temp == array_to_check[j]) {
                return true;
            }
        }
    }
    return false;
}

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

void set_of_possible_orient_sets::print_result_set(){
    std::cout << "Possible orient sets with element count " << numb_of_elem_in_orient_set << " : \n"
    <<"---------------------------------\n";
    if (input_set.size() == 0) {
        std::cout << "Input set is empty.\n";
        std::cout <<"---------------------------------\n";
        return;
    }else if(input_set.size() == 1){
        std::cout << "< " << set_possible_orient_sets[0][0] << " >\n";
        std::cout <<"---------------------------------\n";
        return;
    }
    for (int i = 0; i< set_possible_orient_sets.size(); i++) {
        int size_of_cur_set = numb_of_elem_in_orient_set;
        std::cout << i+1 << ": < ";
        for (int j =0; j<size_of_cur_set; j++) {
            std::cout << set_possible_orient_sets[i][j];
            if (j<size_of_cur_set-1) {
                std::cout << ", ";
            }
        }
        std::cout << " >\n";
    }
    std::cout <<"---------------------------------\n";
}

bool set_of_possible_orient_sets::read_set_from_file(){
    int size_of_input;
    char buffer[200];
    FILE *text_file = fopen(TEXT_FILENAME, "r");
    if (text_file == NULL) {
        std::cerr << "Error opening text file.\n";
        return false;
    }
    fscanf(text_file, "Size of input: %d\n", &size_of_input);
    fscanf(text_file, "Number of elements in oriental sets: %d\n", &numb_of_elem_in_orient_set);
    if (numb_of_elem_in_orient_set>size_of_input || numb_of_elem_in_orient_set>9) {
        std::cerr << "🟥 WRONG INPUT! Number of elements may be bigger than size of input set or bigger than 9 🟥";
        numb_of_elem_in_orient_set=0;
        fclose(text_file);
        return false;
    }
    input_set.resize(size_of_input);
    for (int i=0; i<size_of_input; i++) {
        fscanf(text_file, "Element: %[^\n]\n", buffer);
        input_set[i].assign(buffer);
    }
    if (input_set.size()>12) {
        std::cerr << "\n🟥 Too big input set, don't input > 12 🟥\n";
        fclose(text_file);
        clear_set();
        return false;
    }
    if(is_wrong_input()){
        std::cerr << "\n🟥 WRONG INPUT OF ELEMENTS 🟥\n";
        fclose(text_file);
        clear_set();
        return false;
    }
    if (input_set.size() == 0) {
        fclose(text_file);
        return true;
    }else if(input_set.size() == 1){
        numb_of_elem_in_orient_set=1;
        fclose(text_file);
        return true;
    }
    fclose(text_file);
    return true;
}

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

bool set_of_possible_orient_sets::get_input(){
    int choice=0;
    do {
        std::cout
        << "|---------- Input menu ----------|\n"
        << "| * Read set from file - 1       |\n"
        << "| * Input set manually - 2       |\n"
        << "|--------------------------------|\n"
        << "Input: ";
        std::cin >> choice;
        if (std::cin.fail() || choice >2) {
            std::cin.clear();
            std::cin.ignore(100,'\n');
            choice = 0;
        }
        switch (choice) {
            case 1:
                if(!read_set_from_file())return false;
                break;
            case 2:
                if(!read_set_from_keyboard())return false;
                break;
            default:
                std::cout << "\n🟥 WRONG INPUT 🟥\n";
                break;
        }
    }while(std::cin.fail() || choice < 1);
    return true;
}

void set_of_possible_orient_sets::calculate_possible_sets(bool tested){
    if(tested){
    }else if(!get_input()){
        clear_set();
        return;
    }
    int size_of_input = static_cast<int>(input_set.size());
    std::cout << "Input: {";
    for (int i = 0; i<size_of_input; i++) {
        std::cout<< " " <<input_set[i];
        if (i<size_of_input-1) {
            std::cout<<",";
        }
    }
    std::cout << " }\n";
    calc_size_of_result_set();
    std::vector<std::vector<std::string>> prev_permutation;
    std::vector<std::vector<std::string>> temp_permutations;
    if (input_set.size() == 0) {
//          Nothing to do
    }else if( input_set.size() == 1 ){
        set_possible_orient_sets.resize(1);
        set_possible_orient_sets.push_back({input_set[0]});
    }else if(numb_of_elem_in_orient_set == 1){
        for (int i=0; i<input_set.size(); i++) {
            set_possible_orient_sets[i].push_back(input_set[i]);
        }
    }else if (input_set.size()==2) {
        set_possible_orient_sets.resize(2);
        set_possible_orient_sets[0].push_back(input_set[0]);
        set_possible_orient_sets[0].push_back(input_set[1]);
        set_possible_orient_sets[1].push_back(input_set[1]);
        set_possible_orient_sets[1].push_back(input_set[0]);
    }else if(numb_of_elem_in_orient_set == input_set.size()){
        set_possible_orient_sets = heap_permutations(input_set);
    }else{
        prev_permutation = generate_unordered_permutations(input_set, numb_of_elem_in_orient_set);
        for (int i=0; i<prev_permutation.size(); i++) {
            temp_permutations = heap_permutations(prev_permutation[i]);
            set_possible_orient_sets.insert(set_possible_orient_sets.end(), temp_permutations.begin(), temp_permutations.end());
        }
    }
    print_result_set();
}

void set_of_possible_orient_sets::clear_set(){
    set_possible_orient_sets.clear();
    input_set.clear();
    size_of_result_set = 0;
    numb_of_elem_in_orient_set=0;
}
