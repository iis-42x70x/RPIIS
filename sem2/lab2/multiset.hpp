#ifndef MULTISET_HPP
#define MULTISET_HPP

#include <string>
#include <vector>
#include <map>
#include <variant>
#include <stdexcept>

enum class SetType { Unordered, Ordered };

class Element {
public:
    bool is_atom;
    std::string name;  // если is_atom
    SetType set_type;  // если !is_atom
    std::vector<Element> ordered_subs;     // если set_type == Ordered
    std::map<Element, int> unordered_subs; // если set_type == Unordered

    Element();
    explicit Element(const std::string& atom_name);

    bool operator<(const Element& other) const;
    bool operator==(const Element& other) const;
};

std::vector<Element> parse_input(const std::string& filename);
Element union_multisets(const std::vector<Element>& sets);
std::string to_string(const Element& elem);

#endif // MULTISET_HPP