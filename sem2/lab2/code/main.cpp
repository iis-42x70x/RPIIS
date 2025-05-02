//
//  main.cpp
//  Lab2_PIOIVIS_set
//
//  Created by Dmitry Burbas on 22/04/2025.
//

#include <iostream>
#include "set_of_possible_orient_sets.hpp"

int main() {
    set_of_possible_orient_sets set_to_test;
    int flag_to_continue;
    while (1) {
        set_to_test.calculate_possible_sets();
        do{
            std::cout 
            << "|-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/|\n"
            << "| Do you want to make other set? |\n"
            << "|            1 - Yes             |\n"
            << "|            2 - No              |\n"
            << "|-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/-/|\n"
            << "Input: ";
            std::cin >> flag_to_continue;
            if (std::cin.fail()|| (flag_to_continue!=1 && flag_to_continue!=2)) {
                std::cin.clear();
                std::cin.ignore(100,'\n');
                std::cout << "🟥 Wrong input 🟥\n";
                flag_to_continue=0;
            }else if (flag_to_continue == 1){
                set_to_test.clear_set();
                std::cout << "Continuing...\n";
            }else if (flag_to_continue == 2){
                std::cout << "Ending program...\n";
                return 0;
            }
        }while(std::cin.fail() || (flag_to_continue!=1 && flag_to_continue!=2));
    }
}
