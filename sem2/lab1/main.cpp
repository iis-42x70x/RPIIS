#include <iostream>
#include "Set.h"

int main ()
{
    setlocale(LC_ALL, "RU");
    
    Set a;
    Set b;
    
    while (true){
        std :: cout << "Выберите действие: " << std :: endl;
        std :: cout << "1 - Ввести множество(a)" << std :: endl;
        std :: cout << "2 - Ввести множество(b)" << std :: endl;
        std :: cout << "3 - Поиск элемента(а)" << std :: endl;
        std :: cout << "4 - Поиск элемента(b)" << std :: endl;
        std :: cout << "5 - Удаление элемента(a)" << std :: endl;
        std :: cout << "6 - Удаление элемента(b)" << std :: endl;
        std :: cout << "7 - Объединение" << std :: endl;
        std :: cout << "8 - Пересечение" << std :: endl;
        std :: cout << "9 - Вывести элементы(a)" << std :: endl;
        std :: cout << "10 - Вывести элементы(b)" << std :: endl;
        std :: cout << "11 - Выход" << std :: endl;
        
        std :: string str;
        
        std :: cout << "Enter: ";
        std :: cin >> str;
        
        if (str == "1"){
            std :: cout << "Введите множество: ";
            
            std :: string s;
            std :: cin.ignore();
            std :: getline(std :: cin, s);
            
            a.push(s);
        }
        if (str == "2"){
            std :: cout << "Введите множество: ";
            
            std :: string s;
            std :: cin.ignore();
            std :: getline(std :: cin, s);
            
            b.push(s);
        }
        if (str == "3"){
            std :: string s;
            
            std :: cout << "Введите элемент, который нужно найти: ";
            std :: cin.ignore();
            std :: getline(std :: cin, s);
            
            if (a.find(s) == true){
                std :: cout << "Элемент найден" << std :: endl;
            }
            else{
                std :: cout << "Элемент не найден" << std :: endl;
            }
        }
        if (str == "4"){
            std :: string s;
            
            std :: cout << "Введите элемент, который нужно найти: ";
            std :: cin.ignore();
            std :: getline(std :: cin, s);
            
            if (b.find(s) == true){
                std :: cout << "Элемент найден" << std :: endl;
            }
            else{
                std :: cout << "Элемент не найден" << std :: endl;
            }
        }
        if (str == "5"){
            std :: string s;
            
            std :: cout << "Введите элемент, который нужно удалить: ";
            std :: cin.ignore();
            std :: getline(std :: cin, s);
            
            a.del(s);
        }
        if (str == "6"){
            std :: string s;
            
            std :: cout << "Введите элемент, который нужно удалить: ";
            std :: cin.ignore();
            std :: getline(std :: cin, s);
            
            b.del(s);
        }
        if (str == "7"){
            Set res = a.Union(b);
            
            res.print();
        }
        if (str == "8"){
            Set res = a.Intersection(b);
            
            res.print();
        }
        if (str == "9"){
            a.print();
        }
        if (str == "10"){
            b.print();
        }
        if (str == "11"){
            break;
        }
    }
    
    return 0;
}
