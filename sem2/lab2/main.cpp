#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <gtest/gtest.h>
#include "header.h"

int main ()
{
    setlocale(LC_ALL, "RU");
    
    Set a;
    Set b;
    
    while (true){
        int n = 0;
        std :: vector <Set> S;
        Set result;
        
        std :: cout << "Введите количество множеств: ";
        std :: cin >> n;
        std :: cin.ignore();
        
        for (int i = 0; i < n; ++i){
            std :: string s;
            Set a;
            std :: getline (std :: cin, s);
            
            a.push(s);
            S.push_back(a);
        }
        
        Set c;
        
        std :: string e;
        std :: getline(std :: cin, e);
        
        std :: string s = c.normalize(e);
        
        result = result.SymmetricalDifference(S);
        result.print();
        
        return 0;
        
    }
    
    return 0;
}
