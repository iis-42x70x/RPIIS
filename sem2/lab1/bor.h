#pragma once
#include "Node.h"
#include <string>

void add_string(std::string, Node*);

int delete_string(std::string s, Node* root);

void recursive(Node* current, std::string word);

void view_bor(Node* root);

int search_string(std::string s, Node* root);

void delete_bor(Node*);