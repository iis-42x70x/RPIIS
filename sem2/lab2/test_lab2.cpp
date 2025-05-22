#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>
#include <windows.h>
#include <cstdlib>
#include "lab2.h"

void testParseElements() {
    std::string elements[3];
    int count = parseElements("a,b,c", elements, 3);
    assert(count == 3);
    assert(elements[0] == "a");
    assert(elements[1] == "b");
    assert(elements[2] == "c");

    std::cout << "✅ Тест testParseElements пройден\n";
}

void testUniqueCheck() {
    std::string arr1[] = { "a", "b", "c" };
    assert(isUnique(arr1, 3) == true);

    std::string arr2[] = { "a", "a", "c" };
    assert(isUnique(arr2, 3) == false);

    std::cout << "✅ Тест testUniqueCheck пройден\n";
}

void testParseElementsWithAngleBrackets() {
    std::string elements[2];
    int count = parseElements("<a,b>,c", elements, 2);
    assert(count == 2);
    assert(elements[0] == "<a,b>");
    assert(elements[1] == "c");
    std::cout << "✅ Тест testParseElementsWithAngleBrackets пройден\n";
}

void testParseElementsWithCurlyBrackets() {
    std::string elements[3];
    int count = parseElements("{x,y},<a,b>,z", elements, 3);
    assert(count == 3);
    assert(elements[0] == "{x,y}");
    assert(elements[1] == "<a,b>");
    assert(elements[2] == "z");
    std::cout << "✅ Тест testParseElementsWithCurlyBrackets пройден\n";
}

void testParseNestedBrackets() {
    std::string elements[3];
    int count = parseElements("a,<b,{c,d}>,e", elements, 3);
    assert(count == 3);
    assert(elements[0] == "a");
    assert(elements[1] == "<b,{c,d}>");
    assert(elements[2] == "e");
    std::cout << "✅ Тест testParseNestedBrackets пройден\n";
}

void testSingleEmptyElement() {
    std::string elements[1];
    int count = parseElements("", elements, 1);
    assert(count == 0);  // Теперь мы ожидаем 0 элементов
    std::cout << "✅ Тест testSingleEmptyElement пройден\n";
}

void testHasIdenticalElements() {
    std::string arr1[] = { "a", "a", "b" };
    assert(isUnique(arr1, 3) == false);

    std::string arr2[] = { "a", "b", "c" };
    assert(isUnique(arr2, 3) == true);

    std::cout << "✅ Тест testHasIdenticalElements пройден\n";
}

void testFileNotFound() {
    // Убедимся, что файла нет
    remove("input.txt");

    assert(readInput() == false);
    std::cout << "✅ Тест testFileNotFound пройден\n";
}

void testDuplicateElements() {
    std::ofstream input("input.txt");
    input << "2\na,a";
    input.close();

    assert(readInput() == false);
    std::cout << "✅ Тест testDuplicateElements пройден\n";
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    std::setlocale(LC_ALL, ".UTF-8");

    testParseElements();
    testUniqueCheck();
    testParseElementsWithAngleBrackets();
    testParseElementsWithCurlyBrackets();
    testParseNestedBrackets();
    testSingleEmptyElement();
    testHasIdenticalElements();
    testFileNotFound();
    testDuplicateElements();

    std::cout << "🎉 Все оставшиеся тесты успешно пройдены!\n";
    return 0;
}