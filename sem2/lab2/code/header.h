#ifndef HEADER_H
#define HEADER_H

#define MAX_SETS 10
#define MAX_ELEMENTS 100
#define MAX_ELEMENT_LENGTH 1000
#define MAX_LINE_LENGTH 1024

void trim_whitespace(char* str);
void remove_all_spaces(char* str);
void countFreqRec(int idx,
    char sets[MAX_SETS][MAX_ELEMENTS][MAX_ELEMENT_LENGTH],
    int set_counts[MAX_SETS],
    int set_count);
int parse_elements_recursive(const char* set_str, char elements[MAX_ELEMENTS][MAX_ELEMENT_LENGTH], int depth);
int parse_sets_from_line(const char* line, char sets[MAX_SETS][MAX_ELEMENTS][MAX_ELEMENT_LENGTH], int set_counts[MAX_SETS]);
bool is_equal(const char* a, const char* b);
bool exists_in(const char* elem, char set[][MAX_ELEMENT_LENGTH], int count);
int symmetric_difference_all(
    char sets[MAX_SETS][MAX_ELEMENTS][MAX_ELEMENT_LENGTH],
    int set_counts[MAX_SETS],
    int set_count,
    char result[MAX_ELEMENTS][MAX_ELEMENT_LENGTH]
);
void print_set(char elements[][MAX_ELEMENT_LENGTH], int count);

#endif
