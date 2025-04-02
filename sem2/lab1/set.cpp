#include "Set.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

class Set {
private:
    class Node {
    public:
        std::string value;
        Node* next;
    };

    Node* head;

public:
    Set() {
        head = nullptr;
    }

    std::string normalize(const std::string& s) {
        if (s.empty() || s[0] != '{') return s;

        std::vector<std::string> elements;
        int i = 1;

        while (i < s.size() - 1) {
            if (s[i] == '{') {
                int balance = 1;
                int j = i + 1;
                
                while (j < s.size() && balance > 0) {
                    if (s[j] == '{') balance++;
                    else if (s[j] == '}') balance--;
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

    bool contains(const std::string& element) {
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

    void push(std::string str) {
        int n = 0;
        std::string s;

        for (int i = 1; i < str.size() - 1; ++i) {
            if (str[i] == ' ') continue;
            if (str[i] == ',' && n == 0) continue;

            if (n == 0 && str[i] != '{' && str[i] != '}') {
                std::string elem(1, str[i]);
                if (!contains(elem)) {
                    Node* new_node = new Node;
                    new_node->value = elem;
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
            }

            if (str[i] == '{') n++;
            if (n > 0) s += str[i];
            if (str[i] == '}') {
                n--;
               
                if (n == 0) {
                    std::string normalized = normalize(s);
                    if (!contains(normalized)) {
                        Node* new_node = new Node;
                        new_node->value = s;
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
                    s = "";
                }
            }
        }
    }

    bool find(const std::string& str) {
        return contains(str);
    }

    void push_back(std::string str) {
        if (!contains(str)) {
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
    }

    void del(std::string str) {
        if (head == nullptr) {
            std::cout << "Множество пусто." << std::endl;
            return;
        }

        if (normalize(head->value) == normalize(str)) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }

        Node* prev = head;
        Node* current = head->next;
        
        while (current != nullptr) {
            if (normalize(current->value) == normalize(str)) {
                prev->next = current->next;
                delete current;
                return;
            }
            prev = current;
            current = current->next;
        }
    }

    void print() {
        Node* element = head;
        std::cout << "{";
        bool first = true;
        while (element != nullptr) {
            if (!first) std::cout << ",";
            std::cout << element->value;
            first = false;
            element = element->next;
        }
        std::cout << "}" << std::endl;
    }

    Set Union(Set other) {
        Set result;
        Node* element = head;
        while (element != nullptr) {
            result.push_back(element->value);
            element = element->next;
        }
        element = other.head;
        while (element != nullptr) {
            result.push_back(element->value);
            element = element->next;
        }
        return result;
    }

    Set Intersection(Set other) {
        Set result;
        Node* element = head;
        while (element != nullptr) {
            if (other.contains(element->value)) {
                result.push_back(element->value);
            }
            element = element->next;
        }
        return result;
    }
};
