#include <iostream>
#include <string>
#include "Header.h"
#include <fstream>

int main() {
    setlocale(0, "rus");
    int choice;
    std::string sets[100];
    int sets_count = 0;
    std::string elements1[100];
    std::string elements2[100];
    std::string result[200];
    int count1 = 0, count2 = 0, resultCount = 0;

    // Загрузка данных из нового расположения
    load(sets, sets_count, elements1, count1, "C:\\Users\\Lenovo\\Desktop\\Пиовис\\text.txt");

    while (true) {
        std::cout << "Меню:" << std::endl;
        std::cout << "1) Добавить множества" << std::endl;
        std::cout << "2) Просмотр множества" << std::endl;
        std::cout << "3) Просмотр симметрической разности" << std::endl;
        std::cout << "4) Сохранить в файл" << std::endl;
        std::cout << "5) Закрыть программу" << std::endl;
        std::cout << "Выберите пункт меню: ";
        std::cin >> choice;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1) {
            if (sets_count < 100) {
                std::cout << "Введите множество номер " << sets_count + 1 << "\n";
                std::getline(std::cin, sets[sets_count]);
                sets[sets_count] = removeSpaces(sets[sets_count]);
                sets_count++;
            }

        }
        else if (choice == 2) {
            if (sets_count > 0) {
                for (int i = 0; i < sets_count; ++i) {
                    std::cout << "Множество номер " << i + 1 << ": " << sets[i] << "\n";
                }
            }
            else {
                std::cout << "Множества еще не добавлены.\n";
            }
        }
        else if (choice == 3) {
            if (sets_count > 1) {
                count1 = 0;
                count2 = 0;

                extractElements(sets[0], elements1, count1);
                for (int i = 1; i < sets_count; ++i) {
                    extractElements(sets[i], elements2, count2);
                    symmetricDifference(elements1, count1, elements2, count2, result, resultCount);
                    // Обновляем элементы для следующей итерации
                    for (int j = 0; j < resultCount; ++j) {
                        elements1[j] = result[j];
                    }
                    count1 = resultCount;
                    resultCount = 0; // Сбрасываем результат для следующей итерации
                }
                // Печать результата симметрической разности
                std::cout << "Симметрическая разность = {";
                for (int i = 0; i < count1; ++i) {
                    std::cout << elements1[i];
                    if (i < count1 - 1) {
                        std::cout << ", ";
                    }
                }
                std::cout << "}" << std::endl;
            }
            else {
                std::cout << "Для вычисления симметрической разности необходимо как минимум два множества.\n";
            }
        }
        else if (choice == 4) {
            // Сохранение данных в новое расположение
            save(sets, sets_count, elements1, count1, "C:\\Users\\Lenovo\\Desktop\\Пиовис\\text.txt");

        }
        else if (choice == 5) {
            std::cout << "Программа завершена." << std::endl;
            break;
        }
        else {
            std::cout << "Неверный выбор. Пожалуйста, выберите пункт меню снова.\n";
        }
    }

    return 0;
}
