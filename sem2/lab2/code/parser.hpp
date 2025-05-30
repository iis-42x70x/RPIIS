#ifndef PARSER_HPP
#define PARSER_HPP

#include "element.hpp"
#include <string>
#include <stdexcept>

class Parser {
public:
    explicit Parser(const std::string& input);
    Element parse();

private:
    std::string input;
    size_t pos = 0;

    void skipWhitespace();
    bool match(char c);
    char peek() const;
    char get();
    std::string parseName();
    Element parseElement();
    Element parseSet(bool ordered);
};

#endif
