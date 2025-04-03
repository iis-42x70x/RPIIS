//
//  main.cpp
//  Lab1_PIOIVIS_SegTree
//
//  Created by Dmitry Burbas on 24/03/2025.
//

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "SegmentTree.hpp"

using namespace std;

vector<int> get_user_array_input(){
    vector<int> input;
    string buffer;
    int num_buf;
    
    while (input.empty()) {
        cout << "Input an array(to end input - Enter)\nArray: ";
        getline(cin, buffer);
        istringstream iss(buffer);
        while (iss >> num_buf) {
            input.push_back(num_buf);
        }
    }
    
    return input;
}
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
    vector<int> input_array = get_user_array_input();
    int input_size = static_cast<int>(input_array.size());
//    vector<int> array_to_test={5,2,4,1,6,7};
    
    SegmentTree seg_tree(input_array);
    
    SegmentTree_menu(seg_tree, input_size);
    
    return 0;
}
