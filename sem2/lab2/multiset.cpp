#include "multiset.hpp"
#include <fstream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include <iostream>

Element::Element() : is_atom(false), name(), set_type(SetType::Unordered) {}
Element::Element(const std::string& atom_name)
    : is_atom(true), name(atom_name), set_type(SetType::Unordered) {
}

bool Element::operator<(const Element& other) const {
    if (is_atom != other.is_atom) return is_atom < other.is_atom;
    if (is_atom) return name < other.name;
    if (set_type != other.set_type) return set_type < other.set_type;
    if (set_type == SetType::Unordered) return unordered_subs < other.unordered_subs;
    return ordered_subs < other.ordered_subs;
}

bool Element::operator==(const Element& other) const {
    if (is_atom != other.is_atom) return false;
    if (is_atom) return name == other.name;
    if (set_type != other.set_type) return false;
    if (set_type == SetType::Unordered) return unordered_subs == other.unordered_subs;
    return ordered_subs == other.ordered_subs;
}

static void skip_ws(const std::string& s, size_t& pos) {
    while (pos < s.size() && std::isspace(static_cast<unsigned char>(s[pos]))) ++pos;
}

static Element parse_element(const std::string& s, size_t& pos);

static Element parse_set(const std::string& s, size_t& pos, SetType type) {
    char open = (type == SetType::Unordered) ? '{' : '<';
    char close = (type == SetType::Unordered) ? '}' : '>';
    if (s[pos] != open) throw std::runtime_error("Expected opening bracket");
    ++pos;
    skip_ws(s, pos);

    Element result;
    result.is_atom = false;
    result.set_type = type;

    while (pos < s.size() && s[pos] != close) {
        Element e = parse_element(s, pos);
        if (type == SetType::Unordered) {
            result.unordered_subs[e]++;
        }
        else {
            result.ordered_subs.push_back(e);
        }
        skip_ws(s, pos);
        if (s[pos] == ',') {
            ++pos;
            skip_ws(s, pos);
        }
        else break;
    }
    if (pos >= s.size() || s[pos] != close) throw std::runtime_error("Expected closing bracket");
    ++pos;
    return result;
}

static Element parse_element(const std::string& s, size_t& pos) {
    skip_ws(s, pos);
    if (pos >= s.size()) throw std::runtime_error("Unexpected end of input");
    if (s[pos] == '{') return parse_set(s, pos, SetType::Unordered);
    if (s[pos] == '<') return parse_set(s, pos, SetType::Ordered);

    size_t start = pos;
    if (std::isalnum(static_cast<unsigned char>(s[pos]))) {
        ++pos;
        while (pos < s.size() && (std::isalnum(static_cast<unsigned char>(s[pos])) || s[pos] == '_')) ++pos;
        return Element(s.substr(start, pos - start));
    }
    throw std::runtime_error("Invalid character in atom");
}

std::vector<Element> parse_input(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) throw std::runtime_error("Failed to open file");
    std::vector<Element> result;
    std::string line;
    size_t line_number = 0;
    while (std::getline(in, line)) {
        line_number++;
        size_t pos = 0;
        skip_ws(line, pos);
        if (pos >= line.size()) continue;
        Element elem = parse_element(line, pos);
        skip_ws(line, pos);
        if (pos < line.size())
        {
            throw std::runtime_error(
                "Строка " + std::to_string(line_number) +
                ": Обнаружено более одного множества в строке."
            );
        }
        result.push_back(elem);
    }
    return result;
}

Element union_multisets(const std::vector<Element>& sets) {
    if (sets.empty()) return Element();
    if (sets[0].is_atom) return sets[0];

    Element result;
    result.is_atom = false;
    result.set_type = sets[0].set_type;

    if (result.set_type == SetType::Unordered) {
        for (const Element& s : sets) {
            for (const auto& pair : s.unordered_subs) {
                const Element& k = pair.first;
                int v = pair.second;
                result.unordered_subs[k] = std::max(result.unordered_subs[k], v);
            }
        }
    }
    else {
        for (const Element& s : sets) {
            result.ordered_subs.insert(result.ordered_subs.end(), s.ordered_subs.begin(), s.ordered_subs.end());
        }
    }
    return result;
}

static void to_string_rec(const Element& e, std::ostringstream& oss) {
    if (e.is_atom) {
        oss << e.name;
        return;
    }
    char open = (e.set_type == SetType::Unordered) ? '{' : '<';
    char close = (e.set_type == SetType::Unordered) ? '}' : '>';
    oss << open;
    bool first = true;
    if (e.set_type == SetType::Unordered) {
        for (const auto& pair : e.unordered_subs) {
            const Element& k = pair.first;
            int v = pair.second;
            for (int i = 0; i < v; ++i) {
                if (!first) oss << ',';
                to_string_rec(k, oss);
                first = false;
            }
        }
    }
    else {
        for (const auto& sub : e.ordered_subs) {
            if (!first) oss << ',';
            to_string_rec(sub, oss);
            first = false;
        }
    }
    oss << close;
}

std::string to_string(const Element& elem) {
    std::ostringstream oss;
    to_string_rec(elem, oss);
    return oss.str();
}