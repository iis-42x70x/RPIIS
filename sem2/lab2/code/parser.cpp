// parser.cpp
#include "parser.hpp"
#include <cctype>

Parser::Parser(const std::string& input) : input(input) {}

Element Parser::parse() {
    skipWhitespace();
    return parseElement();
}

void Parser::skipWhitespace() {
    while (pos < input.size() && isspace(input[pos])) ++pos;
}

bool Parser::match(char c) {
    skipWhitespace();
    if (pos < input.size() && input[pos] == c) {
        ++pos;
        return true;
    }
    return false;
}

char Parser::peek() const {
    return pos < input.size() ? input[pos] : '\0';
}

char Parser::get() {
    return pos < input.size() ? input[pos++] : '\0';
}

std::string Parser::parseName() {
    skipWhitespace();
    std::string name;
    while (pos < input.size()) {
        char c = input[pos];
        if (isalnum(c) || c == '_') {
            name += c;
            ++pos;
        } else {
            break;
        }
    }
    if (name.empty()) throw std::runtime_error("Expected name at position " + std::to_string(pos));
    return name;
}

Element Parser::parseElement() {
    skipWhitespace();
    char c = peek();
    if (c == '{') {
        return parseSet(false);
    } else if (c == '<') {
        return parseSet(true);
    } else {
        Element el;
        el.name = parseName();
        el.isSet = false;
        return el;
    }
}

Element Parser::parseSet(bool ordered) {
    Element set;
    set.isSet = true;
    set.ordered = ordered;
    get(); // consume '{' or '<'
    skipWhitespace();

    if ((ordered && peek() == '>') || (!ordered && peek() == '}')) {
        get();
        return set; // empty set
    }

    while (true) {
        set.children.push_back(parseElement());
        skipWhitespace();
        if ((ordered && match('>')) || (!ordered && match('}')))
            break;
        if (!match(',')) throw std::runtime_error("Expected ',' at position " + std::to_string(pos));
    }

    return set;
}
