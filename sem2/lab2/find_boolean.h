#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <locale>

#ifndef SET_OPERATIONS_H
#define SET_OPERATIONS_H

#define MAX_ELEMENTS 32
#define MAX_NAME_LEN 50
#define MAX_FILENAME_LEN 256
#define MAX_NESTING_LEVEL 5

typedef struct Element {
    char name[MAX_NAME_LEN];
    bool is_set;
    struct Element* elements;
    int element_count;
} Element;

typedef struct {
    char name[MAX_NAME_LEN];
    Element elements[MAX_ELEMENTS];
    int size;
} Set;

void skip_whitespace(FILE* file);
void read_element_name(FILE* file, char* name);
bool parse_element(FILE* file, Element* element, int nesting_level);
bool parse_set(FILE* file, Element* set_element, int nesting_level);
bool read_set(FILE* file, Set* set);

void print_element(const Element* element);
void generate_subsets(const Set* set);
void free_element(Element* element);

#endif