// parser.cpp
#include "parser.hpp"
#include <cctype>

Parser::Parser(const std::string& input) : input(input) {}

/**
 * Основная точка входа: пропускаем пробелы, разбираем один элемент (либо множество, либо атом).
 */
Element Parser::parse() {
    skipWhitespace();
    return parseElement();
}

void Parser::skipWhitespace() {
    while (pos < input.size() && std::isspace(static_cast<unsigned char>(input[pos]))) {
        ++pos;
    }
}

/**
 * Попытается увидеть в текущей позиции символ c (с учётом пропуска пробелов).
 * Если находит — съедает его и возвращает true, иначе возвращает false.
 */
bool Parser::match(char c) {
    skipWhitespace();
    if (pos < input.size() && input[pos] == c) {
        ++pos;
        return true;
    }
    return false;
}

char Parser::peek() const {
    return (pos < input.size()) ? input[pos] : '\0';
}

char Parser::get() {
    return (pos < input.size()) ? input[pos++] : '\0';
}

/**
 * Разбирает «имя» (атом): допускаем любую последовательность [буква|цифра|'_'], 
 * главное, чтобы она была непустой. Если первый символ — не буква и не цифра, бросаем исключение.
 */
std::string Parser::parseName() {
    skipWhitespace();
    if (pos >= input.size() || !std::isalnum(static_cast<unsigned char>(input[pos]))) {
        throw std::runtime_error("Ожидался атом (буква или цифра) на позиции " + std::to_string(pos));
    }
    std::string name;
    while (pos < input.size()) {
        char c = input[pos];
        if (std::isalnum(static_cast<unsigned char>(c)) || c == '_') {
            name.push_back(c);
            ++pos;
        } else {
            break;
        }
    }
    return name;
}

/**
 * Разбирает один элемент: если впереди '{' → нечёткое множество, если '<' → упорядоченное,
 * иначе — атом через parseName().
 */
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

/**
 * Разбирает множество. 
 *  - Если ordered == false → фигурные скобки {…}, иначе угловые <…>.
 *  - Для {…} (ordered==false) мы дополнительно игнорируем любые дубликаты при добавлении в set.children.
 */
Element Parser::parseSet(bool ordered) {
    Element set;
    set.isSet = true;
    set.ordered = ordered;

    // Съедаем открывающую скобку '{' или '<'
    get();
    skipWhitespace();

    // Если сразу следующая скобка — соответствующая закрывающая, возвращаем пустое множество
    if ((ordered && peek() == '>') || (!ordered && peek() == '}')) {
        get(); // съели '>' или '}'
        return set; // пустое множество
    }

    // Иначе разбираем подряд вложенные элементы через parseElement()
    while (true) {
        // 1) Разбираем один элемент (рекурсивно), получаем child
        Element child = parseElement();

        // 2) Если это неупорядоченное ({…}), проверяем дубликат
        if (!ordered) {
            bool exists = false;
            for (auto& prev : set.children) {
                if (prev.equals(child)) {
                    exists = true;
                    break;
                }
            }
            if (!exists) {
                set.children.push_back(child);
            }
            // если exists == true → просто игнорируем, НЕ бросаем ошибку
        }
        else {
            // Если это упорядоченное (<…>), добавляем без проверки
            set.children.push_back(child);
        }

        skipWhitespace();
        // 3) Если следующая — закрывающая скобка (соответственно '>' для ordered, '}' для не-ordered) — съедаем и выходим
        if ((ordered && match('>')) || (!ordered && match('}'))) {
            break;
        }
        // 4) Иначе ожидаем запятую. Если её нет — бросаем ошибку
        if (!match(',')) {
            throw std::runtime_error("Ожидалась запятая ',' на позиции " + std::to_string(pos));
        }
    }

    return set;
}
