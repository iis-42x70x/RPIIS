// parser.cpp
#include "parser.hpp"
#include <cctype>

Parser::Parser(const std::string& input) : input(input) {}

Element Parser::parse() {
    skipWhitespace();
    // Разбираем корневой элемент (множество или атом)
    Element el = parseElement();

    // --- НОВОЕ: после parseElement() проверяем, что не осталось "лишнего" текста ---
    skipWhitespace();
    if (pos < input.size()) {
        // Выбросим исключение, чтобы в main.cpp у нас попало в catch и строка пропустилась
        throw std::runtime_error(
            "Найден лишний символ '" + std::string(1, input[pos]) +
            "' на позиции " + std::to_string(pos));
    }
    // ------------------------------------------------------------------------------

    return el;
}

void Parser::skipWhitespace() {
    while (pos < input.size() && isspace(static_cast<unsigned char>(input[pos]))) {
        ++pos;
    }
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
    if (pos < input.size()) {
        return input[pos];
    }
    return '\0';
}

char Parser::get() {
    if (pos < input.size()) {
        return input[pos++];
    }
    return '\0';
}

std::string Parser::parseName() {
    skipWhitespace();
    if (pos >= input.size() || !(isalpha(static_cast<unsigned char>(input[pos])))) {
        throw std::runtime_error(
            "Ожидалось имя (буква) на позиции " + std::to_string(pos));
    }

    std::string name;
    while (pos < input.size() && (isalnum(static_cast<unsigned char>(input[pos])) || input[pos] == '_')) {
        name.push_back(input[pos]);
        ++pos;
    }
    return name;
}

Element Parser::parseElement() {
    skipWhitespace();
    if (pos >= input.size()) {
        throw std::runtime_error("Неожиданный конец строки при разборе элемента");
    }

    // Если встретили '{' — это неупорядоченное множество
    if (match('{')) {
        return parseSet(false);
    }
    // Если встретили '<' — это упорядоченное множество
    if (match('<')) {
        return parseSet(true);
    }
    // Иначе — это имя (атомарный элемент)
    std::string nm = parseName();
    Element atom;
    atom.name = nm;
    return atom;
}

Element Parser::parseSet(bool ordered) {
    Element set;
    set.isSet = true;
    set.ordered = ordered;

    // Условие для пустого множества: сразу встретили '}' или '>' после '{' или '<'
    skipWhitespace();
    if ((ordered && peek() == '>') || (!ordered && peek() == '}')) {
        get(); // читаем символ '>' или '}'
        return set; // пустое множество
    }

    // Иначе читаем вложенные элементы
    while (true) {
        set.children.push_back(parseElement());
        skipWhitespace();
        // Если встретили '>' (для ordered) или '}' (для unordered) — значит конец множества
        if ((ordered && match('>')) || (!ordered && match('}'))) {
            break;
        }
        // Иначе ожидаем запятую
        if (!match(',')) {
            char found = (pos < input.size() ? input[pos] : '\0');
            throw std::runtime_error(
                "Ожидалась запятая ',' на позиции " + std::to_string(pos) +
                ", найден '" + std::string(1, found) + "'");
        }
    }

    return set;
}
