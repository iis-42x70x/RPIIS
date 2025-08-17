// element.hpp
#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <string>
#include <vector>
#include <iostream>

struct Element {
    std::string name;                    // если это простой элемент
    std::vector<Element> children;       // если это множество
    bool isSet = false;                  // true — это множество
    bool ordered = false;                // true — < >, false — { }

    // Сравнение элементов рекурсивно
    bool equals(const Element& other) const {
        if (isSet != other.isSet || ordered != other.ordered)
            return false;

        if (!isSet)
            return name == other.name;

        if (children.size() != other.children.size())
            return false;

        if (ordered) {
            for (size_t i = 0; i < children.size(); ++i) {
                if (!children[i].equals(other.children[i]))
                    return false;
            }
            return true;
        } else {
            // неориентированное: порядок не важен, ищем вхождение каждого
            std::vector<bool> used(other.children.size(), false);
            for (const auto& a : children) {
                bool found = false;
                for (size_t i = 0; i < other.children.size(); ++i) {
                    if (!used[i] && a.equals(other.children[i])) {
                        used[i] = true;
                        found = true;
                        break;
                    }
                }
                if (!found) return false;
            }
            return true;
        }
    }

    // Вывод элемента
    void print(std::ostream& os) const {
        if (!isSet) {
            os << name;
        } else {
            os << (ordered ? '<' : '{');
            for (size_t i = 0; i < children.size(); ++i) {
                children[i].print(os);
                if (i + 1 < children.size())
                    os << ", ";
            }
            os << (ordered ? '>' : '}');
        }
    }
};

inline std::ostream& operator<<(std::ostream& os, const Element& el) {
    el.print(os);
    return os;
}

#endif
