#include "operations.hpp"

bool contains(const Element& set, const Element& el) {
    for (const auto& e : set.children) {
        if (e.equals(el)) return true;
    }
    return false;
}

Element symmetricDifference(const Element& a, const Element& b) {
    Element result;
    result.isSet = true;
    result.ordered = false;

    for (const auto& el : a.children) {
        if (!contains(b, el)) result.children.push_back(el);
    }

    for (const auto& el : b.children) {
        if (!contains(a, el)) result.children.push_back(el);
    }

    return result;
}
