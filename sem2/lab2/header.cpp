#include "Set.h"

Set::Set() : head(nullptr) {}

Set::~Set() {
 
}

std::string Set :: normalize(std::string s) {
    if (s.empty() || s[0] != '{') {
        return s;
    }

    std::vector<std::string> elements;
    int i = 1;

    while (i < s.size() - 1) {
        if (s[i] == '{' || s[i] == '<') {
            char opening = s[i];
            char closing;
            
            if (opening == '{') {
                closing = '}';
            } else {
                closing = '>';
            }
            
            int balance = 1;
            int j = i + 1;
            
            while (j < s.size() && balance > 0) {
                if (s[j] == opening) balance++;
                else if (s[j] == closing) balance--;
                j++;
            }
            
            std::string nested = s.substr(i, j - i);
            elements.push_back(normalize(nested));
            i = j;
        }
        else if (s[i] != ',' && s[i] != ' ') {
            elements.push_back(std::string(1, s[i]));
            i++;
        }
        else {
            i++;
        }
    }

    std::sort(elements.begin(), elements.end());

    std::string result = "{";
    
    for (size_t k = 0; k < elements.size(); ++k) {
        if (k != 0) result += ",";
        result += elements[k];
    }
    
    result += "}";

    return result;
}

bool Set :: contains(std::string element) {
    std::string normElement = normalize(element);
    Node* current = head;
    
    while (current != nullptr) {
        if (normalize(current->value) == normElement) {
            return true;
        }
        current = current->next;
    }
    
    return false;
}

void Set :: push(std :: string str) {
    int curly_braces = 0;
    int angle_braces = 0;
    std::string current_element;

    for (int i = 1; i < str.size() - 1; ++i) {
        if (str[i] == ' ') continue;

        if (str[i] == ',' && curly_braces == 0 && angle_braces == 0) continue;

        if (curly_braces == 0 && angle_braces == 0 &&
            str[i] != '{' && str[i] != '}' && str[i] != '<' && str[i] != '>') {
            
            Node* new_node = new Node;
            new_node->value = std::string(1, str[i]);
            new_node->next = nullptr;
            
            if (head == nullptr) {
                head = new_node;
            } else {
                Node* last = head;
                while (last->next != nullptr) last = last->next;
                last->next = new_node;
            }
            continue;
        }

        if (str[i] == '{' || str[i] == '<') {
            if (str[i] == '{') curly_braces++;
            if (str[i] == '<') angle_braces++;
            current_element += str[i];
            continue;
        }

        if (str[i] == '}' || str[i] == '>') {
            current_element += str[i];
            if (str[i] == '}') curly_braces--;
            if (str[i] == '>') angle_braces--;

            if (curly_braces == 0 && angle_braces == 0) {
                std::string normalized_value;
                
                if (current_element[0] == '{') {
                    normalized_value = normalize(current_element);
                } else {
                    normalized_value = current_element;
                }
                
                Node* new_node = new Node;
                new_node->value = normalized_value;
                new_node->next = nullptr;

                if (head == nullptr) {
                    head = new_node;
                } else {
                    Node* last = head;
                    while (last->next != nullptr) last = last->next;
                    last->next = new_node;
                }
                current_element.clear();
            }
            continue;
        }

        if (curly_braces > 0 || angle_braces > 0) {
            current_element += str[i];
        }
    }
}

void Set::print(){
    Node* element = head;
    bool first = true;
    
    std::cout << "{";
    
    while (element != nullptr) {
        if (!first) std :: cout << ",";
        std :: cout << element->value;
        first = false;
        element = element->next;
    }
    std::cout << "}" << std::endl;
}

void Set :: push_back(std::string str) {
    Node* new_node = new Node;
    new_node->value = str;
    new_node->next = nullptr;

    if (head == nullptr) {
        head = new_node;
    }
    else {
        Node* last = head;
        while (last->next != nullptr) last = last->next;
        last->next = new_node;
    }
}

Set Set :: SymmetricalDifference(std::vector<Set> sets) {
    Set result;
    std::vector<std::string> all_elements;
    
    for (size_t i = 0; i < sets.size(); i++) {
        Node* current = sets[i].head;
        
        while (current != nullptr) {
            bool found = false;
            for (size_t j = 0; j < all_elements.size(); j++) {
                if (all_elements[j] == current->value) {
                    found = true;
                    break;
                }
            }
            if (!found) {
                all_elements.push_back(current->value);
            }
            current = current->next;
        }
    }

    for (int i = 0; i < all_elements.size(); i++) {
        std::string elem = all_elements[i];
        int total = 0;
        
        for (int j = 0; j < sets.size(); j++) {
            int count = 0;
            Node* current = sets[j].head;
            
            while (current != nullptr) {
                if (current->value == elem) count++;
                current = current->next;
            }
            
            if (j == 0) {
                total += count;
            } else {
                total -= count;
            }
        }
        
        int absolute;
        if (total < 0) {
            absolute = -total;
        } else {
            absolute = total;
        }
        
        for (int j = 0; j < absolute; j++) {
            result.push_back(elem);
        }
    }
    
    return result;
}
