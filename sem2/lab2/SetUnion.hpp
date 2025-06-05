#ifndef SETUNION_HPP
#define SETUNION_HPP

#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

class SetUnion {
public:
    void performUnion(const std::string& filename);
    std::set<std::string> getUnionResult() const;

    // Для тестирования
    std::set<std::string> parse_set(const std::string& str) const;
    bool is_valid_element(const std::string& element) const;

private:
    std::vector<std::set<std::string>> sets;
    std::set<std::string> union_set;

    bool is_valid_name(const std::string& name) const;
    bool is_valid_tuple(const std::string& tuple) const;
    std::string parse_element(const std::string& str, size_t& pos) const;
    void compute_union();
};

#endif // SETUNION_HPP