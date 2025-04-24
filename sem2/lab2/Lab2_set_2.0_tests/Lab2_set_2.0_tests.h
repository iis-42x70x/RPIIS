#ifndef SET_OPERATIONS_H
#define SET_OPERATIONS_H

#include <vector>
#include <string>
#include <set>


class SetOperations {
public:
    enum class ElementType { NUMBER, LETTER, MULTIPLE_LETTER, SUBSET, TUPLE };

    struct Element {
        ElementType type;
        int number;
        char letter;
        int count;
        std::vector<Element> subset;

        Element();
        bool operator<(const Element& other) const;
        bool operator==(const Element& other) const;
    };

    // Чтение множеств из файла
    static std::vector<std::vector<Element>> readSetsFromFile(const std::string& filename);

    // Запись пересечения в файл
    static void writeIntersectionToFile(const std::vector<Element>& intersection, const std::string& filename);

    // Нахождение пересечения
    static std::vector<Element> findIntersection(const std::vector<std::vector<Element>>& sets);

    // Обработка множества
    static std::vector<Element> parseSet(const std::string& str, size_t& pos);

    static bool isNumber(char c);
    static bool isLetter(char c);
    static void skipWhitespace(const std::string& str, size_t& pos);

private:
    static Element parseElement(const std::string& str, size_t& pos);
    static std::vector<Element> parseTuple(const std::string& str, size_t& pos);
};

#endif 